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

// TODO: Set URL with given pollutant and date range (remove hardcoded
// addresses)

// Forward declarations
class DataScraperTestFixture;

/// @brief Fetches data from the given URL
class DataScraper {
public:
  DataScraper() = default;
  ~DataScraper() = default;

  /// @brief Collects the data from an given URL (website)
  void FetchData();

  /// @brief Set the type of pollutant to fetch from the URL
  void SetPollutant(const Pollutant &pollutant);

  /// @brief Sets the date span for data collection
  void SetDate(const std::string &from, const std::string &to);

  /// @brief Get the data acquired from the given URL
  [[nodiscard]] const std::string &GetFetchedData() const;

  // Protected for testing purposes
protected:
  static std::size_t WriteCallback(void *contents, std::size_t size,
                                   std::size_t nmemb, void *userp);
  void CreateUrl();
  std::string GetTodaysDate();
  void FetchDataFromUrl();
  void SetUrl(const std::string &url);
  std::string GetUrl() { return url_; }

private:
  UrlComponents url_components_;
  CURL *curl_{nullptr};
  CURLcode res_;

  Pollutant pollutant_{Pollutant::UNKNOWN};

  std::string url_{""};
  std::string fetched_data_{""};
  std::string date_from_{""};
  std::string date_to_{""};
  std::string todays_date_{""};

  std::map<Pollutant, std::string> pollutant_values_{
      {Pollutant::UNKNOWN, "0"},
      {Pollutant::CARBON_MONOXIDE, "3"},
      {Pollutant::OZONE, "31"},
      {Pollutant::BENZEN, "32"}};
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
