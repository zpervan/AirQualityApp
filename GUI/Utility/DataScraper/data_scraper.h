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

  /// @attention As there is no need to copy or move data to another DataScraper
  /// object, the copy and move functionalities will be explicitly deleted
  DataScraper(const DataScraper &data_scraper) = delete;
  DataScraper &operator=(const DataScraper &data_scraper) = delete;
  DataScraper(DataScraper &&data_scraper) = delete;
  DataScraper &operator=(DataScraper &&data_scraper) = delete;

  /// @section Various method for fetching data

  /// @brief Collects the data from an given URL (website)
  void FetchData();

  /// @section Setter and Getter methods
  const std::string &GetUrl() const;
  const std::string &GetFetchedData() const;

  void SetUrl(const std::string &url);

private:
  void ReadDataFromUrl();
  static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                                   void *userp);
  CURL *curl_{nullptr};
  CURLcode res_;
  std::string url_{""};
  std::string fetched_data_{""};
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
