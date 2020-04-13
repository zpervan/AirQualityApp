// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

/******************************************************************************/
/**  Documentation: https://curl.haxx.se/libcurl/c/libcurl-tutorial.html     **/
/******************************************************************************/

#ifndef AIRQUALITYAPP_DATA_SCRAPER_H
#define AIRQUALITYAPP_DATA_SCRAPER_H

#include <curl/curl.h>
#include <string>

/// @brief Fetches data from the given URL
class DataScraper {
public:
  DataScraper() = default;
  ~DataScraper() = default;

  /// @brief Collects the data from an given URL (website)
  void FetchData();

  /// @brief Set the URL from which data should be fetched
  void SetUrl(const std::string &url);

  /// @brief Get the data acquired from the given URL
  [[nodiscard]] const std::string &GetFetchedData() const;

private:
  void FetchDataFromUrl();
  static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                                   void *userp);
  CURL *curl_{nullptr};
  CURLcode res_;
  std::string url_{""};
  std::string fetched_data_{""};
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
