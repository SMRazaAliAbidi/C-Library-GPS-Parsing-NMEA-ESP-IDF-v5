#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "gps_parser.h"

static const char *TAG = "gps_parser_example";

// Example GPS data handler function
void handle_gps_data(const GpsData *data) {
    // Process the parsed GPS data
    ESP_LOGI(TAG, "Time: %s", data->time);
    ESP_LOGI(TAG, "Latitude: %s", data->latitude);
    ESP_LOGI(TAG, "Longitude: %s", data->longitude);
    ESP_LOGI(TAG, "Altitude: %.1f", data->altitude);
}

void app_main() {
    // Example GPS data packet
    const char *packet = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
    
    // Parse GPS data
    GpsData data;
    if (parse_gps_data(packet, &data)) {
        // Display parsed GPS data
        handle_gps_data(&data);
    } else {
        ESP_LOGE(TAG, "Failed to parse GPS data!");
    }
}
