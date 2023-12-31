#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "gps_parser.h"

//static const char *TAG = "gps_parser";


void app_main() {
    // Example GPS data packet
    char *packet = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,2.0,0031*70";
    //char *packet = "$GPGGA,172814.0,3723.46587704,N,12202.26957864,W,2,6,1.2,18.893,M,-25.669,M,2.0 0031*4F";
    
    // Parse GPS data
    GpsData data;
    data = parse_gps_data(packet, data);
    if(data.checkpass)
    {
        ESP_LOGW(TAG, "Checksum is Validated.\n");
    }
    else{
        ESP_LOGW(TAG, "Checksum Error.\n");
    }

if (data.validstring){
  print_gps_data(data);}
  else{
    ESP_LOGW(TAG, "Error in string parsing.\n");
  }
}
