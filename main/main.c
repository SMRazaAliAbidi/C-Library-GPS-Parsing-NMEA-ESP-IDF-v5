#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "gps_parser.h"

//static const char *TAG = "gps_parser";


void app_main() {
    // Example GPS data packet
    char *packet = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
    
    // Parse GPS data
    GpsData data;
    data = parse_gps_data(packet);
    if(data.checkpass)
    {
        ESP_LOGW(TAG, "Checksum is Validateed.\n");
    }
    else{
        ESP_LOGW(TAG, "Checksum Error.\n");
    }

  print_gps_data(&data);
}
