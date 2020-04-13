// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "data_scraper.h"

#include <iostream>

void DataScraper::FetchData() {
  curl_ = curl_easy_init();

  if (curl_) {
    FetchDataFromUrl();

    if (fetched_data_.empty()) {
      fetched_data_ = "No valid data found";
    }
  }
}

void DataScraper::FetchDataFromUrl() {
  fetched_data_.clear();

  curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &fetched_data_);

  res_ = curl_easy_perform(curl_);
  curl_easy_cleanup(curl_);
}

void DataScraper::SetUrl(const std::string &url) { url_ = url; }

const std::string &DataScraper::GetFetchedData() const { return fetched_data_; }

std::size_t DataScraper::WriteCallback(void *contents, size_t size,
                                       size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}
