// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#include "date_time.h"

namespace DateTime
{
std::string GetTodayDate() {
  std::time_t time = std::time(0);

  std::ostringstream today_date;
  today_date << std::put_time(std::localtime(&time), "%d.%m.%Y");

  return {today_date.str()};
}

std::pair<std::time_t, std::string>
ConvertFromEpochToStandardTime(std::string &epoch_time) {
  // The fetched epoch time has 3 additional characters. To return a valid date
  // and time, the fetched epoch time has to be resized
  epoch_time.resize(10);
  std::time_t epoch_time_t = std::stoll(epoch_time);

  std::ostringstream standard_time;
  standard_time << std::put_time(std::localtime(&epoch_time_t),
      "%m/%d/%Y %H:%M");

  return {epoch_time_t, standard_time.str()};
}

}
