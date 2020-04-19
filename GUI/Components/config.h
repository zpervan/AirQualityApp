// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_CONFIG_H
#define AIRQUALITYAPP_CONFIG_H

#include "../Utility/ThirdParty/DearImgui/imgui.h"

#include <memory>

/// @brief Configuration file for various components of the application.
namespace Config {

namespace Window {

static bool exit_application{false};
static bool show_about_window{false};

static std::pair<uint16_t, uint16_t> main_window_size{1400, 720};
static ImVec2 data_window_size{200.f, 280.f};
static ImVec2 plot_window_size{450.f, 60.f};

static ImGuiComboFlags combo_flags = ImGuiComboFlags_None;
static std::size_t date_range = 30;

static bool show_carbon_monoxide{true};
static bool show_benzene{true};
static bool show_ozone{true};
static bool show_sulfur_dioxide{true};
static bool show_nitrogen_dioxide{true};
static bool show_temperature{false};

} // namespace Window

namespace Plot {

static std::pair<float, float> nitrogen_dioxide_minmax_scaling{0.f, 1.f};
static std::pair<float, float> sulfur_dioxide_minmax_scaling{0.f, 1.f};
static std::pair<float, float> carbon_monoxide_minmax_scaling{0.f, 1.f};
static std::pair<float, float> benzene_minmax_scaling{0.f, 1.f};
static std::pair<float, float> ozone_minmax_scaling{0.f, 1.f};
static std::pair<float, float> temperature_minmax_scaling{0.f, 1.f};
static std::string text_overlay;
static int value_offset = 0;

} // namespace Plot

namespace DataFetch {

static bool enable_air_measurement_fetching{true};

} // namespace DataFetch

} // namespace Config

#endif // AIRQUALITYAPP_CONFIG_H
