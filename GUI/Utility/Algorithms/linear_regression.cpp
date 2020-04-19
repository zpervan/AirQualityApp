// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#include "linear_regression.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>

void LinearRegression::SetXValues(const std::vector<float> &x_values) {
  x_values_ = x_values;
}

void LinearRegression::SetYValues(const std::vector<float> &y_values) {
  y_values_ = y_values;
}

void LinearRegression::CalculateLeastSquareRegressionCoeffs() {
  TrySetDataValueCount();
  CalculateXSquaredValues();
  CalculateXYProducts();
  CalculateSums();
  CalculateSlope();
  CalculateIntercept();
}

std::vector<float> LinearRegression::CalculateLeastSquareRegression(
    const std::vector<float> &x_values) {
  std::vector<float> calculated_values;
  calculated_values.reserve(x_values.size());

  std::transform(
      x_values.begin(), x_values.end(), std::back_inserter(calculated_values),
      [&](const float x_value) { return slope_ * x_value + intercept_; });

  ClearData();
  return calculated_values;
}

void LinearRegression::TrySetDataValueCount() {
  x_values_.size() == y_values_.size()
      ? data_value_count_ = x_values_.size()
      : throw std::out_of_range("X and Y values are not the same size!");
}

void LinearRegression::CalculateXSquaredValues() {
  squared_values_.reserve(x_values_.size());
  std::transform(x_values_.begin(), x_values_.end(),
                 std::back_inserter(squared_values_),
                 [](const float x) { return std::pow(x, 2); });
}

void LinearRegression::CalculateXYProducts() {
  product_values_.reserve(x_values_.size());
  std::transform(x_values_.begin(), x_values_.end(), y_values_.begin(),
                 std::back_inserter(product_values_), std::multiplies<float>());
}

void LinearRegression::CalculateSums() {
  SumValues(x_values_, sum_x_value_);
  SumValues(y_values_, sum_y_value_);
  SumValues(squared_values_, sum_squared_value_);
  SumValues(product_values_, sum_product_value_);
}

void LinearRegression::SumValues(const std::vector<float> &values,
                                 float &sum_value) {
  std::for_each(values.begin(), values.end(), [&](float n) { sum_value += n; });
}

void LinearRegression::CalculateSlope() {
  slope_ =
      ((data_value_count_ * sum_product_value_) - (sum_x_value_ * sum_y_value_)) /
      ((data_value_count_ * sum_squared_value_) - std::pow(sum_x_value_, 2));
}

void LinearRegression::CalculateIntercept() {
  intercept_ = (sum_y_value_ - (slope_ * sum_x_value_)) / data_value_count_;
}

void LinearRegression::ClearData() {
  squared_values_.resize(0);
  product_values_.resize(0);

  data_value_count_ = 0;
  sum_x_value_ = 0;
  sum_y_value_ = 0;
  sum_squared_value_ = 0;
  sum_product_value_ = 0;
  slope_ = 0;
  intercept_ = 0;
}

const std::vector<float> &LinearRegression::GetXValues() const {
  return x_values_;
}

const std::vector<float> &LinearRegression::GetYValues() const {
  return y_values_;
}

const std::vector<float> &LinearRegression::GetSquaredValues() const {
  return squared_values_;
}

const std::vector<float> &LinearRegression::GetProductValues() const {
  return product_values_;
}

float LinearRegression::GetSumXValue() const { return sum_x_value_; }

float LinearRegression::GetSumYValue() const { return sum_y_value_; }

float LinearRegression::GetSumSquaredValue() const {
  return sum_squared_value_;
}

float LinearRegression::GetSumProductValue() const {
  return sum_product_value_;
}

float LinearRegression::GetSlopeValue() const { return slope_; }

std::size_t LinearRegression::GetDataValueCount() const {
  return data_value_count_;
}

float LinearRegression::GetIntercept() const { return intercept_; }
