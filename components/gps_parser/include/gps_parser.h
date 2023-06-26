#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdbool.h>

typedef struct {
    char time[11];
    double latitude;
    double longitude;
    // Add other GPS parameters as needed
} GPSData;

bool parse_gps_data(const char* ggaPacket, GPSData* gpsData);

#endif  /* GPS_PARSER_H */
