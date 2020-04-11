// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#include "../linear_regression.h"

#include "gtest/gtest.h"

// TODO: Refactor to test only specific methods

class LinearRegressionTest : public ::testing::Test {
protected:
  LinearRegressionTest() {

    std::vector<int> x{2, 3, 5, 7, 9};
    std::vector<int> y{4, 5, 7, 10, 15};

    LinearRegression linear_regression{x, y};
    linear_regression.CalculateLeastSquareRegressionCoeffs();

    linear_regression_ = std::move(linear_regression);
    std::move(x.begin(), x.end(), std::back_inserter(x_default_values_));
  };

  LinearRegression linear_regression_;

  std::vector<int> x_default_values_;
  const double precision = 1.0e-4;
};

TEST_F(LinearRegressionTest,
       GivenXYValues_WhenConstructingTestClass_CorrectXYSize) {
  size_t expected_size = 5;

  const auto actual_x_values = linear_regression_.GetXValues();
  const auto actual_y_values = linear_regression_.GetYValues();

  ASSERT_EQ(actual_x_values.size(), expected_size);
  ASSERT_EQ(actual_y_values.size(), expected_size);
}

TEST_F(
    LinearRegressionTest,
    GivenArraysWithSameSize_WhenSettingDataValueCount_ThenCorrectValueIsSet) {
  const size_t expected_data_count_value = 5;

  EXPECT_EQ(expected_data_count_value, linear_regression_.GetDataValueCount());
}

TEST_F(
    LinearRegressionTest,
    GivenArraysWithDifferentSize_WhenSettingDataValueCount_ThenThrowOutOfRangeException) {

  const std::vector<int> x_values{1, 2, 3};
  const std::vector<int> y_values{2, 3};

  LinearRegression linear_regression{x_values, y_values};

  EXPECT_THROW(linear_regression.CalculateLeastSquareRegressionCoeffs(), std::out_of_range);
}

TEST_F(LinearRegressionTest,
       GivenPoints_WhenCalculatingSquaredValues_CorrectValuesAreCalculated) {

  const std::vector<int> expected_squared_values{4, 9, 25, 49, 81};

  const auto actual_squared_values = linear_regression_.GetSquaredValues();

  ASSERT_EQ(expected_squared_values.size(), actual_squared_values.size());

  for (size_t i = 0; i < expected_squared_values.size(); i++) {
    EXPECT_EQ(expected_squared_values[i], actual_squared_values[i]);
  }
}

TEST_F(LinearRegressionTest,
       GivenPoints_WhenCalculatingSumValues_CorrectValuesAreCalculated) {

  const std::vector<int> expected_product_values{8, 15, 35, 70, 135};

  const auto actual_product_values = linear_regression_.GetProductValues();

  ASSERT_EQ(expected_product_values.size(), actual_product_values.size());

  for (size_t i = 0; i < expected_product_values.size(); i++) {
    EXPECT_EQ(expected_product_values[i], actual_product_values[i]);
  }
}

TEST_F(LinearRegressionTest,
       GivenCalculatedValues_WhenSummingUp_ThenCorrectValuesAreCalculated) {
  std::tuple<int, int, int, int> expected_values =
      std::make_tuple(26, 41, 168, 263);

  const auto [expected_x_value, expected_y_value, expected_squared_value,
              expected_product_value] = expected_values;

  EXPECT_EQ(linear_regression_.GetSumXValue(), expected_x_value);
  EXPECT_EQ(linear_regression_.GetSumYValue(), expected_y_value);
  EXPECT_EQ(linear_regression_.GetSumSquaredValue(), expected_squared_value);
  EXPECT_EQ(linear_regression_.GetSumProductValue(), expected_product_value);
}

TEST_F(
    LinearRegressionTest,
    GivenCalculatedAndSummedValues_WhenCalculatingSlope_ThenCorrectSlopeValuesIsCalculated) {
  const double expected_slope_value = 1.5183;

  EXPECT_NEAR(expected_slope_value, linear_regression_.GetSlopeValue(), precision);
}

TEST_F(
    LinearRegressionTest,
    GivenCalculatedAndSummedValues_WhenCalculatingIntercept_ThenCorrectInterceptValuesIsCalculated) {

  const double expected_intercept_value = 0.3049;

  EXPECT_NEAR(expected_intercept_value, linear_regression_.GetIntercept(), precision);
}

TEST_F(LinearRegressionTest,
       GivenEquation_WhenCalculated_ThenCorrectValuesCalculated) {
  const std::array<double, 5> expected_values{3.3414, 4.8597, 7.8963, 10.9329,
                                              13.9695};

  const auto actual_values =
      linear_regression_.CalculateLeastSquareRegression(x_default_values_);

  for (size_t i = 0; i < x_default_values_.size(); i++) {
    EXPECT_NEAR(expected_values[i], actual_values[i], precision);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
