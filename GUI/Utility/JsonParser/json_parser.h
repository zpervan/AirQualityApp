// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_JSON_PARSER_H
#define AIRQUALITYAPP_JSON_PARSER_H

#include "../DataTypes/data_types.h"

#include <array>
#include <optional>
#include <string>
#include <vector>

// TODO: Epoch conversion to date should be done here

/// @brief Parses the fetched JSON file and assigns the values with the
/// appropriate data.
/// @attention There should be only one instance of this object!
class JsonParser {
public:
  JsonParser() = default;

  /// @brief Fills JsonParser's data buffer with the fetched JSON data
  /// @param data JSON data
  void ReadData(std::string &&data);

  /// @brief Parses the given fetched JSON data and fills the
  /// AirQualityMeasurement data structure with appropriate data
  /// @return Returns a valid vector of type AirQualityMeasurement
  std::optional<std::vector<AirQualityMeasurement>> Parse();

private:
  void RemoveRedundantCharacters();
  void ReplaceSpecialCharacters();
  void AssignAirParametersValues();
  std::pair<std::time_t, std::string>
  ConvertFromEpochToStandardTime(std::string &epoch_time);

  std::vector<AirQualityMeasurement> air_quality_measurements_;
  std::string data_buffer_{""};
  std::array<char, 5> redundant_characters{{'[', '{', '}', ']', '\"'}};

  /// @section For testing purposes
protected:
  [[nodiscard]] const std::string &GetDataBuffer() const;
  [[nodiscard]] const std::vector<AirQualityMeasurement> &
  GetAirQualityMeasurements() const;
};

#endif // AIRQUALITYAPP_JSON_PARSER_H
