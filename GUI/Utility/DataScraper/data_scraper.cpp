// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "data_scraper.h"

#include <iomanip>
#include <iostream>
#include <sstream>

void DataScraper::FetchData() {
  CreateUrl();

  curl_ = curl_easy_init();
  if (curl_) {
    FetchDataFromUrl();

    if (fetched_data_->empty()) {
      fetched_data_ = "No valid data found";
    }
  }
}

void DataScraper::FetchDataFromUrl() {
  fetched_data_->clear();

  curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &fetched_data_);

  res_ = curl_easy_perform(curl_);
  curl_easy_cleanup(curl_);
}

void DataScraper::SetUrl(const std::string &url) { url_ = url; }

std::optional<std::string> DataScraper::TryGetFetchedData() const {
  return (fetched_data_ == empty_fetched_data_) ? std::nullopt : fetched_data_;
}

std::size_t DataScraper::WriteCallback(void *contents, size_t size,
                                       size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

void DataScraper::SetDate(const std::string &from, const std::string &to) {
  date_from_ = from;
  date_to_ = to;
}

void DataScraper::SetPollutant(const Pollutant &pollutant) {
  pollutant_ = pollutant;
}

inline bool IsCustomDateNotSet(std::string &from, const std::string &to) {
  return from.empty() || to.empty();
}

void DataScraper::CreateUrl() {

  if (IsCustomDateNotSet(date_from_, date_to_)) {
    date_from_ = date_to_ = todays_date_ = GetTodaysDate();
  }

  const std::string pollutant = pollutant_values_[pollutant_];

  url_ = url_components_.address + url_components_.station + "160" +
         url_components_.pollutant + pollutant + url_components_.data_type +
         "0" + url_components_.date_from + date_from_ +
         url_components_.date_to + date_to_;
}

std::string DataScraper::GetTodaysDate() {
  std::time_t time = std::time(0);

  std::ostringstream today_date;
  today_date << std::put_time(std::localtime(&time), "%d.%m.%Y");

  return {today_date.str()};
}
