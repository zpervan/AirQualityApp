// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_DATA_H
#define AIRQUALITYAPP_DATA_H

#include "../Utility/DateTime/date_time.h"

#include <string>
#include <vector>

/// @brief Various data storage components of the application.
namespace Date {

static DateTime::DateFormats dates{};
static std::string current_date{};

} // namespace Date

namespace Utility {

static std::unique_ptr<AirMeasurementFetcher> sAirMeasurementFetcher =
    std::make_unique<AirMeasurementFetcher>();
static std::unique_ptr<JsonParser> sJsonParser = std::make_unique<JsonParser>();
static std::vector<AirQualityMeasurement> air_quality_measurements{};
static std::string last_fetch{"Last update: "};

} // namespace Utility

namespace Pollutants {

static std::vector<float> nitrogen_dioxide_values{};
static std::vector<float> sulfur_dioxide_values{};
static std::vector<float> carbon_monoxide_values{};
static std::vector<float> benzene_values{};
static std::vector<float> ozone_values{};
static std::vector<float> temperature_values{};

static std::string nitrogen_dioxide_last_fetch{"Not yet fetched"};
static std::string sulfur_dioxide_last_fetch{"Not yet fetched"};
static std::string carbon_monoxide_last_fetch{"Not yet fetched"};
static std::string benzene_last_fetch{"Not yet fetched"};
static std::string ozone_last_fetch{"Not yet fetched"};
static std::string temperature_last_fetch{"Not yet fetched"};

} // namespace Pollutants

#endif // AIRQUALITYAPP_DATA_H
