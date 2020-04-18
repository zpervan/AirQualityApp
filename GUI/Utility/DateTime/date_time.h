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

/// @brief Acquires today's date
/// @return Today's date in epoch and standard date
std::pair<std::time_t, std::string> GetTodayDate();

/// @brief Tries to convert epoch data (if available) to standard time
/// @param epoch_time Time represented in Unix time
/// @return A pair containing converted epoch time and standard date-time
std::optional<std::pair<std::time_t, std::string>>
TryConvertFromEpochToStandardTime(std::string &epoch_time);

/// @brief Returns dates in a given range from a relative date
/// @param range Represent how much dates should be acquired/shown
/// @param from_date The date from which the fetching should start
/// @return Returns a vector of dates in standard and epoch date-time
DateFormats PopulateDates(std::size_t range, std::time_t from_date = 0);

} // namespace DateTime

#endif // AIRQUALITYAPP_DATE_TIME_H
