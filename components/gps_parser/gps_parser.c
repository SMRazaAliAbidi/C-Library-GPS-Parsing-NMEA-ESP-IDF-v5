#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gps_parser.h"
#include <ctype.h> //for the isxdigit function

GpsData parse_gps_data(char *packet, GpsData gps_data)
{
    // GpsData gps_data;

    // Initializing data fields with a default value
    strcpy(gps_data.time, null_data);
    strcpy(gps_data.latitude, null_data);
    strcpy(gps_data.latitude_d, null_data);
    strcpy(gps_data.longitude, null_data);
    strcpy(gps_data.longitude_d, null_data);
    strcpy(gps_data.calc_checksum, null_data);
    strcpy(gps_data.parse_checksum, null_data);
    gps_data.checkpass = false;

    char time[11];
    char latitude[12];
    char longitude[14];
    char longitudeDirection;
    char latitudeDirection;
    if (!(strncmp(packet, "$GPGGA", 6)))
    {
        gps_data.validstring = true; // Packet validity is checked
        // Compare Checksums
        calculateChecksum(packet, &gps_data);
        parsechecksum(packet, &gps_data);

        if (strcmp(gps_data.parse_checksum, gps_data.calc_checksum) == 0)
        {
            gps_data.checkpass = true;
        }
        else
        {
            gps_data.checkpass = false;
        }

        int result = sscanf(packet, "$GPGGA,%15[^,],%15[^,],%c,%15[^,],%c", time, latitude, &latitudeDirection, longitude, &longitudeDirection);
        if (result != 5)
        {
            return gps_data;
        }
        else
        {

            // Parsing the time into standard format:
            int hours, tminutes, seconds;
            float milliseconds;
            sscanf(time, "%2d%2d%2d.%f", &hours, &tminutes, &seconds, &milliseconds);

            if (hours >= 0 && hours <= 23 && tminutes >= 0 && tminutes <= 59 && seconds >= 0 && seconds <= 59)
            {
                sprintf(gps_data.time, "%02d:%02d:%02d.%03d", hours, tminutes, seconds, (int)(milliseconds * 1000));
            }
            else
            {
                strcpy(gps_data.time, "Invalid time format!");
            }

            // Parse the longitude value
            float longitudeValue = atof(longitude);
            int degrees = (int)(longitudeValue / 100);
            float minutes = longitudeValue - (degrees * 100);
            longitudeValue = degrees + (minutes / 60.0);

            // Copy the parsed values to the gps_data structure
            snprintf(gps_data.time, sizeof(gps_data.time), "%s", time);
            snprintf(gps_data.latitude, sizeof(gps_data.latitude), "%s", latitude);
            snprintf(gps_data.longitude, sizeof(gps_data.longitude), "%f", longitudeValue);
            snprintf(gps_data.latitude_d, sizeof(gps_data.latitude_d), "%c", latitudeDirection);
            snprintf(gps_data.longitude_d, sizeof(gps_data.longitude_d), "%c", longitudeDirection);
        }
        return gps_data;
    }
    else
    {
        // cleard the string valiidty flag
        gps_data.validstring = false;

        // stored invalid string flag in all fields
        strcpy(gps_data.time, invalid);
        strcpy(gps_data.latitude, invalid);
        strcpy(gps_data.latitude_d, invalid);
        strcpy(gps_data.longitude, invalid);
    }
    return gps_data;
}

void calculateChecksum(const char *sentence, GpsData *gps_Data)
{
    // GpsData gps_Data;

    unsigned char checksum = 0;

    // Iterate over each character in the sentence
    for (int i = 1; sentence[i] != '\0' && sentence[i] != '*'; i++)
    {
        // Exclude the dollar sign '$' character
        if (sentence[i] != '$')
        {
            // XOR each character with the checksum
            checksum ^= sentence[i];
        }
    }

    // Store the calculated checksum in the data structure
    snprintf(gps_Data->calc_checksum, sizeof(gps_Data->calc_checksum), "%02X", checksum);

    ESP_LOGW(TAG, "The checksum is calculated successfully: %s", gps_Data->calc_checksum);
}

void parsechecksum(const char *sentence, GpsData *data)
{

    // GpsData data;
    int ast = 0;
    int j = 0;
    int CHECKSUM_LENGTH = 3;

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
            if (isxdigit((unsigned char)sentence[i])) // Check if character is a valid hexadecimal digit
            {
                data->parse_checksum[j++] = sentence[i];
                if (j >= CHECKSUM_LENGTH - 1) // Stop if reached the maximum length of the checksum
                    break;
            }
        }
    }
    data->parse_checksum[j] = '\0';
    ESP_LOGW(TAG, "The checksum is parsed successfully: %s", data->parse_checksum);
}
void print_gps_data(GpsData data)
{
    // GpsData data;
    printf("Time:                   %s\n", data.time);
    printf("Latitude:               %s\n", data.latitude);
    printf("Latitude Direction:     %s\n", data.latitude_d);
    printf("Longitude:              %s\n", data.longitude);
    printf("Longitude Direction:    %s\n", data.longitude_d);
}
