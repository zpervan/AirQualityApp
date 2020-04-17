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
#include <map>
#include <string>

/// @brief Fetches data from the given URL
class DataScraper {
public:
  /// @brief Collects the data from an given URL (website)
  void FetchData();

  /// @brief Set the type of pollutant to fetch from the URL
  void SetPollutant(const DataTypes::Pollutant &pollutant);

  /// @brief Sets the date span for data collection
  void SetDate(const std::string &from, const std::string &to);

  /// @brief Get the data acquired from the given URL
  [[nodiscard]] std::optional<std::string> TryGetFetchedData() const;

  // Protected for testing purposes
protected:
  static std::size_t WriteCallback(void *contents, std::size_t size,
                                   std::size_t nmemb, void *userp);

  const std::string GetUrl() { return url_; }
  const std::string GetTodayDate() { return today_date_; }

  void CreateUrl();
  void FetchDataFromUrl();

private:
  UrlComponents url_components_;
  CURL *curl_{nullptr};
  CURLcode res_;
  DataTypes::Pollutant pollutant_{DataTypes::Pollutant::UNKNOWN};

  const std::string empty_fetched_data_{"[]"};

  std::optional<std::string> fetched_data_{""};
  std::string url_{""};
  std::string date_from_{""};
  std::string date_to_{""};
  std::string today_date_{""};
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
