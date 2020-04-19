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
#include <numeric>
#include <thread>

// Forward declarations

void ProcessNitrogenDioxide();
void ProcessSulfurDioxide();
void ProcessCarbonMonoxide();
void ProcessBenzene();
void ProcessOzone();
void ProcessTemperature();
std::pair<float, float> CalculateMinMaxPlotScaling(std::vector<float> &values);

// Function definitions

void ProcessData() {
  while (true) {
    if (!Config::DataFetch::enable_air_measurement_fetching) {
      std::cout << "Data fetching is disabled.\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(5000));
      continue;
    }

    std::cout << "Processing data...\n";
    Utility::sAirMeasurementFetcher->SetDate(Date::current_date,
                                             Date::current_date);

    if (Config::Window::show_nitrogen_dioxide)
      ProcessNitrogenDioxide();
    if (Config::Window::show_sulfur_dioxide)
      ProcessSulfurDioxide();
    if (Config::Window::show_carbon_monoxide)
      ProcessCarbonMonoxide();
    if (Config::Window::show_benzene)
      ProcessBenzene();
    if (Config::Window::show_ozone)
      ProcessOzone();
    if (Config::Window::show_temperature)
      ProcessTemperature();

    std::cout << "Processing DONE!\n" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }
}

// Forward declarations of helper functions
bool IsFetchedDataEmpty(const std::optional<std::string> &fetched_data,
                        const Mapping::Pollutant &pollutant);
std::optional<std::string>
FetchDataForPollutant(const Mapping::Pollutant &pollutant);
void ParseFetchedData(std::string &fetched_data);
std::vector<float>
CalculateLinearRegression(const std::vector<float> &y_values);

