// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_PROCESS_DATA_H
#define AIRQUALITYAPP_PROCESS_DATA_H

#include "config.h"
#include "data.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

// Forward declarations
void ProcessCarbonMonoxide();
void ProcessBenzene();
void ProcessOzone();
std::pair<float, float> CalculateMinMaxPlotScaling(std::vector<float> &values);

void ProcessData() {
  while (true) {
    if (!Config::DataFetch::enable_air_measurement_fetching) {
      std::cout << "Data fetching is disabled.\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(5000));
      continue;
    }

    std::cout << "Processing data...\n";
    Utility::sAirMeasurementFetcher->SetDate(Date::current_date, Date::current_date);

    if (Config::Window::enable_carbon_monoxide)
      ProcessCarbonMonoxide();
    if (Config::Window::enable_benzene)
      ProcessBenzene();
    if (Config::Window::enable_ozone)
      ProcessOzone();

    std::cout << "Processing DONE!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }
}

// Forward declarations
bool IsFetchedDataEmpty(const std::optional<std::string> &fetched_data,
                        const Mapping::Pollutant &pollutant);

void ProcessCarbonMonoxide() {

  std::cout << "Processing CO data...\n";

  Utility::sAirMeasurementFetcher->SetPollutant(
      Mapping::Pollutant::CARBON_MONOXIDE);
  Utility::sAirMeasurementFetcher->FetchData();
  auto fetched_data = Utility::sAirMeasurementFetcher->TryGetFetchedData();

  if (IsFetchedDataEmpty(fetched_data, Mapping::Pollutant::CARBON_MONOXIDE)) {
    return;
  }

  Utility::sJsonParser->ReadData(std::move(fetched_data->data()));
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Pollutants::carbon_monoxide_last_fetch =
      Utility::air_quality_measurements.back().standard_time;
  Pollutants::carbon_monoxide_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::carbon_monoxide_values.emplace_back(
        air_quality_measurement.value);
  }

  Config::Plot::carbon_monoxide_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::carbon_monoxide_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing CO data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
};

void ProcessBenzene() {
  std::cout << "Processing Benzene data...\n";

  Utility::sAirMeasurementFetcher->SetPollutant(Mapping::Pollutant::BENZENE);
  Utility::sAirMeasurementFetcher->FetchData();
  auto fetched_data = Utility::sAirMeasurementFetcher->TryGetFetchedData();

  if (IsFetchedDataEmpty(fetched_data, Mapping::Pollutant::BENZENE)) {
    return;
  }

  Utility::sJsonParser->ReadData(fetched_data->data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Pollutants::benzene_last_fetch =
      Utility::air_quality_measurements.back().standard_time;
  Pollutants::benzene_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::benzene_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::benzene_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::benzene_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Benzene data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void ProcessOzone() {
  std::cout << "Processing Ozone data...\n";

  Utility::sAirMeasurementFetcher->SetPollutant(Mapping::Pollutant::OZONE);
  Utility::sAirMeasurementFetcher->FetchData();
  auto fetched_data = Utility::sAirMeasurementFetcher->TryGetFetchedData();

  if (IsFetchedDataEmpty(fetched_data, Mapping::Pollutant::OZONE)) {
    return;
  }

  Utility::sJsonParser->ReadData(fetched_data->data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Pollutants::ozone_values.resize(0);
  Pollutants::ozone_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::ozone_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::ozone_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::ozone_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Ozone data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

std::pair<float, float> CalculateMinMaxPlotScaling(std::vector<float> &values) {
  float min_element = *std::min_element(values.begin(), values.end());
  float max_element = *std::max_element(values.begin(), values.end());

  // Sometimes the measurements have the same value and it's shown as there are
  // no values at all. This is just offseting the plot to see the values.
  if (min_element == max_element) {
    max_element += 1.f;
  }

  // Because the minimum value is not shown in the plot, offset it for 1 unit
  (min_element - 1) < 0 ? min_element = 0 : min_element -= 1.f;

  return {min_element, max_element};
}

std::string PollutantAsString(const Mapping::Pollutant &pollutant) {
  switch (pollutant) {
  case Mapping::Pollutant::CARBON_MONOXIDE:
    return "Carbon Monoxide";
  case Mapping::Pollutant::BENZENE:
    return "Benzene";
  case Mapping::Pollutant::OZONE:
    return "Ozone";
  default:
    return "Unknown";
  }
}

bool IsFetchedDataEmpty(const std::optional<std::string> &fetched_data,
                        const Mapping::Pollutant &pollutant) {

  if (!fetched_data.has_value()) {
    const std::string pollutant_string = PollutantAsString(pollutant);
    std::cerr << "Fetched " + pollutant_string + " data is empty!\n";
    return true;
  }
  return false;
}

#endif // AIRQUALITYAPP_PROCESS_DATA_H
