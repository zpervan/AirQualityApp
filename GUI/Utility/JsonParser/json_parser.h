// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_JSON_PARSER_H
#define AIRQUALITYAPP_JSON_PARSER_H

#include "../DataTypes/data_types.h"

#include <string>
#include <vector>

// TODO: Add GetParsedData function?
// TODO: Better name than JsonParser?
// TODO: Handle faulty fetched data
// TODO: Epoch conversion to date should be done here

/// @brief Parses the fetched JSON file from the given URL and assigns the values.
class JsonParser {
public:
  JsonParser() = default;
  void ReadData(std::string &&fetched_data);
  std::vector<AirQualityMeasurement> Parse();

  const std::string &GetDataBuffer() const;
  const std::vector<AirQualityMeasurement> &GetAirQualityMeasurements() const;
  void SetDataBuffer(const std::string &data_buffer);

private:
  void RemoveSpecialCharacters();
  void ReplaceSpecialCharacters();
  void AssignAirParametersValues();

  void PrintData(std::vector<AirQualityMeasurement> &data);

  std::vector<AirQualityMeasurement> air_quality_measurements_;
  std::string data_buffer_{""};
  const char redundant_characters[6]{"[{}]\""};
};

#endif // AIRQUALITYAPP_JSON_PARSER_H
