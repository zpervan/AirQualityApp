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

/// @brief Parses the air measurement JSON file and assigns the parsed values to
/// the appropriate data.
class JsonParser {
public:
  /// @brief Fills JsonParser's data buffer with the fetched air measurement
  /// JSON data.
  /// @param data Fetched air measurements data in JSON format
  void ReadData(std::string &&data);

  /// @brief Parses the given fetched air measurement data and fills the
  /// AirQualityMeasurement data structure with the appropriate values
  /// @return Returns a valid vector with assigned AirQualityMeasurement data
  std::optional<std::vector<AirQualityMeasurement>> Parse();

private:
  void RemoveRedundantCharacters();
  void ReplaceSpecialCharacters();
  void AssignAirParametersValues();

  std::vector<AirQualityMeasurement> air_quality_measurements_;
  std::string data_buffer_{""};
  std::array<char, 5> redundant_characters{{'[', '{', '}', ']', '\"'}};

  // For testing purposes
protected:
  const std::string &GetDataBuffer() const;
  const std::vector<AirQualityMeasurement> &GetAirQualityMeasurements() const;
};

#endif // AIRQUALITYAPP_JSON_PARSER_H
