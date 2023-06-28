#include "gps_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "esp_log.h"

static const char *TAG = "gps_parser";

GpsData parse_gps_data(const char *packet);
{
    GpsData gps_data;

    // Initializing data fields with a default value
    strcpy(gps_data.time, null_data);
    strcpy(gps_data.latitude, null_data);
    strcpy(gps_data.latitude_d, null_data);
    strcpy(gps_data.longitude, null_data);
    strcpy(gps_data.longitude_d, null_data);
    strcpy(gps_data.calc_checksum, null_data);
    strcpy(gps_data.parse_checksum, null_data);
    gps_Data.checkpass = false;

    // strsep() delimiter declared comma
    char delimiter[5] = ",";
    // pointer to both parts of the separated string
    char *post_delimiter = packet;
    char *pre_delimiter = packet;

    if (!(strncmp(packet, "$GPGGA", 6)))
    {
        // Compare Checksums
        unsigned char calculatedcheck = calculateChecksum(packet);
        unsigned char parsedcheck = parsechecksum(packet);
        if (strcmp(gps_Data.parse_checksum, gps_Data.calc_checksum) == 0)
        {
            gps_data.checkpass = true;
        }
        else
        {
            gps_data.checkpass = false;
        }
        pre_delimiter = strsep(&post_delimiter, "*");
        post_delimiter = pre_delimiter;
        pre_delimiter = strsep(&post_delimiter, delimiter);

        // Parsing time
        pre_delimiter = strsep(&post_delimiter, delimiter);
        if (!(strcmp(pre_delimiter, "")))
        {
            strcpy(gps_Data.time, null_data);
        }
        else
        {
            // converting time to standard format
            int hours, minutes, seconds;
            float milliseconds;
            sscanf(pre_delimiter, "%2d%2d%2d.%f", &hours, &minutes, &seconds, &milliseconds);

            if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59)
            {
                sprintf(gps_Data.time, "%02d:%02d:%02d.%03d", hours, minutes, seconds, (int)(milliseconds * 1000));
            }
            else
            {
                strcpy(gps_data.time, "Invalid time format!");
            }
        }
        // Parsing Latitude
        pre_delimiter = strsep(&post_delimiter, delimiter);
        if (!(strcmp(pre_delimiter, "")))
        {
            strcpy(gps_data.latitude, null_data);
        }
        else
        {
            strcpy(gps_data.latitude, pre_delimiter);
        }

        // Parsing latitude direction
        pre_delimiter = strsep(&post_delimiter, delimiter);
        if (!(strcmp(pre_delimiter, "")))
        {
            strcpy(gps_data.latitude_d, null_data);
        }
        else
        {
            strcpy(gps_data.latitude_d, pre_delimiter);
        }

        // Parsing longitude
        pre_delimiter = strsep(&post_delimiter, delimiter);
        if (!(strcmp(pre_delimiter, "")))
        {
            strcpy(gps_data.longitude, null_data);
        }
        else
        {
            strcpy(gps_data.longitude, pre_delimiter);
        }

        // Parsing Longitude Direction
        pre_delimiter = strsep(&post_delimiter, delimiter);
        if (!(strcmp(pre_delimiter, "")))
        {
            strcpy(gps_data.longitude_d, null_data);
        }
        else
        {
            strcpy(gps_data.longitude_d, pre_delimiter);
        }
        return gpsData;
    }
    return gpsData;
}

unsigned char calculateChecksum(const char *sentence)
{
    GpsData gps_Data;

    unsigned char checksum = 0;

    // Iterate over each character in the sentence
    for (int i = 1; sentence[i] != '\0'; i++)
    {
        // Exclude the dollar sign '$' and asterisk '*' characters
        if (sentence[i] != '$' && sentence[i] != '*')
        {
            // XOR each character with the checksum
            checksum ^= sentence[i];
        }
    }
    ESP_LOGW(TAG, "The checksum is calculated successfully %02X", checksum);
    gps_Data.calc_checksum = checksum;
    return checksum;
}
unsigned char parsechecksum(const char *sentence)
{
    GpsData gps_Data;
    int ast = 0;
    int j = 0;

    // Extracting checksum from the given GGA sentence
    for (int i = 0; sentence[i] != '\0'; i++)
    {
        if (sentence[i] == '*')
        {
            ast = 1;
            continue;
        }
        else if (ast)
        {
            gps_Data.parse_checksum[j++] = sentence[i];
        }
    }
    gps_Data.parse_checksum[j] = '\0';

    if (!(strcmp(gps_Data.parse_checksum, "")))
    {
        strcpy(gps_Data.parse_checksum, null_data);
        strcpy(gps_Data.calc_checksum, "");
    }
    else
    {
        ESP_LOGW(TAG, "The checksum is parsed successfully");
        return gps_Data.parse_checksum;
    }
}
