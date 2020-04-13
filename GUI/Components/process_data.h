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
std::pair<float, float> GetMinMaxScalingValues(std::vector<float> &values);

void ProcessData() {
  while (1) {
    if (!Config::DataFetching::enable_data_fetching) {
      std::cout << "Data fetching is disabled." << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      continue;
    }

    std::cout << "Processing data..." << std::endl;

    if (Config::Window::enable_carbon_monoxide)
      ProcessCarbonMonoxide();
    if (Config::Window::enable_benzene)
      ProcessBenzene();
    if (Config::Window::enable_ozone)
      ProcessOzone();

    std::cout << "Processing DONE!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void ProcessCarbonMonoxide() {

  std::cout << "Processing CO data..." << std::endl;
  Utility::sDataScraper->SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                "json?postaja=160&polutant=3&tipPodatka=0&"
                                "vrijemeOd=11.04.2020&vrijemeDo=11.04.2020");

  Utility::sDataScraper->FetchData();

  auto fetched_data = Utility::sDataScraper->GetFetchedData();
  Gas::carbon_monoxide_values.resize(0);

  Utility::sJsonParser->ReadData(fetched_data.data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Gas::carbon_monoxide_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::carbon_monoxide_minmax_scaling =
      GetMinMaxScalingValues(Gas::carbon_monoxide_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing CO data DONE!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
};

void ProcessBenzene() {
  std::cout << "Processing Benzene data..." << std::endl;
  Utility::sDataScraper->SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                "json?postaja=160&polutant=32&tipPodatka=0&"
                                "vrijemeOd=11.04.2020&vrijemeDo=11.04.2020");

  Utility::sDataScraper->FetchData();

  auto fetched_data = Utility::sDataScraper->GetFetchedData();

  Utility::sJsonParser->ReadData(fetched_data.data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Gas::benzene_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Gas::benzene_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::benzene_minmax_scaling =
      GetMinMaxScalingValues(Gas::benzene_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Benzene data DONE!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void ProcessOzone() {
  std::cout << "Processing Ozone data..." << std::endl;
  Utility::sDataScraper->SetUrl("http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                "json?postaja=160&polutant=31&tipPodatka=0&"
                                "vrijemeOd=11.04.2020&vrijemeDo=11.04.2020");

  Utility::sDataScraper->FetchData();

  auto fetched_data = Utility::sDataScraper->GetFetchedData();

  Utility::sJsonParser->ReadData(fetched_data.data());
  Utility::air_quality_measurements = Utility::sJsonParser->Parse().value();

  Gas::ozone_values.resize(0);

  for (auto &air_quality_measurement : Utility::air_quality_measurements) {
    Gas::ozone_values.emplace_back(air_quality_measurement.value);
  }

  Config::Plot::ozone_minmax_scaling =
      GetMinMaxScalingValues(Gas::ozone_values);

  Utility::air_quality_measurements.resize(0);
  std::cout << "Processing Ozone data DONE!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

std::pair<float, float> GetMinMaxScalingValues(std::vector<float> &values) {
  const float min_element = *std::min_element(values.begin(), values.end());
  const float max_element = *std::max_element(values.begin(), values.end());

  return {min_element, max_element};
}

#endif // AIRQUALITYAPP_PROCESS_DATA_H
