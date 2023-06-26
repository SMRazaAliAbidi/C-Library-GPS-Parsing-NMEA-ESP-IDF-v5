#include <stdio.h>
#include "gps_parser.h"


void app_main(void)
{
     const char* ggaPacket = "$GPGGA,123519.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,-164.0,M,,,,*47";
    GPSData gpsData;

    if (parse_gps_data(ggaPacket, &gpsData)) {
        printf("Time: %s\n", gpsData.time);
        printf("Latitude: %f\n", gpsData.latitude);
        printf("Longitude: %f\n", gpsData.longitude);
    } else {
        printf("Invalid GGA packet\n");
    }
}
