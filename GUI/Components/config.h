// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_CONFIG_H
#define AIRQUALITYAPP_CONFIG_H

/// @brief This represents the configuration file for implemented components.
/// All components have their own namespace and configuration variables should
/// be
///

#include "../Utility/DataScraper/data_scraper.h"
#include "../Utility/JsonParser/json_parser.h"
#include "../Utility/ThirdParty/DearImgui/imgui.h"

#include <memory>

namespace Config {
namespace Window {

static std::pair<uint16_t, uint16_t> main_window_size{1280, 720};
static ImVec2 widget_window_size{200.f, 300.f};

static ImGuiComboFlags combo_flags = ImGuiComboFlags_None;
static std::size_t date_range = 10;

static bool enable_carbon_monoxide{false};
static bool enable_benzene{false};
static bool enable_ozone{false};
} // namespace Window

namespace Plot {
static std::pair<float, float> carbon_monoxide_minmax_scaling{0.f, 1.f};
static std::pair<float, float> benzene_minmax_scaling{0.f, 1.f};
static std::pair<float, float> ozone_minmax_scaling{0.f, 1.f};
} // namespace Plot

namespace DataFetching {
static bool enable_data_fetching{true};
} // namespace DataFetching
} // namespace Config

namespace Utility {
static std::unique_ptr<DataScraper> sDataScraper = std::make_unique<DataScraper>();
static std::unique_ptr<JsonParser> sJsonParser = std::make_unique<JsonParser>();
static std::vector<AirQualityMeasurement> air_quality_measurements{};
static std::string last_fetch{"Last update: "};
} // namespace Utility

#endif // AIRQUALITYAPP_CONFIG_H
