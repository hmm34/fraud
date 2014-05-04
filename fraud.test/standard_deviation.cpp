// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>

// Tests standard deviation for integers
void test_standard_deviation_integer() {
}

// Tests standard deviation for doubles
void test_standard_deviation_double() {
  int n = 5;
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double sd = standard_deviation(a, n);
  if (!equalWithEpsilon(sd, 1.58113883008419))
    throw failed;
}

// Tests standard deviation for template iterators
void test_standard_deviation_iterator() {

  // Substitution with double array
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double sd1 = standard_deviation(std::begin(a), std::end(a), 0);
  if (!equalWithEpsilon(sd1, 1.58113883008419))
    throw failed;

  // Substitution with float array
  float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double sd2 = standard_deviation(std::begin(b), std::end(b), 0);
  if (!equalWithEpsilon(sd2, 1.58113883008419))
    throw failed;

  // Substitution with double vector
  std::vector<double> v1;
  v1.push_back(1.0);
  v1.push_back(2.0);
  v1.push_back(3.0);
  v1.push_back(4.0);
  v1.push_back(5.0);
  double sd3 = standard_deviation(v1.begin(), v1.end(), 0);
  if (!equalWithEpsilon(sd3, 1.58113883008419))
    throw failed;
}

int main() {
  int err = 0;
  err += test(test_standard_deviation_integer);
  err += test(test_standard_deviation_double);
  err += test(test_standard_deviation_iterator);
  return err;
}
