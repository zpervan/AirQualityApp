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

  ImGui::SetWindowSize(Config::Window::window_size);

  ImGui::Text("Select data to visualize:");
  ImGui::Checkbox(" Carbon Monoxide (CO)", &Config::Window::show_carbon_monoxide);
  ImGui::Checkbox(" Benzene", &Config::Window::show_benzene);
  ImGui::Checkbox(" Ozone (O3)", &Config::Window::show_ozone);

  ImGui::End();
}

void ShowCarbonMonoxide();
void ShowBenzene();
void ShowOzone();

// TODO: No resize in every iteration!!
// TODO: Initial data fetching (before the counter triggers)

void ShowHistograms() {
  if (Config::Window::show_carbon_monoxide) ShowCarbonMonoxide();
  if (Config::Window::show_benzene)         ShowBenzene();
  if (Config::Window::show_ozone)           ShowOzone();
}

void ShowCarbonMonoxide() {
  ImGui::Begin("Carbon Monoxide - CO", &Config::Window::show_carbon_monoxide);

  ImGui::PlotHistogram("Histogram", Gas::carbon_monoxide_values.data(),
                       Gas::carbon_monoxide_values.size(), 0, nullptr, 0.0f,
                       1.0f, ImVec2(0, 120));

  ImGui::End();
}

void ShowBenzene() {
  ImGui::Begin("Benzene", &Config::Window::show_benzene);

  ImGui::PlotHistogram("Histogram", Gas::benzene_values.data(),
                       Gas::benzene_values.size(), 0, nullptr, 0.0f, 1.0f,
                       ImVec2(0, 120));

  ImGui::End();
}

void ShowOzone() {
  ImGui::Begin("Ozone", &Config::Window::show_ozone);

  ImGui::PlotHistogram("Histogram", Gas::ozone_values.data(),
                       Gas::ozone_values.size(), 0, nullptr, 0.0f, 1.0f,
                       ImVec2(0, 120));

  ImGui::End();
}

} // namespace Window
#endif // AIRQUALITYAPP_WINDOW_H
