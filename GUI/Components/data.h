// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_DATA_H
#define AIRQUALITYAPP_DATA_H

#include "../Utility/DateTime/date_time.h"

#include <string>
#include <vector>

namespace Date {
static DateTime::DateFormats dates{};
static std::string current_date{};
}

namespace Pollutants {
static std::vector<float> carbon_monoxide_values{};
static std::vector<float> benzene_values{};
static std::vector<float> ozone_values{};

static std::string carbon_monoxide_last_fetch{"Not yet fetched"};
static std::string benzene_last_fetch{"Not yet fetched"};
static std::string ozone_last_fetch{"Not yet fetched"};
} // namespace Pollutants

#endif // AIRQUALITYAPP_DATA_H
