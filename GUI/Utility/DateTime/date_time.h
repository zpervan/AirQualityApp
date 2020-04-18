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

using DMY = std::string;
using MDY = std::string;
using DateFormat = std::pair<DMY, MDY>;
using DateFormats = std::vector<DateFormat>;

std::pair<std::time_t, std::string> GetTodayDate();

std::optional<std::pair<std::time_t, std::string>>
ConvertFromEpochToStandardTime(std::string &epoch_time);

DateFormats PopulateDates(std::size_t range, std::time_t from_date = 0);

} // namespace DateTime

#endif // AIRQUALITYAPP_DATE_TIME_H
