// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "json_parser.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>

void JsonParser::ReadData(std::string &&fetched_data) {
  data_buffer_ = std::move(fetched_data);
}

std::vector<AirQualityMeasurement> JsonParser::Parse() {

  RemoveSpecialCharacters();
  ReplaceSpecialCharacters();
  AssignAirParametersValues();

  /// @attention For debug only. Will be removed
  //  PrintData(air_quality_measurements_);

  return air_quality_measurements_;
}

void JsonParser::RemoveSpecialCharacters() {
  for (std::size_t i = 0; i < strlen(redundant_characters); ++i) {
    data_buffer_.erase(std::remove(data_buffer_.begin(), data_buffer_.end(),
                                   redundant_characters[i]),
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
    if (key == "vrijednost")
      air_quality_data.value = std::stod(value);
    if (key == "mjernaJedinica")
      air_quality_data.unit_of_measurement = value;
    if (key == "vrijeme")
    {
      air_quality_data.time = std::stoll(value);
      air_quality_measurements_.emplace_back(air_quality_data);
    }
  }
}

const std::string &JsonParser::GetDataBuffer() const { return data_buffer_; }
void JsonParser::SetDataBuffer(const std::string &data_buffer) {
  data_buffer_ = data_buffer;
}

const std::vector<AirQualityMeasurement> &
JsonParser::GetAirQualityMeasurements() const {
  return air_quality_measurements_;
}

void JsonParser::PrintData(std::vector<AirQualityMeasurement> &data) {
  std::for_each(air_quality_measurements_.begin(),
                air_quality_measurements_.end(),
                [](AirQualityMeasurement &data) {
                  std::cout << data.value << std::endl;
                  std::cout << data.unit_of_measurement << std::endl;
                  std::cout << data.time << std::endl;
                });
}