// Process function definitions
void ProcessNitrogenDioxide() {
  std::cout << "Processing Nitrogen Dioxide [NO2] data...\n";

  const Mapping::Pollutant nitrogen_dioxide_pollutant =
      Mapping::Pollutant::NITROGEN_DIOXIDE;

  auto fetched_data = FetchDataForPollutant(nitrogen_dioxide_pollutant);

  if (IsFetchedDataEmpty(fetched_data, nitrogen_dioxide_pollutant)) {
    return;
  }

  ParseFetchedData(fetched_data.value());

  Pollutants::nitrogen_dioxide_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  Pollutants::nitrogen_dioxide_values.resize(0);
  Pollutants::lg_nitrogen_dioxide_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::nitrogen_dioxide_values.emplace_back(
        air_quality_measurement.value);
  }

  Config::Plot::nitrogen_dioxide_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::nitrogen_dioxide_values);

  Pollutants::lg_nitrogen_dioxide_values =
      CalculateLinearRegression(Pollutants::nitrogen_dioxide_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Nitrogen Dioxide [NO2] data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void ProcessSulfurDioxide() {
  std::cout << "Processing Sulfur Dioxide [SO2] data...\n";

  const Mapping::Pollutant sulfur_dioxide_pollutant =
      Mapping::Pollutant::SULFUR_DIOXIDE;

  auto fetched_data = FetchDataForPollutant(sulfur_dioxide_pollutant);

  if (IsFetchedDataEmpty(fetched_data, sulfur_dioxide_pollutant)) {
    return;
  }

  ParseFetchedData(fetched_data.value());

  Pollutants::sulfur_dioxide_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  Pollutants::sulfur_dioxide_values.resize(0);
  Pollutants::lg_sulfur_dioxide_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::sulfur_dioxide_values.emplace_back(
        air_quality_measurement.value);
  }

  Config::Plot::sulfur_dioxide_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::sulfur_dioxide_values);

  Pollutants::lg_sulfur_dioxide_values =
      CalculateLinearRegression(Pollutants::sulfur_dioxide_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Sulfur Dioxide [SO2] data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void ProcessCarbonMonoxide() {

  std::cout << "Processing Carbon Monoxide [CO] data...\n";

  const Mapping::Pollutant carbon_monoxide =
      Mapping::Pollutant::CARBON_MONOXIDE;

  auto fetched_data = FetchDataForPollutant(carbon_monoxide);

  if (IsFetchedDataEmpty(fetched_data, carbon_monoxide)) {
    return;
  }

  ParseFetchedData(fetched_data.value());

  Pollutants::carbon_monoxide_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  Pollutants::carbon_monoxide_values.resize(0);
  Pollutants::lg_carbon_monoxide_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::carbon_monoxide_values.emplace_back(
        air_quality_measurement.value);
  }

  Config::Plot::carbon_monoxide_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::carbon_monoxide_values);

  Pollutants::lg_carbon_monoxide_values =
      CalculateLinearRegression(Pollutants::carbon_monoxide_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Carbon Monoxide [CO] data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void ProcessBenzene() {
  std::cout << "Processing Benzene data...\n";

  const Mapping::Pollutant benzene_pollutant = Mapping::Pollutant::BENZENE;

  auto fetched_data = FetchDataForPollutant(benzene_pollutant);

  if (IsFetchedDataEmpty(fetched_data, benzene_pollutant)) {
    return;
  }

  ParseFetchedData(fetched_data.value());

  Pollutants::benzene_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  Pollutants::benzene_values.resize(0);
  Pollutants::lg_benzene_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::benzene_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::benzene_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::benzene_values);

  Pollutants::lg_benzene_values =
      CalculateLinearRegression(Pollutants::benzene_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Benzene data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void ProcessOzone() {
  std::cout << "Processing Ozone data...\n";

  const Mapping::Pollutant ozone_pollutant = Mapping::Pollutant::OZONE;

  auto fetched_data = FetchDataForPollutant(ozone_pollutant);

  if (IsFetchedDataEmpty(fetched_data, ozone_pollutant)) {
    return;
  }

  ParseFetchedData(fetched_data.value());

  Pollutants::ozone_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  Pollutants::ozone_values.resize(0);
  Pollutants::lg_ozone_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::ozone_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::ozone_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::ozone_values);

  Pollutants::lg_ozone_values =
      CalculateLinearRegression(Pollutants::ozone_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Ozone data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void ProcessTemperature() {
  std::cout << "Processing Temperature [°C] data...\n";

  const Mapping::Pollutant temperature_flag = Mapping::Pollutant::TEMPERATURE;

  auto fetched_data = FetchDataForPollutant(temperature_flag);

  if (IsFetchedDataEmpty(fetched_data, temperature_flag)) {
    return;
  }

  ParseFetchedData(fetched_data.value());

  Pollutants::temperature_last_fetch =
      Utility::air_quality_measurements.back().standard_time;

  Pollutants::temperature_values.resize(0);
  Pollutants::lg_temperature_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Pollutants::temperature_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::temperature_minmax_scaling =
      CalculateMinMaxPlotScaling(Pollutants::temperature_values);

  Pollutants::lg_temperature_values =
      CalculateLinearRegression(Pollutants::temperature_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Temperature [°C] data DONE!\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
  case Mapping::Pollutant::NITROGEN_DIOXIDE:
    return "Nitrogen Dioxide";
  case Mapping::Pollutant::SULFUR_DIOXIDE:
    return "Sulfur Dioxide";
  case Mapping::Pollutant::CARBON_MONOXIDE:
    return "Carbon Monoxide";
  case Mapping::Pollutant::BENZENE:
    return "Benzene";
  case Mapping::Pollutant::OZONE:
    return "Ozone";
  case Mapping::Pollutant::TEMPERATURE:
    return "Temperature";
  default:
    return "Unknown";
  }
}

bool IsFetchedDataEmpty(const std::optional<std::string> &fetched_data,
                        const Mapping::Pollutant &pollutant) {
  if (!fetched_data.has_value()) {
    const std::string pollutant_string = PollutantAsString(pollutant);
    const std::string error_message =
        pollutant_string + " data empty! Check if API data available";

    std::cerr << error_message << std::endl;

    Pollutants::temperature_last_fetch = error_message;

    return true;
  }
  return false;
}

std::optional<std::string>
FetchDataForPollutant(const Mapping::Pollutant &pollutant) {
  Utility::sAirMeasurementFetcher->SetPollutant(pollutant);
  Utility::sAirMeasurementFetcher->FetchData();
  return Utility::sAirMeasurementFetcher->TryGetFetchedData();
}

void ParseFetchedData(std::string &fetched_data) {
  Utility::sJsonParser->ReadData(std::move(fetched_data.data()));
  Utility::air_quality_measurements =
      std::move(Utility::sJsonParser->Parse().value());
}

std::vector<float>
CalculateLinearRegression(const std::vector<float> &y_values) {

  std::vector<float> x_values(y_values.size());
  std::iota(x_values.begin(), x_values.end(), 0);

  Utility::sLinearRegression->SetXValues(x_values);
  Utility::sLinearRegression->SetYValues(y_values);
  Utility::sLinearRegression->CalculateLeastSquareRegressionCoeffs();

  return Utility::sLinearRegression->CalculateLeastSquareRegression(x_values);
}
#endif // AIRQUALITYAPP_PROCESS_DATA_H
