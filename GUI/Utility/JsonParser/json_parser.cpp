// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "json_parser.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>

void JsonParser::ReadData(std::string &&data) {
  data_buffer_.clear();
  data_buffer_ = std::move(data);
}

std::optional<std::vector<AirQualityMeasurement>> JsonParser::Parse() {
  air_quality_measurements_.resize(0);

  RemoveRedundantCharacters();
  ReplaceSpecialCharacters();
  AssignAirParametersValues();

  if (air_quality_measurements_.empty()) {
    return std::nullopt;
  }

  return air_quality_measurements_;
}

void JsonParser::RemoveRedundantCharacters() {
  for (const char &redundant_character : redundant_characters) {
    data_buffer_.erase(std::remove(data_buffer_.begin(), data_buffer_.end(),
                                   redundant_character),
                       data_buffer_.end());
  }
}

void JsonParser::ReplaceSpecialCharacters() {
  std::replace(data_buffer_.begin(), data_buffer_.end(), ':', ' ');
  std::replace(data_buffer_.begin(), data_buffer_.end(), ',', ' ');
}

void JsonParser::AssignAirParametersValues() {
  std::istringstream linestream(data_buffer_);
  std::string key;
  std::string value;

  AirQualityMeasurement air_quality_data;

  while (linestream >> key >> value) {
    if (key == "vrijednost") // value
      air_quality_data.value = std::stof(value);
    if (key == "mjernaJedinica") // unit of measure
      air_quality_data.unit_of_measurement = value;
    if (key == "vrijeme") { // time
      air_quality_data.time = std::stoll(value);
      air_quality_measurements_.emplace_back(air_quality_data);
    }
  }
}

const std::string &JsonParser::GetDataBuffer() const { return data_buffer_; }

const std::vector<AirQualityMeasurement> &
JsonParser::GetAirQualityMeasurements() const {
  return air_quality_measurements_;
}
