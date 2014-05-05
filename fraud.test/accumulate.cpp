// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>
#include <list>

// Tests accumulate for integers
void test_accumulate_integer() {
}

// Tests accumulate for template iterators
void test_accumulate_iterators() {

  // Substitution with double array
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double s1 = accumulate(std::begin(a), std::end(a), add, 0);
  if (s1 != 15.0)
    throw failed;

  // Substitution with float array
  float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float s2 = accumulate(std::begin(b), std::end(b), add, 0);
  if (s2 != 15.0)
    throw failed;

  // Substitution with double vector
  std::vector<double> v1;
  v1.push_back(1.0);
  v1.push_back(2.0);
  v1.push_back(3.0);
  v1.push_back(4.0);
  v1.push_back(5.0);
  double s3 = accumulate(v1.begin(), v1.end(), add, 0);
  if (s3 != 15.0)
    throw failed;
}

int main() {
  int err = 0;
  err += test(test_accumulate_iterators);
  return err;
}
