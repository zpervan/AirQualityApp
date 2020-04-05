// Udacity capstone project, 2020
// Air Quality in Croatia
// Student: Zvonimir Pervan

#include <gtest/gtest.h>

#include "../../DataTypes/data_types.h"
#include "../json_parser.h"

#include <memory>

class JsonParserTestFixture : public ::testing::Test {
protected:
  JsonParserTestFixture()
      : default_json_parser_(std::make_unique<JsonParser>()) {}
  ~JsonParserTestFixture() = default;

  std::unique_ptr<JsonParser> default_json_parser_;
  std::string default_fetched_data_{
      R"([{"vrijednost":0.6,"mjernaJedinica":"mg/m3","vrijeme":1585868400000}])"};

  AirQualityMeasurement default_air_quality_measurement_data_{0.6, "mg/m3",
                                                              1585868400000};

  void CheckAirQualityMeasurementData(const AirQualityMeasurement &actual,
                                      const AirQualityMeasurement &expected) {
    EXPECT_EQ(actual.value, expected.value);
    EXPECT_EQ(actual.unit_of_measurement, expected.unit_of_measurement);
    EXPECT_EQ(actual.time, expected.time);
  }
};

TEST_F(
    JsonParserTestFixture,
    GivenAirQualityMeasurement_WhenDataIsRead_ThenParserDataBufferIsAssigned) {

  std::string expected_fetched_data{
      R"([{"vrijednost":0.6,"mjernaJedinica":"mg/m3","vrijeme":1585868400000}])"};

  default_json_parser_->ReadData(std::move(default_fetched_data_));

  ASSERT_TRUE(!default_json_parser_->GetDataBuffer().empty());
  EXPECT_EQ(expected_fetched_data, default_json_parser_->GetDataBuffer());
}

TEST_F(
    JsonParserTestFixture,
    GivenValidAirQualityMeasurement_WhenDataIsParsed_ThenValidMeasurementIsAssigned) {

  default_json_parser_->SetDataBuffer(default_fetched_data_);

  ASSERT_TRUE(!default_json_parser_->Parse().empty());

  auto actual_measurements =
      default_json_parser_->GetAirQualityMeasurements().back();

  CheckAirQualityMeasurementData(actual_measurements,
                                 default_air_quality_measurement_data_);
}

TEST_F(
    JsonParserTestFixture,
    GivenValidAirQualityMeasurements_WhenDataIsParsed_ThenValidMeasurementsAreAssigned) {
  std::string fetched_data{
      R"([{"vrijednost":0.1,"mjernaJedinica":"mg/m3-1","vrijeme":11111111111},{"vrijednost":0.2,"mjernaJedinica":"mg/m3-2","vrijeme":22222222222}, {"vrijednost":0.3,"mjernaJedinica":"mg/m3-3","vrijeme":33333333333}])"};

  default_json_parser_->SetDataBuffer(fetched_data);

  ASSERT_TRUE(!default_json_parser_->Parse().empty());

  const auto actual_measurements =
      default_json_parser_->GetAirQualityMeasurements();

  const std::vector<AirQualityMeasurement> expected_measurements{
      {0.1, "mg/m3-1", 11111111111},
      {0.2, "mg/m3-2", 22222222222},
      {0.3, "mg/m3-3", 33333333333}};

  for (std::size_t i = 0; i < actual_measurements.size(); i++) {
    CheckAirQualityMeasurementData(actual_measurements.at(i),
                                   expected_measurements.at(i));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
