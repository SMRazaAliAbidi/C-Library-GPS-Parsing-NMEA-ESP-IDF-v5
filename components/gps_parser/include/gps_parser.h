#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // for atoi, atof
#include <string.h> // for strchr
#include <stdbool.h>
#include <esp_log.h>

#define invalid "Invalid Data"
#define null_data "Null Data"

static const char *TAG = "gps_parser";

typedef struct gps_data_parser
{
    char time[25];                //GPS Time Information
    char latitude[15];            // Latitude Value
    char latitude_d[15];          // Longitude Value
    char longitude[15];           // Direction of Latitude (N,S)
    char longitude_d[15];         // Direction of Longitude (E,W)
    char qual_ind[15];            // Quality indicator
    char num_satellites[15];      // Number of satellites
    char HDOP[15];                // Horizontal Dilution of Precision
    char altitude_antenna[15];    // Altitude of antenna
    char units_antenna[15];       // Units of antenna altitude
    char geoidal_separation[15];  // Geoidal separation
    char units_separation[15];    // Units of geoidal separation
    char age_correction[15];      // correction age
    char correction_sta[15];      // Correction station ID
    char calc_checksum[16];       // Calculated Value of checksum
    char parse_checksum[16];      // Parsed Value of checksunm
    bool validstring, checkpass;  //Indicators for checksum and string validation

} GpsData;

GpsData parse_gps_data(char *packet, GpsData data);

void calculateChecksum(const char *sentence, GpsData *data);
void parsechecksum(const char *sentence, GpsData *data);
void print_gps_data(GpsData data);

#endif /* GPS_PARSER_H */