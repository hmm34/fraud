// Heather Michaud

#include "concepts.hpp"
#include "test.hpp"
#include <vector>

// Tests correlation coefficient for integers
void test_correlation_coefficient_integer() {
}

// Tests correlation coefficient for doubles
void test_correlation_coefficient_double() {
	int n = 5;
	double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double r = correlation_coefficient(a, a, n);
	if (!equalWithEpsilon(r, 1.0))
		throw failed;
}

// Test correlation coefficient for template iterators
void test_correlation_coefficient_iterator() {

	// Substitution with double array
	double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double r1 = correlation_coefficient(std::begin(a),
	                                   std::end(a),
	                                   std::begin(a), 
	                                   std::end(a), 
	                                   double_additive_identity);
	if (!equalWithEpsilon(r1, 1.0))
		throw failed;

	// Substitution with float array
	float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float r2 = correlation_coefficient(std::begin(b),
	                                   std::end(b),
	                                   std::begin(b), 
	                                   std::end(b), 
	                                   float_additive_identity);
	if (!equalWithEpsilon(r2, 1.0))
		throw failed;

	// Substitution with double vector
	std::vector<double> v1;
	v1.push_back(1.0);
	v1.push_back(2.0);
	v1.push_back(3.0);
	v1.push_back(4.0);
	v1.push_back(5.0);
	double r3 = correlation_coefficient(v1.begin(),
		                                v1.end(),
		                                v1.begin(),
		                                v1.end(),
		                                double_additive_identity);
	if (!equalWithEpsilon(r3, 1.0))
		throw failed;
}

int main() {
  int err = 0;
  err += test(test_correlation_coefficient_integer);
  err += test(test_correlation_coefficient_double);
  err += test(test_correlation_coefficient_iterator);
  return err;
}
