// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#include "date_time.h"
#include <iostream>

namespace DateTime {

namespace {

const std::size_t expected_epoch_data_size = 13;
inline bool IsEpochDataValid(const std::string &epoch_time) {
  if (epoch_time.empty()) {
    std::cerr << "Epoch time data is empty. No data fetched?" << std::endl;
    return false;
  }
  if (epoch_time.size() != expected_epoch_data_size) {
    std::cerr << "Epoch time data is of size " << epoch_time.size() <<
                     ", but should be 13! Is the fetched data correct?"
              << std::endl;
    return false;
  }
  return true;
}

} // namespace

std::string GetTodayDate() {
  std::time_t time = std::time(0);

  std::ostringstream today_date;
  today_date << std::put_time(std::localtime(&time), "%d.%m.%Y");

  return {today_date.str()};
}

std::optional<std::pair<std::time_t, std::string>>
ConvertFromEpochToStandardTime(std::string &epoch_time) {

  if (!IsEpochDataValid(epoch_time))
    return std::nullopt;

  // The fetched epoch time has 3 additional characters. To return a valid date
  // and time, the fetched epoch time has to be resized
  epoch_time.resize(10);
  std::time_t epoch_time_t = std::stoll(epoch_time);

  std::ostringstream standard_time;
  standard_time << std::put_time(std::localtime(&epoch_time_t),
                                 "%m/%d/%Y %H:%M");

  return std::make_pair(epoch_time_t, standard_time.str());
}

} // namespace DateTime
