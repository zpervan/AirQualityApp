// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#include "../linear_regression.h"

#include "gtest/gtest.h"

class LinearRegressionTestFixture : protected LinearRegression,
                                    public ::testing::Test {
protected:
  LinearRegressionTestFixture() {
    const std::vector<float> x_values{2.0, 3.0, 5.0, 7.0, 9.0};
    const std::vector<float> y_values{4.0, 5.0, 7.0, 10.0, 15.0};

    SetXValues(x_values);
    SetYValues(y_values);

    CalculateLeastSquareRegressionCoeffs();
  };

  const float precision = 1.0e-4;
};

TEST_F(
    LinearRegressionTestFixture,
    GivenArraysWithSameElementSize_WhenGettingDataSize_ThenCorrectValueIsSet) {
  size_t expected_size = 5;

  const auto actual_x_values = GetXValues();
  const auto actual_y_values = GetYValues();

  ASSERT_EQ(actual_x_values.size(), expected_size);
  ASSERT_EQ(actual_y_values.size(), expected_size);
}

TEST_F(
    LinearRegressionTestFixture,
    GivenArraysWithDifferentSize_WhenSettingDataValueCount_ThenThrowOutOfRangeException) {

  const std::vector<float> x_values{1.0, 2.0, 3.0};
  const std::vector<float> y_values{2.0, 3.0};

  SetXValues(x_values);
  SetYValues(y_values);

  EXPECT_THROW(CalculateLeastSquareRegressionCoeffs(), std::out_of_range);
}

TEST_F(
    LinearRegressionTestFixture,
    GivenXYDataPoints_WhenCalculatingSquaredValues_CorrectValuesAreCalculated) {

  const std::vector<float> expected_squared_values{4.0, 9.0, 25.0, 49.0, 81.0};

  const auto actual_squared_values = GetSquaredValues();

  ASSERT_EQ(expected_squared_values.size(), actual_squared_values.size());

  for (size_t i = 0; i < expected_squared_values.size(); i++) {
    EXPECT_EQ(expected_squared_values[i], actual_squared_values[i]);
  }
}

TEST_F(LinearRegressionTestFixture,
       GivenXYDataPoints_WhenCalculatingSumValues_CorrectValuesAreCalculated) {

  const std::vector<float> expected_product_values{8.0, 15.0, 35.0, 70.0,
                                                    135.0};

  const auto actual_product_values = GetProductValues();

  ASSERT_EQ(expected_product_values.size(), actual_product_values.size());

  for (size_t i = 0; i < expected_product_values.size(); i++) {
    EXPECT_EQ(expected_product_values[i], actual_product_values[i]);
  }
}

TEST_F(
    LinearRegressionTestFixture,
    GivenCalculatedValuesAndCoefficients_WhenSumming_ThenCorrectValuesAreCalculated) {
  std::tuple<float, float, float, float> expected_values =
      std::make_tuple(26.0, 41.0, 168.0, 263.0);

  const auto [expected_x_value, expected_y_value, expected_squared_value,
              expected_product_value] = expected_values;

  EXPECT_EQ(expected_x_value, GetSumXValue());
  EXPECT_EQ(expected_y_value, GetSumYValue());
  EXPECT_EQ(expected_squared_value, GetSumSquaredValue());
  EXPECT_EQ(expected_product_value, GetSumProductValue());
}

TEST_F(
    LinearRegressionTestFixture,
    GivenCalculatedAndSummedValues_WhenCalculatingSlope_ThenCorrectSlopeValuesIsCalculated) {
  const float expected_slope_value = 1.5183;

  EXPECT_NEAR(expected_slope_value, GetSlopeValue(), precision);
}

TEST_F(
    LinearRegressionTestFixture,
    GivenCalculatedAndSummedValues_WhenCalculatingIntercept_ThenCorrectInterceptValuesIsCalculated) {

  const float expected_intercept_value = 0.3049;

  EXPECT_NEAR(expected_intercept_value, GetIntercept(), precision);
}

TEST_F(LinearRegressionTestFixture,
       GivenEquation_WhenCalculated_ThenCorrectValuesCalculated) {
  const std::array<float, 5> expected_values{3.3414, 4.8597, 7.8963, 10.9329,
                                              13.9695};
  const std::vector<float> x_values = GetXValues();

  const auto actual_values = CalculateLeastSquareRegression(x_values);

  for (size_t i = 0; i < x_values.size(); i++) {
    EXPECT_NEAR(expected_values[i], actual_values[i], precision);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
