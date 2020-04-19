// Udacity capstone project, 2020
// Project: Air Quality in Croatia
// Student: Zvonimir Pervan

/******************************************************************************/
/** Least square regression:                                                 **/
/**        https://www.mathsisfun.com/data/least-squares-regression.html     **/
/******************************************************************************/


#ifndef LINEAR_REGRESSION_UTILS_H
#define LINEAR_REGRESSION_UTILS_H

#include <vector>

class LinearRegression {
public:
  /// @brief Set the X values for linear regression coefficient calculations
  /// @param x_values
  void SetXValues(const std::vector<float> &x_values);

  /// @brief Set the X values for linear regression coefficient calculations
  /// @param y_values
  void SetYValues(const std::vector<float> &y_values);

  /// @brief Calculates the linear regression coefficients for given XY points
  /// with the"Least Square Method"
  void CalculateLeastSquareRegressionCoeffs();

  /// @brief Calculates the linear regression line for given X points
  /// Formula: y = slope * x + intercept
  /// @param x_values X points
  /// @return Vector of calculated output points
  std::vector<float>
  CalculateLeastSquareRegression(const std::vector<float> &x_values);

  LinearRegression() = default;

private:
  void ClearData();
  void SumValues(const std::vector<float>& values, float &sum_value);
  std::vector<float> x_values_{};
  std::vector<float> y_values_{};
  std::vector<float> squared_values_{};
  std::vector<float> product_values_{};

  std::size_t data_value_count_{};
  float sum_x_value_{};
  float sum_y_value_{};
  float sum_squared_value_{};
  float sum_product_value_{};
  float slope_{};
  float intercept_{};

  // For testing purposes
protected:
  void CalculateXSquaredValues();
  void CalculateXYProducts();
  void CalculateSums();
  void CalculateSlope();
  void CalculateIntercept();
  void TrySetDataValueCount();

  const std::vector<float> &GetXValues() const;
  const std::vector<float> &GetYValues() const;
  const std::vector<float> &GetSquaredValues() const;
  const std::vector<float> &GetProductValues() const;

  float GetSumXValue() const;
  float GetSumYValue() const;
  float GetSumSquaredValue() const;
  float GetSumProductValue() const;
  std::size_t GetDataValueCount() const;
  float GetSlopeValue() const;
  float GetIntercept() const;
};

#endif // LINEAR_REGRESSION_UTILS_H
