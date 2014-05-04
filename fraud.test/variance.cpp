// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>

// Tests variance for integers
void test_variance_integer() {
}

// Tests variance for doubles
void test_variance_double() {
  int n = 5;
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double v = variance(a, n);
  if (v != 2.5)
    throw failed;
}

// Test variance for template iterators
void test_variance_iterator() {
  // Substitution with double array
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double v1 = variance(std::begin(a), std::end(a), 0);
  if (v1 != 2.5)
    throw failed;

  // Substitution with float array
  float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float v2 = variance(std::begin(b), std::end(b), 0);
  if (v2 != 2.5)
    throw failed;

  // Substitution with double vector
  std::vector<double> sv1;
  sv1.push_back(1.0);
  sv1.push_back(2.0);
  sv1.push_back(3.0);
  sv1.push_back(4.0);
  sv1.push_back(5.0);
  double v3 = variance(sv1.begin(), sv1.end(), 0);
  if (v3 != 2.5)
    throw failed;
}

int main() {
  int err = 0;
  err += test(test_variance_integer);
  err += test(test_variance_double);
  err += test(test_variance_iterator);
  return err;
}
