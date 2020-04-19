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
void ShowSulfurDioxide();
void ShowNitrogenDioxide();
void ShowTemperature();
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
  ImGui::SetWindowSize(Config::Window::data_window_size);

  ImGui::Text("City: Osijek, Croatia");
  ImGui::Checkbox("Fetch data?", &Config::DataFetch::enable_air_measurement_fetching);

  if (Config::DataFetch::enable_air_measurement_fetching) {
    ShowDateComboBox();
  }

  ImGui::Separator();

  ImGui::Text("Select data to visualize:");

  ImGui::Checkbox(" Carbon Monoxide [CO]", &Config::Window::show_carbon_monoxide);
  ImGui::Checkbox(" Benzene [C6H6]", &Config::Window::show_benzene);
  ImGui::Checkbox(" Ozone [O3]", &Config::Window::show_ozone);
  ImGui::Checkbox(" Sulfur Dioxide [SO2]", &Config::Window::show_sulfur_dioxide);
  ImGui::Checkbox(" Nitrogen Dioxide [NO2]", &Config::Window::show_nitrogen_dioxide);
  ImGui::Checkbox(" Temperature [°C]", &Config::Window::show_temperature);

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
  if (Config::Window::show_nitrogen_dioxide)
    ShowNitrogenDioxide();

  if (Config::Window::show_sulfur_dioxide)
    ShowSulfurDioxide();

  if (Config::Window::show_carbon_monoxide)
    ShowCarbonMonoxide();

  if (Config::Window::show_benzene)
    ShowBenzene();

  if (Config::Window::show_ozone)
    ShowOzone();

  if (Config::Window::show_temperature)
    ShowTemperature();
}

void ShowNitrogenDioxide() {
  ImGui::SetNextWindowPos(ImVec2(280, 220), ImGuiCond_FirstUseEver);

  ImGui::Begin("Nitrogen Dioxide [NO2]", &Config::Window::show_nitrogen_dioxide);

  ImGui::PlotHistogram("", Pollutants::nitrogen_dioxide_values.data(),
      Pollutants::nitrogen_dioxide_values.size(), 1.f, nullptr,
      Config::Plot::nitrogen_dioxide_minmax_scaling.first,
      Config::Plot::nitrogen_dioxide_minmax_scaling.second,
      Config::Window::plot_window_size);

  ImGui::Text("%s",
      (Utility::last_fetch + Pollutants::nitrogen_dioxide_last_fetch).c_str());

  ImGui::End();
}

void ShowSulfurDioxide() {
  ImGui::SetNextWindowPos(ImVec2(280, 20), ImGuiCond_FirstUseEver);

  ImGui::Begin("Sulfur Dioxide [SO2]", &Config::Window::show_sulfur_dioxide);

  ImGui::PlotHistogram("", Pollutants::sulfur_dioxide_values.data(),
      Pollutants::sulfur_dioxide_values.size(), 1.f, nullptr,
      Config::Plot::sulfur_dioxide_minmax_scaling.first,
      Config::Plot::sulfur_dioxide_minmax_scaling.second,
      Config::Window::plot_window_size);

  ImGui::Text("%s",
      (Utility::last_fetch + Pollutants::sulfur_dioxide_last_fetch).c_str());

  ImGui::End();
}

void ShowCarbonMonoxide() {
  ImGui::SetNextWindowPos(ImVec2(750, 20), ImGuiCond_FirstUseEver);

  ImGui::Begin("Carbon Monoxide [CO]", &Config::Window::show_carbon_monoxide);

  ImGui::PlotHistogram("", Pollutants::carbon_monoxide_values.data(),
                       Pollutants::carbon_monoxide_values.size(), 100.f,
                       nullptr,
                       Config::Plot::carbon_monoxide_minmax_scaling.first,
                       Config::Plot::carbon_monoxide_minmax_scaling.second,
                       Config::Window::plot_window_size);

  ImGui::Text(
      "%s",
      (Utility::last_fetch + Pollutants::carbon_monoxide_last_fetch).c_str());

  ImGui::End();
}

void ShowBenzene() {
  ImGui::SetNextWindowPos(ImVec2(750, 220), ImGuiCond_FirstUseEver);

  ImGui::Begin("Benzene [C6H6]", &Config::Window::show_benzene);

  ImGui::PlotHistogram("", Pollutants::benzene_values.data(),
                       Pollutants::benzene_values.size(), 1.f, nullptr,
                       Config::Plot::benzene_minmax_scaling.first,
                       Config::Plot::benzene_minmax_scaling.second,
                       Config::Window::plot_window_size);

  ImGui::Text("%s",
              (Utility::last_fetch + Pollutants::benzene_last_fetch).c_str());

  ImGui::End();
}

void ShowOzone() {
  ImGui::SetNextWindowPos(ImVec2(750, 420), ImGuiCond_FirstUseEver);

  ImGui::Begin("Ozone [O3]", &Config::Window::show_ozone);

  ImGui::PlotHistogram("", Pollutants::ozone_values.data(),
                       Pollutants::ozone_values.size(), 1.f, nullptr,
                       Config::Plot::ozone_minmax_scaling.first,
                       Config::Plot::ozone_minmax_scaling.second,
                       Config::Window::plot_window_size);

  ImGui::Text("%s",
              (Utility::last_fetch + Pollutants::ozone_last_fetch).c_str());

  ImGui::End();
}

void ShowTemperature() {
  ImGui::SetNextWindowPos(ImVec2(280, 420), ImGuiCond_FirstUseEver);

  ImGui::Begin("Temperature [°C]", &Config::Window::show_temperature);

  ImGui::PlotHistogram("", Pollutants::temperature_values.data(),
      Pollutants::temperature_values.size(), 1.f, nullptr,
      Config::Plot::temperature_minmax_scaling.first,
      Config::Plot::temperature_minmax_scaling.second,
      Config::Window::plot_window_size);

  ImGui::Text("%s",
      (Utility::last_fetch + Pollutants::temperature_last_fetch).c_str());

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
