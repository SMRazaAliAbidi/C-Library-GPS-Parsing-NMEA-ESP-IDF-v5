#include <stdio.h>  // Added for debugging
#include <string.h>
#include <stdlib.h>
#include "gps_parser.h"

gps_data Parse_gps_data(char *msg)
{
    gps_data gpsData;

    // Initializing data fields with a default value
    strcpy(gps_Data.time_stamp, field_missing);
    strcpy(gps_Data.latitude, field_missing);
    strcpy(gps_Data.lat_direction, field_missing);
    strcpy(gps_Data.longitude, field_missing);
    strcpy(gps_Data.lon_direction, field_missing);

    strcpy(gps_Data.calculated_checksum, field_missing);
    strcpy(gps_Data.parsed_checksum, field_missing);
   
   // clears checksum integrity flag 
    gpsData.check_sum_validated = false;

    // declaring the delimiter for strsep() function
    char delimiter[5] = ",";
    // pointer to the 2nd half of the separated string
    char *post_delimiter = msg;
    // pointer to the 1st half of the separated string
    char *pre_delimiter = msg;

    if (strncmp(ggaPacket, "$GPGGA,", 7) != 0)
        return false; // Not a GGA packet

    // Extract fields from the packet
    char time[11];
    char latitude[11];
    char longitude[12];
    char longitudeDirection, latitudeindicator;

    int result = sscanf(ggaPacket, "$GPGGA,%10[^,],%10[^,],%c,%11[^,],%c", time, latitude, &latitudeindicator, longitude, &longitudeDirection);
    if (result != 5)
        return false; // Invalid packet format or missing fields

    // Print extracted values
    printf("Time: %s\n", time);
    printf("Latitude: %s %c\n", latitude, latitudeindicator);
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
