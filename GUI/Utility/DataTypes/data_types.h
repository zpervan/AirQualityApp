// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan
//

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
#endif // AIRQUALITYAPP_DATA_TYPES_H
