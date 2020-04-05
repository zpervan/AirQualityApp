// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "data_scraper.h"

#include <curl/curl.h>
#include <iostream>

void DataScraper::FetchAirQualityData() {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;
  }
}

const std::string &DataScraper::GetUrl() const { return url_; }

void DataScraper::SetUrl(const std::string &url) { url_ = url; }

std::size_t DataScraper::WriteCallback(void *contents, size_t size,
                                       size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}
