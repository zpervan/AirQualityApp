// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "json_parser.h"

#include <algorithm>
#include <cstring>
#include <iomanip>
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
      auto [epoch_time, standard_time] = ConvertFromEpochToStandardTime(value);

      air_quality_data.epoch_time = epoch_time;
      air_quality_data.standard_time = standard_time;

      air_quality_measurements_.emplace_back(air_quality_data);
    }
  }
}

const std::string &JsonParser::GetDataBuffer() const { return data_buffer_; }

std::pair<std::time_t, std::string>
JsonParser::ConvertFromEpochToStandardTime(std::string &epoch_time) {
  // As the epoch time given in the JSON has 3 characters extra, we resize the
  // string so it return the valid date and time value
  epoch_time.resize(10);
  std::time_t epoch_time_t = std::stoll(epoch_time);

  std::ostringstream standard_time;
  standard_time << std::put_time(std::localtime(&epoch_time_t),
                                 "%m/%d/%Y %H:%M");

  return {epoch_time_t, standard_time.str()};
}

const std::vector<AirQualityMeasurement> &
JsonParser::GetAirQualityMeasurements() const {
  return air_quality_measurements_;
}
