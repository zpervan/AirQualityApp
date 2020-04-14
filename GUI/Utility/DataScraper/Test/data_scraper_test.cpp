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
  const std::string default_url_{"http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                 "json?postaja=160&polutant=3&tipPodatka=0&"
                                 "vrijemeOd=04.04.2020&vrijemeDo=04.04.2020"};
};

TEST_F(DataScraperTestFixture,
       GivenNonExistingUrl_WhenFetchingData_ThenNoValidDataFound) {

  SetUrl("NotGood.what");
  FetchData();

  ASSERT_FALSE(GetFetchedData().empty());
  EXPECT_EQ(GetFetchedData(), "No valid data found");
}

TEST_F(DataScraperTestFixture,
       GivenValidUrl_WhenFetchingData_ThenDataIsFetched) {

  SetUrl(default_url_);
  FetchData();

  ASSERT_FALSE(GetFetchedData().empty());
  EXPECT_NE(GetFetchedData(), "No valid data found");
}

TEST_F(
    DataScraperTestFixture,
    GivenValidUrl_WhenFetchingDataMulipleTimes_ThenFetchedDataIsNotAppended) {
  const std::size_t expected_size = 1633;

  SetUrl(default_url_);
  FetchData();

  ASSERT_FALSE(GetFetchedData().empty());
  EXPECT_EQ(expected_size, GetFetchedData().size());

  FetchData();

  ASSERT_FALSE(GetFetchedData().empty());
  EXPECT_EQ(expected_size, GetFetchedData().size());
}

TEST_F(DataScraperTestFixture,
       GivenDateTime_WhenSettingDate_ThenValidUrlWithDateSet) {

  const std::string expected_url{"http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                 "json?postaja=160&polutant=3&tipPodatka=0&"
                                 "vrijemeOd=01.02.2020&vrijemeDo=03.04.2020"};

  const std::string date_from{"01.02.2020"};
  const std::string date_to{"03.04.2020"};

  SetDate(date_from, date_to);

  const std::string actual_url = GetUrl();

  ASSERT_FALSE(actual_url.empty());
  EXPECT_EQ(expected_url, actual_url);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
