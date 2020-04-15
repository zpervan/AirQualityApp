// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_DATA_TYPES_H
#define AIRQUALITYAPP_DATA_TYPES_H

#include <ctime>
#include <string>

/// @brief Parameters and values which describe air quality measurement
struct AirQualityMeasurement {
  float value{0.0};
  std::string unit_of_measurement{""};
  std::time_t epoch_time{0}; // Unix epoch time
  std::string standard_time{""};

  // Overloaded comparison operator for testing purposes
  friend bool operator==(const AirQualityMeasurement &lhs,
                         const AirQualityMeasurement &rhs);
};

inline bool operator==(const AirQualityMeasurement &lhs,
                       const AirQualityMeasurement &rhs) {
  return (lhs.value == rhs.value) &&
         (lhs.unit_of_measurement == rhs.unit_of_measurement) &&
         (lhs.epoch_time == rhs.epoch_time) &&
         (lhs.standard_time == rhs.standard_time);
}

class DataScraper;

/// @brief Url components from which the API URL is made of
/// @attention This should be only visible to the DataScraper class
struct UrlComponents {
public:
  const std::string address{"http://iszz.azo.hr/iskzl/rs/podatak/export/json?"};
  const std::string station{"postaja="};
  const std::string pollutant{"&polutant="};
  const std::string data_type{"&tipPodatka="};
  const std::string date_from{"&vrijemeOd="};
  const std::string date_to{"&vrijemeDo="};

private:
  friend class DataScraper;
  UrlComponents() = default;
};

enum class Pollutant {
  UNKNOWN = 0,
  CARBON_MONOXIDE = 3,
  OZONE = 32,
  BENZEN = 31
};
#endif // AIRQUALITYAPP_DATA_TYPES_H
