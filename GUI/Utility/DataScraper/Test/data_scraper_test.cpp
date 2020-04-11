// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include "../data_scraper.h"

#include <gtest/gtest.h>
#include <memory>

class DataScraperTestFixture : public ::testing::Test {
protected:
  // Default constructor
  DataScraperTestFixture() : data_scraper(std::make_unique<DataScraper>()) {}

  std::unique_ptr<DataScraper> data_scraper;
  const std::string default_url_{"http://iszz.azo.hr/iskzl/rs/podatak/export/"
                                 "json?postaja=160&polutant=3&tipPodatka=0&"
                                 "vrijemeOd=04.04.2020&vrijemeDo=04.04.2020"};
};

TEST_F(
    DataScraperTestFixture,
    GivenDefaultDataScraperObject_WhenInstatiated_ThenInstatiationSuccessful) {

  EXPECT_TRUE(data_scraper);
}

TEST_F(DataScraperTestFixture,
       GivenNonExistingUrl_WhenFetchingData_ThenNoValidDataFound) {

  data_scraper->SetUrl("NotGood.what");
  data_scraper->FetchData();

  ASSERT_FALSE(data_scraper->GetFetchedData().empty());
  EXPECT_EQ(data_scraper->GetFetchedData(), "No valid data found");
}

TEST_F(DataScraperTestFixture, GivenValidUrl_WhenFetchingData_ThenDataIsFetched) {

  data_scraper->SetUrl(default_url_);
  data_scraper->FetchData();

  ASSERT_FALSE(data_scraper->GetFetchedData().empty());
  EXPECT_NE(data_scraper->GetFetchedData(), "No valid data found");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
