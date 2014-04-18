// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>

// Tests mean for integers
void test_mean_integer() {
}

// Tests mean for doubles
void test_mean_double() {
	int n = 5;
	double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double m = mean(a, n);
	if (m != 3.0)
		throw failed;
}

// Tests mean for template iterators
void test_mean_iterator() {
	
	// Substitute double array
	double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double m1 = mean(std::begin(a), std::end(a), double_additive_identity);
	if (m1 != 3.0)
		throw failed;

	// Substitute float array
	float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double m2 = mean(std::begin(b), std::end(b), float_additive_identity);
	if (m2 != 3.0)
		throw failed;

	// Substitute with double vector
	std::vector<double> v1;
	v1.push_back(1.0);
	v1.push_back(2.0);
	v1.push_back(3.0);
	v1.push_back(4.0);
	v1.push_back(5.0);
	double m3 = mean(v1.begin(), v1.end(), double_additive_identity);
	if (m3 != 3.0)
		throw failed;
}

int main() {
  int err = 0;
  err += test(test_mean_integer);
  err += test(test_mean_double);
  err += test(test_mean_iterator);
  return err;
}
