// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_PROCESS_DATA_H
#define AIRQUALITYAPP_PROCESS_DATA_H

#include "config.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
// TODO: No resize in every iteration!!
// TODO: Initial data fetching (before the counter triggers)

// Forward declarations
void ProcessCarbonMonoxide();
void ProcessBenzene();
void ProcessOzone();
std::pair<float, float> CalculateMinMaxPlotScaling(std::vector<float> &values);

void ProcessData() {
  while (1) {
    if (!Config::DataFetching::enable_data_fetching) {
      std::cout << "Data fetching is disabled." << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      continue;
    }

    std::cout << "Processing data..." << std::endl;

    if (Config::Window::enable_carbon_monoxide) ProcessCarbonMonoxide();
    if (Config::Window::enable_benzene) ProcessBenzene();
    if (Config::Window::enable_ozone) ProcessOzone();

    std::cout << "Processing DONE!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void ProcessCarbonMonoxide() {

  std::cout << "Processing CO data..." << std::endl;
  Utility::sDataScraper->SetUrl(
      "http://iszz.azo.hr/iskzl/rs/podatak/export/"
      "json?postaja=160&polutant=3&tipPodatka=0&vrijemeOd=13.04.2020&vrijemeDo="
      "13.04.2020");

  Utility::sDataScraper->FetchData();
  auto fetched_data = Utility::sDataScraper->GetFetchedData();
  Utility::sJsonParser->ReadData(fetched_data.data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Gas::carbon_monoxide_last_fetch = Utility::air_quality_measurements.back().standard_time;
  Gas::carbon_monoxide_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Gas::carbon_monoxide_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::carbon_monoxide_minmax_scaling =
      CalculateMinMaxPlotScaling(Gas::carbon_monoxide_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing CO data DONE!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
};

void ProcessBenzene() {
  std::cout << "Processing Benzene data..." << std::endl;
  Utility::sDataScraper->SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                "json?postaja=160&polutant=32&tipPodatka=0&"
                                "vrijemeOd=13.04.2020&vrijemeDo=13.04.2020");

  Utility::sDataScraper->FetchData();
  auto fetched_data = Utility::sDataScraper->GetFetchedData();
  Utility::sJsonParser->ReadData(fetched_data.data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Gas::benzene_last_fetch = Utility::air_quality_measurements.back().standard_time;
  Gas::benzene_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Gas::benzene_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::benzene_minmax_scaling =
      CalculateMinMaxPlotScaling(Gas::benzene_values);


  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Benzene data DONE!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void ProcessOzone() {
  std::cout << "Processing Ozone data..." << std::endl;
  Utility::sDataScraper->SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                "json?postaja=160&polutant=31&tipPodatka=0&"
                                "vrijemeOd=13.04.2020&vrijemeDo=13.04.2020");

  Utility::sDataScraper->FetchData();
  auto fetched_data = Utility::sDataScraper->GetFetchedData();
  Utility::sJsonParser->ReadData(fetched_data.data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Gas::ozone_values.resize(0);
  Gas::ozone_last_fetch = Utility::air_quality_measurements.back().standard_time;

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Gas::ozone_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::ozone_minmax_scaling =
      CalculateMinMaxPlotScaling(Gas::ozone_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Ozone data DONE!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

std::pair<float, float> CalculateMinMaxPlotScaling(std::vector<float> &values) {
  float min_element = *std::min_element(values.begin(), values.end());
  float max_element = *std::max_element(values.begin(), values.end());

  // Sometimes the measurement have the same values and it's shown as there are
  // no values at all. This is just offseting the plot to see the values.
  if (min_element == max_element) {
    max_element += 1.f;
  }

  // Because the minimum value is not shown in the plot, offset it for 1 unit
  (min_element - 1) < 0 ? min_element = 0 : min_element -= 1.f;

  return {min_element, max_element};
}

#endif // AIRQUALITYAPP_PROCESS_DATA_H
