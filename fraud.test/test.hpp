// Heather Michaud

#ifndef TEST_HPP
#define TEST_HPP

#include <stdexcept>
#include <iostream>
#include <math.h>
#include "concepts.hpp"
#include "fraud.hpp"

// This is used to provide simple function diagnostics.
#define failed std::runtime_error(__FUNCTION__)

// This is a test harness. It runs a test and logs any failures.
template<Function F>
  int test(F f) {
    try { 
      f();
    } catch(std::exception& err) {
      std::cerr << "error: " << err.what() << '\n';
      return 1;
    }
    return 0;
  }

// -------------------------------------------------------------------------- //
// Test utilities

bool inline equalWithEpsilon(double result, double expected) {
	double epsilon = 0.00000000000000000000000000001;
	if (abs(result - expected) < epsilon)
		return true;
	return false;
}

double double_additive_identity = 0.0;
float float_additive_identity = 0.0;


#endif
