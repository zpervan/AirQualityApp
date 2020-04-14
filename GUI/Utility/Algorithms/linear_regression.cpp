// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#include "linear_regression.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>

LinearRegression &
LinearRegression::operator=(const LinearRegression &rhs) {
  x_values_ = rhs.x_values_;
  y_values_ = rhs.y_values_;
  squared_values_ = rhs.squared_values_;
  product_values_ = rhs.product_values_;

  sum_x_value_ = rhs.sum_x_value_;
  sum_y_value_ = rhs.sum_y_value_;
  sum_squared_value_ = rhs.sum_squared_value_;
  sum_product_value_ = rhs.sum_product_value_;

  data_value_count_ = rhs.data_value_count_;

  slope_ = rhs.slope_;
  intercept_ = rhs.intercept_;

  return *this;
}

LinearRegression &
LinearRegression::operator=(LinearRegression &&linear_regression) {
  *this = linear_regression;
  return *this;
}

void LinearRegression::CalculateLeastSquareRegressionCoeffs() {
  TrySetDataValueCount();
  CalculateXSquaredValues();
  CalculateXYProducts();
  CalculateSums();
  CalculateSlope();
  CalculateIntercept();
}

std::vector<double> LinearRegression::CalculateLeastSquareRegression(
    const std::vector<int> &x_values) {
  std::vector<double> calculated_values;
  calculated_values.reserve(x_values.size());

  std::transform(
      x_values.begin(), x_values.end(), std::back_inserter(calculated_values),
      [&](const int x_value) { return slope_ * x_value + intercept_; });

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
                 [](const int x) { return std::pow(x, 2); });
}

void LinearRegression::CalculateXYProducts() {
  product_values_.reserve(x_values_.size());
  std::transform(x_values_.begin(), x_values_.end(), y_values_.begin(),
                 std::back_inserter(product_values_), std::multiplies<int>());
}

void LinearRegression::CalculateSums() {
  sum_x_value_ = std::accumulate(x_values_.begin(), x_values_.end(), 0);
  sum_y_value_ = std::accumulate(y_values_.begin(), y_values_.end(), 0);
  sum_squared_value_ =
      std::accumulate(squared_values_.begin(), squared_values_.end(), 0);
  sum_product_value_ =
      std::accumulate(product_values_.begin(), product_values_.end(), 0);
}

void LinearRegression::CalculateSlope() {
  slope_ =
      (data_value_count_ * sum_product_value_ - (sum_x_value_ * sum_y_value_)) /
      (data_value_count_ * sum_squared_value_ - std::pow(sum_x_value_, 2));
}

void LinearRegression::CalculateIntercept() {
  intercept_ = (sum_y_value_ - slope_ * sum_x_value_) / data_value_count_;
}

const std::vector<int> &LinearRegression::GetXValues() const {
  return x_values_;
}

const std::vector<int> &LinearRegression::GetYValues() const {
  return y_values_;
}

const std::vector<int> &LinearRegression::GetSquaredValues() const {
  return squared_values_;
}

const std::vector<int> &LinearRegression::GetProductValues() const {
  return product_values_;
}

int LinearRegression::GetSumXValue() const { return sum_x_value_; }

int LinearRegression::GetSumYValue() const { return sum_y_value_; }

int LinearRegression::GetSumSquaredValue() const { return sum_squared_value_; }

int LinearRegression::GetSumProductValue() const { return sum_product_value_; }

double LinearRegression::GetSlopeValue() const { return slope_; }
int LinearRegression::GetDataValueCount() const { return data_value_count_; }
double LinearRegression::GetIntercept() const { return intercept_; }
