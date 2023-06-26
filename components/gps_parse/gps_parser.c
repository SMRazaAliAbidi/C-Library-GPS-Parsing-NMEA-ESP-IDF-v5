#include <stdio.h>  // Added for debugging
#include <string.h>
#include <stdlib.h>
#include "gps_parser.h"

bool parse_gps_data(const char* ggaPacket, GPSData* gpsData) {
    // Check the packet type

    if (strncmp(ggaPacket, "$GPGGA,", 7) != 0)
        return false; // Not a GGA packet

    // Extract fields from the packet
    char time[11];
    char latitude[12];
    char longitude[14];
    char longitudeDirection;

    int result = sscanf(ggaPacket, "$GPGGA,%10[^,],%11[^,],%13[^,],%c", time, latitude, longitude, &longitudeDirection);
    if (result != 4)
        return false; // Invalid packet format or missing fields

    // Print extracted values
    printf("Time: %s\n", time);
    printf("Latitude: %s\n", latitude);
    printf("Longitude: %s %c\n", longitude, longitudeDirection);

    // Copy extracted values to the GPSData struct
    strcpy(gpsData->time, time);
    gpsData->latitude = atof(latitude);

    // Parse the longitude value
    float longitudeValue = atof(longitude);
    int degrees = (int)(longitudeValue / 100);
    float minutes = longitudeValue - (degrees * 100);
    gpsData->longitude = degrees + (minutes / 60.0);

    // Adjust longitude based on the direction indicator
    if (longitudeDirection == 'W' || longitudeDirection == 'w')
        gpsData->longitude *= -1;
    // Add code to extract other GGA parameters as needed

    // Validate the checksum
    int checksumIndex = strlen(ggaPacket) - 2;
    if (ggaPacket[checksumIndex] != '*')
        return false; // Invalid packet format

    uint8_t calculatedChecksum = 0;
    for (int i = 1; i < checksumIndex; i++)
        calculatedChecksum ^= ggaPacket[i];

    char receivedChecksum[3];
    strncpy(receivedChecksum, ggaPacket + checksumIndex + 1, 2);
    receivedChecksum[2] = '\0';

    uint8_t parsedChecksum = strtol(receivedChecksum, NULL, 16);
    if (calculatedChecksum != parsedChecksum) {
        printf("Calculated checksum: %02X\n", calculatedChecksum);
        printf("Received checksum: %02X\n", parsedChecksum);
        return false; // Checksum mismatch
    }

    return true;
}
