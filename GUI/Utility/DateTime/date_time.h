// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_DATE_TIME_H
#define AIRQUALITYAPP_DATE_TIME_H

#include <iomanip>
#include <optional>
#include <string>
#include <vector>

namespace DateTime {

using DateFormats = std::vector<std::pair<std::string, std::string>>;
using DateFormat = std::pair<std::string, std::string>;

std::string GetTodayDate();

std::optional<std::pair<std::time_t, std::string>>
ConvertFromEpochToStandardTime(std::string &epoch_time);

DateFormats PopulateDates(const std::size_t range,
                          const std::time_t from_date = 0);
} // namespace DateTime

#endif // AIRQUALITYAPP_DATE_TIME_H
