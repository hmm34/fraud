// Heather Michaud

#ifndef ORBIT_HPP
#define ORBIT_HPP

#include "concepts.hpp"
#include "composite.hpp"

// Returns the least number of transformations for x to reach y.
//
// Precondition: y is reachable from x under f.
template<Regular T, typename F>
  requires Transform<F, T>()
Distance_type<F> distance(T x, T y, F f) {
  Distance_type<F> n = 0;
  while (x != y) {
    x = f(x);
    ++n;
  }
  return n;
}

#endif
