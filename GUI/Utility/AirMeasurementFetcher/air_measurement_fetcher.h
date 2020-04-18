// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

/******************************************************************************/
/**  Documentation regarding the CURL library:                               **/
/**         https://curl.haxx.se/libcurl/c/libcurl-tutorial.html             **/
/******************************************************************************/

#ifndef AIRQUALITYAPP_DATA_SCRAPER_H
#define AIRQUALITYAPP_DATA_SCRAPER_H

#include "../DataTypes/data_types.h"

#include <curl/curl.h>

#include <map>
#include <string>

/// @brief Contains functionality in which one can set a date and pollutant then
/// fetch the data from the predefined air quality URL
class AirMeasurementFetcher {

public:
  /// @brief Fetch air quality measurement data in JSON file format
  void FetchData();

  /// @brief Set the type of pollutant which should be fetched
  void SetPollutant(const Mapping::Pollutant &pollutant);

  /// @brief Sets the date range from which the data should be fetched
  void SetDate(const std::string &from, const std::string &to);

  /// @brief Try to get the fetched data
  std::optional<std::string> TryGetFetchedData();

private:
  static std::size_t WriteCallback(void *contents, std::size_t size,
                                   std::size_t nmemb, void *userp);

  UrlComponents url_components_;
  CURL *curl_{nullptr};
  CURLcode res_;
  Mapping::Pollutant pollutant_{Mapping::Pollutant::UNKNOWN};

  const std::string empty_fetched_data_{"[]"};

  std::optional<std::string> fetched_data_{""};
  std::string url_{""};
  std::string date_from_{""};
  std::string date_to_{""};
  std::string today_date_{""};

  // For testing purposes
protected:
  std::string GetUrl() { return url_; }
  std::string GetTodayDate() { return today_date_; }

  void CreateUrl();
  void FetchDataFromUrl();
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
