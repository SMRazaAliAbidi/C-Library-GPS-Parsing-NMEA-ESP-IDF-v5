#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "gps_parser.h" // Include the header file of the function to be tested
#include "esp_log.h"




// Function to run the unit tests
void runTest()
{
    // Test case 1: Valid GPS data
    char packet[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0031*5E";
    GpsData gpsdata;
    gpsdata = parse_gps_data(packet, gpsdata);
    if(gpsdata.checkpass)
    {
        ESP_LOGW(TAG, "Checksum is Validated.\n");
    }
    else{
        ESP_LOGW(TAG, "Checksum Error.\n");
    }
    // Test individual struct fields
    if (!(strcmp(gpsdata.time, "002153.00")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (time_stamp)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (time_stamp)\n");
    }

    if (!(strcmp(gpsdata.latitude, "3342.6618")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (latitude)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (latitude)\n");
    }

    if (!(strcmp(gpsdata.latitude_d, "N")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Latitude direction)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Latitude direction)\n");
    }

    if (!(strcmp(gpsdata.longitude, "11751.3858")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Longitude)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Longitude)\n");
    }


    if (!(strcmp(gpsdata.longitude_d, "W")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Longitude Direction)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Longitude Direction)\n");
    }

    if (!(strcmp(gpsdata.qual_ind, "1")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Quality Indicator)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Quality Indicator)\n");
    }

    if (!(strcmp(gpsdata.num_satellites, "10")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Num of Satellites)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Num of Satellites)\n");
    }

    if (!(strcmp(gpsdata.HDOP, "1.2")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (HDOP)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (HDOP)\n");
    }

    if (!(strcmp(gpsdata.altitude_antenna, "27.0")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Altitude of antenna)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Altitude of antenna)\n");
    }


    if (!(strcmp(gpsdata.units_antenna, "M")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Units of Antenna)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Units of Antenna)\n");
    }


    if (!(strcmp(gpsdata.geoidal_separation, "-34.2")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Geoidal Separation)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Geoidal Separation)\n");
    }

    if (!(strcmp(gpsdata.units_separation, "M")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Units of Geoidal Separation)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Units of Geoidal Separation)\n");
    }

    if (!(strcmp(gpsdata.age_correction, "Null Data")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Age Correction)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Age Correction)\n");
    }

    if (!(strcmp(gpsdata.correction_sta, "0031")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Units of Age Correction)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Units of Age Correction)\n");
    }

    if (!(strcmp(gpsdata.calc_checksum, "5E")))
    {
        ESP_LOGD(TAG, "Test case 1: Passed (Calculated Checksum)\n");
    }
    else
    {
        ESP_LOGE(TAG, "Test case 1: Failed (Calculated Checksum)\n");
    }

}
void app_main(void)
{
    runTest(); // Run the unit tests
}