#include <stdio.h>
#include "gps_parser.h" //Header file for GPS parsing library
#include "esp_log.h"


static const char *TAG = "";

void app_main(void)
{

    
     char packet[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
   
    GPSData gpsData;
    gpsData = Parse_gps_data(packet);

    if (gpsData.check_sum_validated)
  {
    ESP_LOGW(TAG, "CHECKSUM VALIDATED!\n");
  }
  else
  {
    ESP_LOGW(TAG,"CHECKSUM IS NOT VALIDATED!\n");
  }

    if (parse_gps_data(ggaPacket, &gpsData)) {
        printf("Time: %s\n", gpsData.time);
        printf("Latitude: %f\n", gpsData.latitude);
        printf("Longitude: %f\n", gpsData.longitude);
    } else {
        printf("Invalid GGA packet\n");
    }
}
