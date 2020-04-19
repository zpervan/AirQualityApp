// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_CONFIG_H
#define AIRQUALITYAPP_CONFIG_H

#include "../Utility/AirMeasurementFetcher/air_measurement_fetcher.h"
#include "../Utility/JsonParser/json_parser.h"
#include "../Utility/ThirdParty/DearImgui/imgui.h"

#include <memory>

/// @brief Configuration file for various components of the application.
namespace Config {

namespace Window {

static bool exit_application{false};
static bool show_about_window{false};

static std::pair<uint16_t, uint16_t> main_window_size{1280, 720};
static ImVec2 widget_window_size{200.f, 300.f};

static ImGuiComboFlags combo_flags = ImGuiComboFlags_None;
static std::size_t date_range = 30;

static bool enable_carbon_monoxide{true};
static bool enable_benzene{true};
static bool enable_ozone{true};

} // namespace Window

namespace Plot {

static std::pair<float, float> carbon_monoxide_minmax_scaling{0.f, 1.f};
static std::pair<float, float> benzene_minmax_scaling{0.f, 1.f};
static std::pair<float, float> ozone_minmax_scaling{0.f, 1.f};

} // namespace Plot

namespace DataFetch {

static bool enable_air_measurement_fetching{true};

} // namespace DataFetch

} // namespace Config

#endif // AIRQUALITYAPP_CONFIG_H
