
# _C Library for Parsing GPS Data _

The GPS Parser Library is a C library designed to parse GPS data from NMEA 0183 (GPGGA) payloads. It offers a straightforward interface for extracting various GPS data fields, including latitude, longitude, altitude, and time from NMEA 0183 (GPGGA) strings.


## Implemented Features
The library currently supports the following features:

1. Parsing GPS data from NMEA 0183 (GPGGA) strings.
2. Validating the checksum of the received GPS data.
3. Extracting and storing various GPS data fields, such as time, latitude, longitude, altitude, etc.
4. Printing the parsed GPS data for easy inspection.

## Approach
 The GPS data parser code follows a systematic approach to extract the necessary information from GPS data strings while monitoring missing or incorrect data. The main function responsible for parsing is parse_gps_data, which takes a GPGGA string as input, performs operations to extract useful information, and returns the individual fields' data in a structure called gps_data.

    At the beginning of the function, all fields in the gps_data structure are initialized with default values. The code then checks if the string starts with the talker ID '$GPGGA' using the strcmp() function. If it does not match, the function returns, and the code execution terminates.

    Before parsing the data, the code checks the validity of the checksum. It extracts the exact checksum value from the GPGGA sentence and calculates the checksum of the given data. The calculated checksum is compared with the extracted checksum to validate the integrity of the data.

    Once the checksum is validated, the code proceeds to parse the individual fields using the sscanf() function. It starts by parsing the time_stamp field and continues iteratively for 14 fields until the last available field. If sscanf returns a NULL value, it indicates that there is no data between two consecutive commas, and the missing field is stored accordingly with a placeholder.

    After parsing all the fields, the parsed data can be displayed on the terminal using functions such as ESP_LOGW or printf(). Additionally, the provided print_gps_data function can be used to print all the parsed GPS data fields.

    This approach ensures that the GPS data is accurately parsed, missing fields are identified, and the integrity of the data is verified before extraction.

## Installation

1. Clone the repository from GitHub.
2. Include the gps_parser.h header file in your project.
3. Build your project with the GPS Parser Library source files.
4. Run your project.

## Prerequisites
The GPS Parser Library has the following prerequisites:

1. Standard C library
2. ESP-IDF Library (required for ESP32 development)
## Functions
The GPS Parser Library provides the following functions:

1. parse_gps_data: Parses the GPS data from the NMEA 0183 (GPGGA) string and returns a GpsData structure containing the parsed data.
2. calculateChecksum: Calculates the checksum of the given GPS data sentence and stores it in the calc_checksum field of the GpsData structure.
3. parsechecksum: Extracts the checksum from the GPS data sentence and stores it in the parse_checksum field of the GpsData structure.
4. print_gps_data: Prints the parsed GPS data stored in the GpsData structure.
## Contact

For any inquiries or issues related to the GPS Parser Library, please contact:

Author: Syed Muhammad Raza Ali Abidi
Email: smabidi32@gmail.com