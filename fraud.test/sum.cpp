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
	double s1 = sum(std::begin(a), std::end(a), double_additive_identity);
	if (s1 != 15.0)
		throw failed;

	// Substitution with float array
	float b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float s2 = sum(std::begin(b), std::end(b), float_additive_identity);
	if (s2 != 15.0)
		throw failed;

	// Substitution with double vector
	std::vector<double> v1;
	v1.push_back(1.0);
	v1.push_back(2.0);
	v1.push_back(3.0);
	v1.push_back(4.0);
	v1.push_back(5.0);
	double s3 = sum(v1.begin(), v1.end(), double_additive_identity);
	if (s3 != 15.0)
		throw failed;

	/*
	// Substitution with double list
	std::list<double> l1(5gi);
	// TODO: WHY THE &*!@ DOES THIS GIVE ME:
	// dyld: lazy symbol binding failed: Symbol not found: __ZNSt8__detail15_List_node_base7_M_hookEPS0_
	// ????????????
	l1.push_back(1.0);
	l1.push_back(2.0);
	l1.push_back(3.0);
	l1.push_back(4.0);
	l1.push_back(5.0);
	double s4 = sum(l1.begin(), l1.end(), double_additive_identity);
	if (s4 != 15.0)
		throw failed;
	*/
}

int main() {
  int err = 0;
  err += test(test_sum_integer);
  err += test(test_sum_double);
  err += test(test_sum_iterators);
  return err;
}
