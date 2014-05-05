// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>

// Tests arithmetic_mean for integers
void test_arithmetic_mean_integer() {
}

// Tests arithmetic_mean for doubles
void test_arithmetic_mean_double() {
  int n = 5;
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double m = arithmetic_mean(a, n);
  if (m != 3.0)
    throw failed;
}

// Tests arithmetic_mean for template iterators
void test_arithmetic_mean_iterator() {
  
  // Substitute double array
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double m1 = arithmetic_mean(std::begin(a), std::end(a), 0);
  if (m1 != 3.0)
    throw failed;

  // Substitute with double vector
  std::vector<double> v1;
  v1.push_back(1.0);
  v1.push_back(2.0);
  v1.push_back(3.0);
  v1.push_back(4.0);
  v1.push_back(5.0);
  double m3 = arithmetic_mean(v1.begin(), v1.end(), 0);
  if (m3 != 3.0)
    throw failed;
}

int main() {
  int err = 0;
  err += test(test_arithmetic_mean_integer);
  err += test(test_arithmetic_mean_double);
  err += test(test_arithmetic_mean_iterator);
  return err;
}
