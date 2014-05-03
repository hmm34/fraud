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

template<Real R, Real T>
bool inline equalWithEpsilon(R result_r, T expected) {
	T epsilon = T(0.0000000001);
  T result = T(result_r);
	if (abs(result - expected) < epsilon)
		return true;
	return false;
}

#endif
