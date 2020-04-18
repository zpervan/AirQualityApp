// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

/*********************************************************************/
/** Epoch conversion validated with https://www.epochconverter.com/ **/
/*********************************************************************/

#include "../date_time.h"

#include <gtest/gtest.h>

TEST(DateTimeTest, GivenValidEpochTime_WhenConverted_TheCorrectDateReturned) {

  std::string epoch_date{"1587198738000"};

  const std::time_t expected_epoch{1587198738};
  const std::string expected_date{"04/18/2020 10:32 CEST"};

  const auto actual_converted_data =
      DateTime::TryConvertFromEpochToStandardTime(epoch_date);

  EXPECT_EQ(expected_epoch, actual_converted_data->first);
  EXPECT_EQ(expected_date, actual_converted_data->second);
}

TEST(DateTimeTest, GivenNoEpochTime_WhenConverted_TheCorrectDateReturned) {

  std::array<std::string, 3> invalid_epoch_data{"", "0000",
                                                "0000000000000000000000000"};

  for (auto &data : invalid_epoch_data) {
    ASSERT_FALSE(DateTime::TryConvertFromEpochToStandardTime(data).has_value());
  }
}

TEST(DateTimeTest,
     GivenRangeToAcquireDays_WhenPopulatingDates_ThenCorrectDatesReturned) {

  const std::size_t days_range = 4;
  const std::time_t epoch_from_date = 1587213553;
  const std::array<DateTime::DateFormat, 4> expected_populated_dates{
      std::make_pair("18.04.2020", "04/18/2020"),
      std::make_pair("17.04.2020", "04/17/2020"),
      std::make_pair("16.04.2020", "04/16/2020"),
      std::make_pair("15.04.2020", "04/15/2020")};

  const auto actual_populated_dates =
      DateTime::PopulateDates(days_range, epoch_from_date);

  ASSERT_EQ(days_range, actual_populated_dates.size());

  for (std::size_t i = 0; i < days_range; i++) {
    EXPECT_EQ(expected_populated_dates.at(i), actual_populated_dates.at(i));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
