#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdbool.h>

typedef struct {
    char time[10];
    char latitude[10];
    char longitude[11];
    float altitude;
} GpsData;

bool parse_gps_data(const char* packet, GpsData* data);

#endif /* GPS_PARSER_H */