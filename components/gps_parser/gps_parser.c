#include "gps_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "esp_log.h"

static const char* TAG = "gps_parser";

bool validate_checksum(const char* packet) {
    // Find the start of the checksum
    const char* asterisk = strchr(packet, '*');
    if (asterisk == NULL)
        return false;
    
    // Calculate the checksum
    unsigned int checksum = 0;
    for (const char* c = packet + 1; c < asterisk; ++c)
        checksum ^= *c;
    
    // Parse the provided checksum
    unsigned int provided_checksum;
    if (sscanf(asterisk + 1, "%02X", &provided_checksum) != 1)
        return false;
    
    // Compare the calculated and provided checksums
    return checksum == provided_checksum;
}

    bool parse_gps_data(const char* packet, GpsData* data) {
    // Check if the packet starts with "$GPGGA"
    if (strncmp(packet, "$GPGGA,", 7) != 0) {
        ESP_LOGE(TAG, "Invalid packet format: %s", packet);
        return false;
    }
    
    // Validate packet integrity
    if (!validate_checksum(packet)) {
        ESP_LOGE(TAG, "Invalid checksum: %s", packet);
        return false;
    }
   
    // Tokenize the packet using ',' as the delimiter
    char* packet_copy = strdup(packet);
    char* token = strtok(packet_copy, ",");

    
    // Skip the first six tokens
    for (int i = 0; i < 6; i++) {
        token = strtok(NULL, ",");
        if (token == NULL)
            return false;
    }
    
    // Parse the time
    strncpy(data->time, token, 9);
    data->time[9] = '\0';
    
    // Parse the latitude
    token = strtok(NULL, ",");
    if (token == NULL)
        return false;
    strncpy(data->latitude, token, 9);
    data->latitude[9] = '\0';
    
    // Parse the latitude hemisphere
    token = strtok(NULL, ",");
    if (token == NULL)
        return false;
    if (token[0] == 'S')
        data->latitude[0] = '-';
    
    // Parse the longitude
    token = strtok(NULL, ",");
    if (token == NULL)
        return false;
    strncpy(data->longitude, token, 10);
    data->longitude[10] = '\0';
    
    // Parse the longitude hemisphere
    token = strtok(NULL, ",");
    if (token == NULL)
        return false;
    if (token[0] == 'W')
        data->longitude[0] = '-';
    
    // Skip the next four tokens
    for (int i = 0; i < 4; i++) {
        token = strtok(NULL, ",");
        if (token == NULL)
            return false;
    }
    
    // Parse the altitude
    token = strtok(NULL, ",");
    if (token == NULL)
        return false;
    data->altitude = strtof(token, NULL);
    
    return true;
}
