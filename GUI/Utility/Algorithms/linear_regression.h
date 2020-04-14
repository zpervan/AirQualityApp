// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

#ifndef LINEAR_REGRESSION_UTILS_H
#define LINEAR_REGRESSION_UTILS_H

#include <vector>

// TODO: Calculate residuals for each point

class LinearRegression {
public:
  /// @brief Utilizes the linear regression utils class and sets the XY values.
  /// @param x X points
  /// @param y Y points
  LinearRegression(const std::vector<int> x, const std::vector<int> y)
      : x_values_(x), y_values_(y){};

  /// @brief Calculates the linear regression coefficients for given XY points
  /// with the"Least Square Method"
  void CalculateLeastSquareRegressionCoeffs();

  /// @brief Calculates the linear regression line for given X points
  /// Formula: y = slope * x + intercept
  /// @param x_values X points
  /// @return Vector of calculated output points
  std::vector<double>
  CalculateLeastSquareRegression(const std::vector<int> &x_values);

  LinearRegression() = default;
  LinearRegression(const LinearRegression &linear_regression) = delete;
  LinearRegression(LinearRegression &&linear_regression) = delete;
  LinearRegression &operator=(const LinearRegression &rhs);
  LinearRegression &operator=(LinearRegression &&linear_regression);

  const std::vector<int> &GetXValues() const;
  const std::vector<int> &GetYValues() const;
  const std::vector<int> &GetSquaredValues() const;
  const std::vector<int> &GetProductValues() const;

  int GetSumXValue() const;
  int GetSumYValue() const;
  int GetSumSquaredValue() const;
  int GetSumProductValue() const;
  int GetDataValueCount() const;
  double GetSlopeValue() const;
  double GetIntercept() const;

private:
  void CalculateXSquaredValues();
  void CalculateXYProducts();
  void CalculateSums();
  void CalculateSlope();
  void CalculateIntercept();
  void TrySetDataValueCount();

  std::vector<int> x_values_{};
  std::vector<int> y_values_{};
  std::vector<int> squared_values_{};
  std::vector<int> product_values_{};

  int sum_x_value_{};
  int sum_y_value_{};
  int sum_squared_value_{};
  int sum_product_value_{};
  size_t data_value_count_{};
  double slope_{};
  double intercept_{};
};

#endif // LINEAR_REGRESSION_UTILS_H
