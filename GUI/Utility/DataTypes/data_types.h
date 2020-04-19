// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_DATA_TYPES_H
#define AIRQUALITYAPP_DATA_TYPES_H

#include <ctime>
#include <map>
#include <string>

// Forward declarations
class AirMeasurementFetcher;

/// @brief Parameters and values which describe an air quality measurement
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

/// @brief URL components from which the air quality measurement URL is made of
/// @attention This should be only visible to the AirMeasurementFetcher class
struct UrlComponents {
public:
  const std::string address{"http://iszz.azo.hr/iskzl/rs/podatak/export/json?"};
  const std::string station{"postaja="};
  const std::string pollutant{"&polutant="};
  const std::string data_type{"&tipPodatka="};
  const std::string date_from{"&vrijemeOd="};
  const std::string date_to{"&vrijemeDo="};

private:
  friend class AirMeasurementFetcher;
  UrlComponents() = default;
};

/// @brief Data types for pollutant classification and mapping
/// @attention To reduce confusion, this has it's own namespace because they are
/// multiple data and data structures with the name "Pollutant" in it.
namespace Mapping {

enum class Pollutant {
  UNKNOWN = 0,
  NITROGEN_DIOXIDE = 1,
  SULFUR_DIOXIDE = 2,
  CARBON_MONOXIDE = 3,
  OZONE = 32,
  BENZENE = 31,
  TEMPERATURE = 475
};

static std::map<Pollutant, std::string> PollutantValues{
    {Pollutant::UNKNOWN, "0"},        {Pollutant::NITROGEN_DIOXIDE, "1"},
    {Pollutant::SULFUR_DIOXIDE, "2"}, {Pollutant::CARBON_MONOXIDE, "3"},
    {Pollutant::OZONE, "31"},         {Pollutant::BENZENE, "32"},
    {Pollutant::TEMPERATURE, "475"}};

} // namespace Mapping

#endif // AIRQUALITYAPP_DATA_TYPES_H
