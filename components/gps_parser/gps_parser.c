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
    strcpy(gps_data.qual_ind, null_data);
    strcpy(gps_data.num_satellites, null_data);
    strcpy(gps_data.HDOP, null_data);
    strcpy(gps_data.altitude_antenna, null_data);
    strcpy(gps_data.units_antenna, null_data);
    strcpy(gps_data.geoidal_separation, null_data);
    strcpy(gps_data.units_separation, null_data);
    strcpy(gps_data.age_correction, null_data);
    strcpy(gps_data.correction_sta, null_data);
    gps_data.checkpass = false;

    char time[11];
    char latitude[12];
    char longitude[14];
    char longitudeDirection;
    char latitudeDirection;
    char qual_ind[5];
    char num_satellites[5];
    char HDOP[5];
    char altitude_antenna[10];
    char units_antenna;
    char geoidal_separation[10];
    char units_separation;
    char age_correction[10];
    char correction_sta[10];

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

        int result = sscanf(packet, "$GPGGA,%15[^,],%15[^,],%c,%15[^,],%c,%4[^,],%4[^,],%4[^,],%10[^,],%c,%15[^,],%c,%10[^,],%4[^,]", time, latitude, &latitudeDirection, longitude, &longitudeDirection, qual_ind, num_satellites, HDOP, altitude_antenna, &units_antenna, geoidal_separation, &units_separation, age_correction, correction_sta);

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


        // Copy the parsed values to the gps_data structure
        snprintf(gps_data.time, sizeof(gps_data.time), "%s", time);
        snprintf(gps_data.latitude, sizeof(gps_data.latitude), "%s", latitude);
        snprintf(gps_data.longitude, sizeof(gps_data.longitude), "%s", longitude);
        snprintf(gps_data.latitude_d, sizeof(gps_data.latitude_d), "%c", latitudeDirection);
        snprintf(gps_data.longitude_d, sizeof(gps_data.longitude_d), "%c", longitudeDirection);
        snprintf(gps_data.qual_ind, sizeof(gps_data.qual_ind), "%1s", qual_ind);
        snprintf(gps_data.num_satellites, sizeof(gps_data.num_satellites), "%s", num_satellites);
        snprintf(gps_data.HDOP, sizeof(gps_data.HDOP), "%s", HDOP);
        snprintf(gps_data.altitude_antenna, sizeof(gps_data.altitude_antenna), "%s", altitude_antenna);
        snprintf(gps_data.units_antenna, sizeof(gps_data.units_antenna), "%c", units_antenna);
        snprintf(gps_data.geoidal_separation, sizeof(gps_data.geoidal_separation), "%s", geoidal_separation);
        snprintf(gps_data.units_separation, sizeof(gps_data.units_separation), "%c", units_separation);
        snprintf(gps_data.age_correction, sizeof(gps_data.age_correction), "%s", age_correction);
        snprintf(gps_data.correction_sta, sizeof(gps_data.correction_sta), "%s", correction_sta);

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
        strcpy(gps_data.qual_ind, invalid);
        strcpy(gps_data.num_satellites, invalid);
        strcpy(gps_data.HDOP, invalid);
        strcpy(gps_data.altitude_antenna, invalid);
        strcpy(gps_data.units_antenna, invalid);
        strcpy(gps_data.geoidal_separation, invalid);
        strcpy(gps_data.units_separation, invalid);
        strcpy(gps_data.age_correction, invalid);
        strcpy(gps_data.correction_sta, invalid);
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
    printf("Quality Indicator:      %s\n", data.qual_ind);
    printf("Number of Satellites:   %s\n", data.num_satellites);
    printf("HDOP:                   %s\n", data.HDOP);
    printf("Altitude of Antenna:    %s\n", data.altitude_antenna);
    printf("Unit of Altitude:       %s\n", data.units_antenna);
    printf("Geoidal Separation:     %s\n", data.geoidal_separation);
    printf("Unit of Geoidal:        %s\n", data.units_separation);
    printf("Age Correction:         %s\n", data.age_correction);
    printf("Station Correction:     %s\n", data.correction_sta);
    printf("Parsed Check Sum        %s\n", data.parse_checksum);
    printf("Calculated Check Sum    %s\n", data.calc_checksum);
}
