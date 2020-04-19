// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_WINDOW_H
#define AIRQUALITYAPP_WINDOW_H

#include "../Utility/AirMeasurementFetcher/air_measurement_fetcher.h"
#include "../Utility/JsonParser/json_parser.h"
#include "../Utility/ThirdParty/DearImgui/imgui.h"
#include "config.h"

#include <algorithm>
#include <cstdio>
#include <thread>
#include <vector>

namespace Window {

// Forward declarations
void ShowDataMenu();
void ShowHistograms();
void ShowCarbonMonoxide();
void ShowBenzene();
void ShowOzone();
void ShowDateComboBox();
void ShowAboutWindow();

// Function definitions
static void ShowWindow() {
  ShowDataMenu();
  ShowHistograms();
  if (Config::Window::show_about_window)
    ShowAboutWindow();
}

void ShowDataMenu() {
  ImGui::Begin("Data");

  ImGui::SetWindowSize(Config::Window::widget_window_size);

  ImGui::Checkbox("Fetch data?",
                  &Config::DataFetch::enable_air_measurement_fetching);

  if (Config::DataFetch::enable_air_measurement_fetching) {
    ShowDateComboBox();
  }

  ImGui::Text("Select data to visualize:");
  ImGui::Checkbox(" Carbon Monoxide (CO)",
                  &Config::Window::enable_carbon_monoxide);
  ImGui::Checkbox(" Benzene", &Config::Window::enable_benzene);
  ImGui::Checkbox(" Ozone (O3)", &Config::Window::enable_ozone);

  ImGui::End();
}

void ShowDateComboBox() {
  ImGui::Text("Select date:");
  static const char *current_item = Date::dates.at(0).second.data();

  if (ImGui::BeginCombo("", current_item, Config::Window::combo_flags)) {

    for (auto &date : Date::dates) {

      bool is_selected;
      (current_item == date.second.data()) ? is_selected = true
                                           : is_selected = false;

      if (ImGui::Selectable(date.second.data(), is_selected)) {
        Date::current_date = date.first;
        current_item = date.second.data();
      }

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }
}

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

  ImGui::PlotHistogram(
      "", Pollutants::carbon_monoxide_values.data(),
      Pollutants::carbon_monoxide_values.size(), 100.f, nullptr,
      Config::Plot::carbon_monoxide_minmax_scaling.first,
      Config::Plot::carbon_monoxide_minmax_scaling.second, ImVec2(350, 120));

  ImGui::Text(
      "%s",
      (Utility::last_fetch + Pollutants::carbon_monoxide_last_fetch).c_str());

  ImGui::End();
}

void ShowBenzene() {
  ImGui::SetNextWindowPos(ImVec2(650, 220), ImGuiCond_FirstUseEver);

  ImGui::Begin("Benzene", &Config::Window::enable_benzene);

  ImGui::PlotHistogram(
      "", Pollutants::benzene_values.data(), Pollutants::benzene_values.size(),
      1.f, nullptr, Config::Plot::benzene_minmax_scaling.first,
      Config::Plot::benzene_minmax_scaling.second, ImVec2(350, 120));

  ImGui::Text("%s",
              (Utility::last_fetch + Pollutants::benzene_last_fetch).c_str());

  ImGui::End();
}

void ShowOzone() {
  ImGui::SetNextWindowPos(ImVec2(650, 420), ImGuiCond_FirstUseEver);

  ImGui::Begin("Ozone - O3", &Config::Window::enable_ozone);

  ImGui::PlotHistogram(
      "", Pollutants::ozone_values.data(), Pollutants::ozone_values.size(), 1.f,
      nullptr, Config::Plot::ozone_minmax_scaling.first,
      Config::Plot::ozone_minmax_scaling.second, ImVec2(350, 120));

  ImGui::Text("%s",
              (Utility::last_fetch + Pollutants::ozone_last_fetch).c_str());

  ImGui::End();
}

void ShowAboutWindow() {
  ImGui::Begin("About", &Config::Window::show_about_window);
  ImGui::Text("Air Quality Monitor");
  ImGui::Separator();
  ImGui::Text(
      "This application show the air quality data for Croatian cities.");
  ImGui::Text("Currently, it only supports the air quality data for Osijek");
  ImGui::End();
}

} // namespace Window
#endif // AIRQUALITYAPP_WINDOW_H
