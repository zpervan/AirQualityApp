// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "../data_scraper.h"

#include <gtest/gtest.h>
#include <memory>

class DataScraperTestFixture : protected DataScraper, public ::testing::Test {
protected:
  DataScraperTestFixture() = default;
  ~DataScraperTestFixture() = default;

  const std::string default_date_from_{"01.02.2020"};
  const std::string default_date_to_{"03.04.2020"};
  const std::string default_expected_url_{
      "http://iszz.azo.hr/iskzl/rs/podatak/export/"
      "json?postaja=160&polutant=3&tipPodatka=0&"
      "vrijemeOd=01.02.2020&vrijemeDo=03.04.2020"};
};

TEST_F(DataScraperTestFixture,
       GivenValidPollutant_WhenSetting_ThenUrlWithValidPollutantAndDateSet) {

  SetPollutant(DataTypes::Pollutant::CARBON_MONOXIDE);

  CreateUrl();

  const std::string actual_url = GetUrl();

  ASSERT_FALSE(actual_url.empty());

  const std::string expected_date = GetTodayDate();
  const std::string expected_url = "http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                   "json?postaja=160&polutant=3&tipPodatka=0&"
                                   "vrijemeOd=" +
                                   expected_date +
                                   "&vrijemeDo=" + expected_date;

  EXPECT_EQ(expected_url, actual_url);
}

TEST_F(
    DataScraperTestFixture,
    GivenValidPollutantAndDate_WhenSetting_ThenUrlWithValidPollutantAndDateSet) {

  SetDate(default_date_from_, default_date_to_);
  SetPollutant(DataTypes::Pollutant::CARBON_MONOXIDE);

  CreateUrl();

  const std::string actual_url = GetUrl();

  ASSERT_FALSE(actual_url.empty());
  EXPECT_EQ(default_expected_url_, actual_url);
}

TEST_F(DataScraperTestFixture,
       GivenUrlWithoutDefinedPollutant_WhenFetchingData_ThenNoDataIsReturned) {

  FetchData();

  ASSERT_TRUE(TryGetFetchedData()->empty());

  SetPollutant(DataTypes::Pollutant::UNKNOWN);
  FetchData();

  ASSERT_TRUE(TryGetFetchedData()->empty());
}

TEST_F(
    DataScraperTestFixture,
    GivenValidUrl_WhenFetchingDataMulipleTimes_ThenFetchedDataIsNotAppended) {

  const std::size_t expected_size = 1633;
  const std::string date{"04.04.2020"};

  SetPollutant(DataTypes::Pollutant::CARBON_MONOXIDE);
  SetDate(date, date);

  FetchData();

  ASSERT_FALSE(TryGetFetchedData()->empty());
  EXPECT_EQ(expected_size, TryGetFetchedData()->size());

  FetchData();

  ASSERT_FALSE(TryGetFetchedData()->empty());
  EXPECT_EQ(expected_size, TryGetFetchedData()->size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
