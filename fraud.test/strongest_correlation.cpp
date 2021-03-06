// Heather Michaud

#include "concepts.hpp"
#include "composite.hpp"
#include "test.hpp"

// Tests strongest correlation with longest sequence for integers
void test_strongest_correlation_integer() {
}

// Tests strongest correlation with longest sequence for doubles
void test_strongest_correlation_double() {
  int n = 5;
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

  triple<int, int, double> strongest_r = strongest_correlation(a, a, n, 0, 1);
  std::cout << "Found strongest correlation of sequence: "
            << " 1.0, 2.0, 3.0, 4.0, 5.0\n"
            << "from " << strongest_r.m0 << " to " << strongest_r.m1 << ",\n"
            << "which has a correlation coefficient of: "
            << strongest_r.m2 << "\n";
}

// Tests strongest correlation with longest sequence for template iterators
void test_strongest_correlation_iterators() {
  
  double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

  auto strongest_r =
    strongest_correlation(std::begin(a), std::end(a),
                          std::begin(a), std::end(a), 0.0, 1, 0);

  std::cout << "Found strongest correlation of sequence: "
            << "1.0, 2.0, 3.0, 4.0, 5.0\n"
            << "beginning at: " << *strongest_r.m0 << ",\n";

  auto start = strongest_r.m0;
  int length = 0;
  while (start != strongest_r.m1) {
    ++start;
    ++length;
  }
  std::cout << "of length: " << length << ",\n"
            << "which has a correlation coefficient of: "
            << strongest_r.m2 << "\n";
}

int main() {
  int err = 0;
  err += test(test_strongest_correlation_integer);
  err += test(test_strongest_correlation_double);
  err += test(test_strongest_correlation_iterators);
  return err;
}
