// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef AIRQUALITYAPP_DATE_TIME_H
#define AIRQUALITYAPP_DATE_TIME_H

#include <iomanip>
#include <string>

namespace DateTime {
std::string GetTodayDate();

std::pair<std::time_t, std::string>
ConvertFromEpochToStandardTime(std::string &epoch_time);
} // namespace DateTime

#endif // AIRQUALITYAPP_DATE_TIME_H
