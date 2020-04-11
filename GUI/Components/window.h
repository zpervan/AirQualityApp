// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_WINDOW_H
#define AIRQUALITYAPP_WINDOW_H

#include "../Utility/ThirdParty/DearImgui/imgui.h"
#include "../Utility/DataScraper/data_scraper.h"

#include "config.h"
#include <algorithm>
#include <cstdio>
#include <vector>

namespace Window {

// Forward declarations
void ShowCheckboxes();
void ShowHistogram();

// Function definitions

static void ShowWindow() {
  ShowCheckboxes();
  ShowHistogram();
}

void ShowCheckboxes() {
  ImGui::Begin("Data");

  ImGui::SetWindowSize(Config::Window::window_size);

  ImGui::Text("Select data to visualize:");
  ImGui::Checkbox(" Carbon Monoxide (CO)",
                  &Config::Window::show_carbon_monoxide);
  ImGui::Checkbox(" Benzen", &Config::Window::show_benzen);
  ImGui::Checkbox(" Ozone (O3)", &Config::Window::show_ozone);

  ImGui::End();
}

void ShowHistogram() {

  ImGui::Begin("Histogram");

  static std::vector<float> values{0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
  static int values_offset = 0;

  {
    float average = 0.0f;

    std::for_each(values.begin(), values.end(),
                  [&average](const float &value) { average += value; });

    average /= values.size();
    char overlay[32];
    sprintf(overlay, "avg %f", average);
  }
  char overlay[32];
  ImGui::PlotLines("Lines", values.data(), values.size(), values_offset,
                   nullptr, -1.0f, 1.0f, ImVec2(0, 80));

  ImGui::PlotHistogram("Histogram", values.data(), values.size(), 0, nullptr,
                       0.0f, 1.0f, ImVec2(0, 120));

  ImGui::End();
}

} // namespace Window
#endif // AIRQUALITYAPP_WINDOW_H
