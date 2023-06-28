#include <stdio.h>
#include "gps_parser.h"
#include "esp_log.h"

// Define the tag for ESP_LOG
static const char *TAG = "GPS";

int main()
{
    // Example GPS data
    char gpsDataString[] = "$GPGGA,123456.789,12.3456789,N,123.4567890,E,1,8,1.2,123.4,M,56.7,M,1.0,12345";

    // Parse GPS data
    gps_data parsedData = Parse_gps_data(gpsDataString);

    // Initialize ESP_LOG
    esp_log_level_set(TAG, ESP_LOG_DEBUG); // Set the log level to DEBUG

    // Display GPS data using ESP_LOG
    ESP_LOGI(TAG, "Time Stamp: %s", parsedData.time_stamp);
    ESP_LOGI(TAG, "Latitude: %s", parsedData.latitude);
    ESP_LOGI(TAG, "Latitude Direction: %s", parsedData.lat_direction);
    ESP_LOGI(TAG, "Longitude: %s", parsedData.longitude);
    ESP_LOGI(TAG, "Longitude Direction: %s", parsedData.lon_direction);
    ESP_LOGI(TAG, "Quality Indicator: %s", parsedData.qual_ind);
    ESP_LOGI(TAG, "Number of Satellites: %s", parsedData.num_satellites);
    ESP_LOGI(TAG, "HDOP: %s", parsedData.HDOP);
    ESP_LOGI(TAG, "Altitude of Antenna: %s", parsedData.altitude_antenna);
    ESP_LOGI(TAG, "Unit of Altitude: %s", parsedData.units_antenna);
    ESP_LOGI(TAG, "Geoidal Separation: %s", parsedData.geoidal_separation);
    ESP_LOGI(TAG, "Unit of Geoidal: %s", parsedData.units_separation);
    ESP_LOGI(TAG, "Age Correction: %s", parsedData.age_correction);
    ESP_LOGI(TAG, "Station Correction: %s", parsedData.correction_sta);
    ESP_LOGI(TAG, "Parsed Check Sum: %s", parsedData.parsed_checksum);
    ESP_LOGI(TAG, "Calculated Check Sum: %s", parsedData.calculated_checksum);

    return 0;
}
