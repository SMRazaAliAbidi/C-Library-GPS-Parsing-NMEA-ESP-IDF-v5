#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // for atoi, atof
#include <string.h> // for strchr
#include <stdbool.h>
#include <esp_log.h>

#define Invalid_data "Invalid Data"
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

GpsData parse_gps_data(const char* packet);

void print_gps_data(const GpsData *data)
{
    ESP_LOGW(TAG, "GPS Data:");
    ESP_LOGW(TAG, "Time: %s", data->time);
    ESP_LOGW(TAG, "Latitude: %s", data->latitude);
    ESP_LOGD(TAG, "Latitude Direction:     %s\n", data->latitude_d);
    ESP_LOGW(TAG, "Longitude: %s", data->longitude);
    ESP_LOGD(TAG, "Longitude Direction:    %s\n", data->longitude_d);
    printf("Checksum: %s", data->calc_checksum);
}

#endif /* GPS_PARSER_H */