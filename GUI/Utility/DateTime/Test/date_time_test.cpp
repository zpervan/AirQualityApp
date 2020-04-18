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
  const std::string expected_date{"04/18/2020 10:32"};

  const auto actual_converted_data =
      DateTime::ConvertFromEpochToStandardTime(epoch_date);

  EXPECT_EQ(expected_epoch, actual_converted_data->first);
  EXPECT_EQ(expected_date, actual_converted_data->second);
}

TEST(DateTimeTest, GivenNoEpochTime_WhenConverted_TheCorrectDateReturned) {

  std::array<std::string, 3> invalid_epoch_data{"", "0000",
                                                "0000000000000000000000000"};

  for (auto &data : invalid_epoch_data) {
    ASSERT_FALSE(DateTime::ConvertFromEpochToStandardTime(data).has_value());
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
