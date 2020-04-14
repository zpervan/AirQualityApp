// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

/******************************************************************************/
/**  Documentation: https://curl.haxx.se/libcurl/c/libcurl-tutorial.html     **/
/******************************************************************************/

#ifndef AIRQUALITYAPP_DATA_SCRAPER_H
#define AIRQUALITYAPP_DATA_SCRAPER_H

#include "../DataTypes/data_types.h"
#include <curl/curl.h>
#include <string>

// TODO: Set URL with given pollutant and date range (remove hardcoded addresses)

/// @brief Fetches data from the given URL
class DataScraper {
public:
  DataScraper() = default;
  ~DataScraper() = default;

  /// @brief Collects the data from an given URL (website)
  void FetchData();

  /// @brief Set the URL from which data should be fetched
  void SetUrl(const std::string &url);

  /// @brief Sets the date span for data collection
  void SetDate(const std::string &from, const std::string &to);

  /// @brief Get the data acquired from the given URL
  [[nodiscard]] const std::string &GetFetchedData() const;

private:
  void FetchDataFromUrl();
  static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                                   void *userp);
  UrlComponents url_components_;
  CURL *curl_{nullptr};
  CURLcode res_;
  std::string url_{""};
  std::string fetched_data_{""};

  // For testing
protected:
  std::string GetUrl() { return url_; }
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
