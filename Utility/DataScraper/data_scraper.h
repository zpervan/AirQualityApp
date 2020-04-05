// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

// TODO: Add doxygen
// TODO: Add tests

#ifndef AIRQUALITYAPP_DATA_SCRAPER_H
#define AIRQUALITYAPP_DATA_SCRAPER_H

#include <string>

class DataScraper {
public:
  /// @brief
  DataScraper() = default;
  ~DataScraper() = default;

  /// @attention As there is no need to copy or move data to another DataScraper
  /// object, the copy and move functionalities will be explicitly deleted
  DataScraper(const DataScraper &data_scraper) = delete;
  DataScraper &operator=(const DataScraper &data_scraper) = delete;
  DataScraper(DataScraper &&data_scraper) = delete;
  DataScraper &operator=(DataScraper &&data_scraper) = delete;

  /// @section
  void FetchAirQualityData();

  /// @section Setter and Getter methods
  const std::string &GetUrl() const;
  void SetUrl(const std::string &url);

private:
  static std::size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
  std::string url_{""};
};

#endif // AIRQUALITYAPP_DATA_SCRAPER_H
