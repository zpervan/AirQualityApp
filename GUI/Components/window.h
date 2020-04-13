// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_WINDOW_H
#define AIRQUALITYAPP_WINDOW_H

#include "../Components/config.h"
#include "../Utility/DataScraper/data_scraper.h"
#include "../Utility/JsonParser/json_parser.h"
#include "../Utility/ThirdParty/DearImgui/imgui.h"

#include "config.h"
#include <algorithm>
#include <cstdio>
#include <thread>
#include <vector>

namespace Window {

// Forward declarations
void ShowCheckboxes();
void ShowHistograms();

// Function definitions

static void ShowWindow() {
  ShowCheckboxes();
  ShowHistograms();
}

void ShowCheckboxes() {
  ImGui::Begin("Data");

  ImGui::SetWindowSize(Config::Window::widget_window_size);

  ImGui::Checkbox("FetchData?", &Config::DataFetching::enable_data_fetching);

  ImGui::Text("Select data to visualize:");
  ImGui::Checkbox(" Carbon Monoxide (CO)",
                  &Config::Window::enable_carbon_monoxide);
  ImGui::Checkbox(" Benzene", &Config::Window::enable_benzene);
  ImGui::Checkbox(" Ozone (O3)", &Config::Window::enable_ozone);

  ImGui::End();
}

// Forward declarations
void ShowCarbonMonoxide();
void ShowBenzene();
void ShowOzone();

void ShowHistograms() {
  if (Config::Window::enable_carbon_monoxide)
    ShowCarbonMonoxide();
  if (Config::Window::enable_benzene)
    ShowBenzene();
  if (Config::Window::enable_ozone)
    ShowOzone();
}

void ShowCarbonMonoxide() {
  ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);

  ImGui::Begin("Carbon Monoxide - CO", &Config::Window::enable_carbon_monoxide);

  ImGui::PlotHistogram("Histogram", Gas::carbon_monoxide_values.data(),
                       Gas::carbon_monoxide_values.size(), 100.f, nullptr,
                       Config::Plot::carbon_monoxide_minmax_scaling.first,
                       Config::Plot::carbon_monoxide_minmax_scaling.second,
                       ImVec2(350, 120));

  ImGui::Text("Last fetching: dd.mm.yyyy, hh:mm");

  ImGui::End();
}

void ShowBenzene() {
  ImGui::SetNextWindowPos(ImVec2(650, 220), ImGuiCond_FirstUseEver);

  ImGui::Begin("Benzene", &Config::Window::enable_benzene);

  ImGui::PlotHistogram(
      "Histogram", Gas::benzene_values.data(), Gas::benzene_values.size(), 1.f,
      nullptr, Config::Plot::benzene_minmax_scaling.first,
      Config::Plot::benzene_minmax_scaling.second, ImVec2(350, 120));

  ImGui::Text("Last fetching: dd.mm.yyyy, hh:mm");

  ImGui::End();
}

void ShowOzone() {
  ImGui::SetNextWindowPos(ImVec2(650, 420), ImGuiCond_FirstUseEver);

  ImGui::Begin("Ozone - O3", &Config::Window::enable_ozone);

  ImGui::PlotHistogram(
      "Histogram", Gas::ozone_values.data(), Gas::ozone_values.size(), 1.f,
      nullptr, Config::Plot::ozone_minmax_scaling.first,
      Config::Plot::ozone_minmax_scaling.second, ImVec2(350, 120));

  ImGui::Text("Last fetching: dd.mm.yyyy, hh:mm");

  ImGui::End();
}

} // namespace Window
#endif // AIRQUALITYAPP_WINDOW_H
