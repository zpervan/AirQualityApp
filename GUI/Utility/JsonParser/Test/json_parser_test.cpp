// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include <gtest/gtest.h>

#include "../../DataTypes/data_types.h"
#include "../json_parser.h"

class JsonParserTestFixture : protected JsonParser, public ::testing::Test {
protected:
  void CheckAirQualityMeasurementData(const AirQualityMeasurement &actual,
                                      const AirQualityMeasurement &expected) {
    EXPECT_EQ(actual.value, expected.value);
    EXPECT_EQ(actual.unit_of_measurement, expected.unit_of_measurement);
    EXPECT_EQ(actual.epoch_time, expected.epoch_time);
    EXPECT_EQ(actual.standard_time, expected.standard_time);
  }

  std::string default_fetched_data_{
      R"([{"vrijednost":0.6,"mjernaJedinica":"mg/m3","vrijeme":1585868400000}])"};
  AirQualityMeasurement default_air_quality_measurement_data_{
      0.6, "mg/m3", 1585868400, "04/03/2020 01:00 CEST"};
};

TEST_F(JsonParserTestFixture,
       GivenAirQualityMeasurement_WhenDataIsRead_ThenParserDataBufferHasValue) {

  std::string expected_fetched_data{
      R"([{"vrijednost":0.6,"mjernaJedinica":"mg/m3","vrijeme":1585868400000}])"};

  ReadData(std::move(default_fetched_data_));

  ASSERT_FALSE(GetDataBuffer().empty());
  EXPECT_EQ(expected_fetched_data, GetDataBuffer());
}

TEST_F(JsonParserTestFixture,
       GivenInvalidData_WhenDataIsParsed_ThenParsedDataIsEmpty) {

  std::string invalid_data{"Th[s d4]a} i{ n0t G0.d"};

  ReadData(std::move(invalid_data));

  const auto actual_parsed_data = Parse();

  EXPECT_FALSE(actual_parsed_data.has_value());
}

TEST_F(
    JsonParserTestFixture,
    GivenMultipleAirQualityMeasurement_WhenDataIsRead_ThenParserDataBufferIsAssignedWithUniqueData) {

  std::vector<std::string> data{
      {R"([{"vrijednost":0.1,"mjernaJedinica":"mg/m3-1","vrijeme":1}])"},
      {R"([{"vrijednost":0.2,"mjernaJedinica":"mg/m3-2","vrijeme":2}])"}};

  // Duplicated because the "ReadData" function actually moves the data
  // therefore it's empty and the tests fails because it reads an empty string
  // element
  std::vector<std::string> expected_fetched_data{
      {R"([{"vrijednost":0.1,"mjernaJedinica":"mg/m3-1","vrijeme":1}])"},
      {R"([{"vrijednost":0.2,"mjernaJedinica":"mg/m3-2","vrijeme":2}])"}};

  ReadData(std::move(data.at(0)));

  ASSERT_FALSE(GetDataBuffer().empty());
  EXPECT_EQ(expected_fetched_data.at(0), GetDataBuffer());

  ReadData(std::move(data.at(1)));

  ASSERT_FALSE(GetDataBuffer().empty());
  EXPECT_EQ(expected_fetched_data.at(1), GetDataBuffer());
}

TEST_F(
    JsonParserTestFixture,
    GivenValidAirQualityMeasurement_WhenDataIsParsed_ThenValidMeasurementIsAssigned) {

  ReadData(std::move(default_fetched_data_));

  const auto actual_parsed_data = Parse();

  ASSERT_FALSE(actual_parsed_data->empty());

  auto actual_measurements = GetAirQualityMeasurements().back();

  CheckAirQualityMeasurementData(actual_measurements,
                                 default_air_quality_measurement_data_);
}

/// @attention Test is flaky due to various time-zone environment
/// interpretations. Non-deterministic outputs!
TEST_F(
    JsonParserTestFixture,
    DISABLED_GivenValidAirQualityMeasurements_WhenDataIsParsed_ThenValidMeasurementsAreAssigned) {
  std::string fetched_data{
      R"([{"vrijednost":0.1,"mjernaJedinica":"mg/m3-1","vrijeme":1111111111111},{"vrijednost":0.2,"mjernaJedinica":"mg/m3-2","vrijeme":2222222222222}, {"vrijednost":0.3,"mjernaJedinica":"mg/m3-3","vrijeme":3333333333333}])"};

  ReadData(std::move(fetched_data));

  const auto actual_parsed_data = Parse();

  ASSERT_FALSE(actual_parsed_data->empty());

  const auto actual_measurements = GetAirQualityMeasurements();

  const std::array<AirQualityMeasurement, 3> expected_measurements{
      {{0.1, "mg/m3-1", 1111111111, "03/18/2005 02:58 CET"},
       {0.2, "mg/m3-2", 2222222222, "06/02/2040 05:57 CEST"},
       {0.3, "mg/m3-3", 3333333333, "08/18/2075 07:55 CEST"}}};

  for (std::size_t i = 0; i < actual_measurements.size(); i++) {
    CheckAirQualityMeasurementData(actual_measurements.at(i),
                                   expected_measurements.at(i));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
