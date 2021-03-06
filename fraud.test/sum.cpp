// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>
#include <list>

// Tests sum for integers
void test_sum_integer() {
}

// Tests sum for doubles
void test_sum_double() {
  int n = 5;
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double s = sum(a, n);
  if (s != 15.0)
    throw failed;
}

// Tests sum for template iterators
void test_sum_iterators() {

  // Substitution with double array
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double s1 = sum(std::begin(a), std::end(a), 0);
  if (s1 != 15.0)
    throw failed;

  // Substitution with float array
  float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float s2 = sum(std::begin(b), std::end(b), 0);
  if (s2 != 15.0)
    throw failed;

  // Substitution with double vector
  std::vector<double> v1;
  v1.push_back(1.0);
  v1.push_back(2.0);
  v1.push_back(3.0);
  v1.push_back(4.0);
  v1.push_back(5.0);
  double s3 = sum(v1.begin(), v1.end(), 0);
  if (s3 != 15.0)
    throw failed;
}

int main() {
  int err = 0;
  err += test(test_sum_integer);
  err += test(test_sum_double);
  err += test(test_sum_iterators);
  return err;
}
