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
    char time[25];
    char latitude[15];
    char latitude_d[15];
    char longitude[15];
    char longitude_d[15];
    char calc_checksum[16];
    char parse_checksum[16];
    bool validstring, checkpass;

} GpsData;

GpsData parse_gps_data(char *packet, GpsData data);

void calculateChecksum(const char *sentence, GpsData *data);
void parsechecksum(const char *sentence, GpsData *data);
void print_gps_data(GpsData data);

#endif /* GPS_PARSER_H */