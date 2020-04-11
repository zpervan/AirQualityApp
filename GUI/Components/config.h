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
static ImVec2 window_size{200.f, 300.f};

static bool data_fetched{false};
static bool show_carbon_monoxide{false};
static bool show_benzen{false};
static bool show_ozone{false};
} // namespace Window
} // namespace Config

namespace Utility {

static std::unique_ptr<DataScraper> sDataScraper = std::make_unique<DataScraper>();
static std::unique_ptr<JsonParser> sJsonParser = std::make_unique<JsonParser>();

static std::vector<AirQualityMeasurement> air_quality_measurements{{0,"",0}};
static std::vector<float> air_values{};

static std::size_t counter{0};

} // namespace Utility

#endif // AIRQUALITYAPP_CONFIG_H
