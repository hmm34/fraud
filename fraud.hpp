// Heather Michaud

#ifndef FRAUD_HPP
#define FRAUD_HPP

#include "concepts.hpp"
#include "composite.hpp"
#include "origin/sequence/concepts.hpp"
#include <cmath>
#include <tgmath.h>
#include <iostream>

// ========================================================================= //
// =============== Concrete Implementation: Double Array =================== //
// ========================================================================= //

// Calculates the sum of a list of numbers in an array
double sum(double a[], int n) {
  double s = 0;
  for (int i = 0; i < n; ++i) // O(n)
    s += a[i];
  return s;
}

// Calculates the mean of a list of numbers in an array
double mean(double a[], int n) {
  double s = sum(a, n);  // O(n)
  return s / (double) n;
}

// Calculates the variance in a list of numbers in an array in O(2n)
double variance(double a[], int n) {
  double m = mean(a, n);         // O(n)
  double sumSquares = 0;
  for (int i = 0; i < n; ++i) {  // O(n)
    double diff = a[i] - m;
    sumSquares += (diff * diff);
  }
  return sumSquares / (double) (n - 1);
}

// Calculates the standard deviation in a list of numbers in an array
double standard_deviation(double a[], int n) {
  return sqrt(variance(a, n));
}

// Calculates the correlation coefficient for two lists of numbers in an array
// in O(5n)
double correlation_coefficient(double a[], double b[], int n) {
  double meanA = mean(a, n);                  // O(n)
  double meanB = mean(b, n);                  // O(n)
  double stddevA = standard_deviation(a, n);  // O(2n)
  double stddevB = standard_deviation(b, n);  // O(2n)
  double total = 0;
  for (int i = 0; i < n; ++i) {               // O(n)
    total += ((a[i] - meanA) / stddevA) * ((b[i] - meanB) / stddevB);
  }
  return total / (double) (n - 1);
}

// Calculate the location of the both longest subsequence in an ordered list of
// numbers that has the strongest correlation coefficient, meeting the 
// threshhold minumum sub-sequence length and minumum correlation coefficient
// across the sub-sequence.
triple<int, int, double>
strongest_correlation(double a[], double b[], int n,
                      double minR, int minLength) {
  int startIndex = -1;
  int lastIndex = -1;
  double maxR = minR;
  for (int i = 0; i < n - minLength; ++i) {          // O(n - minLength)
    for (int j = i + minLength; j < n; ++j) {        // O(n - minLength)
      double r = correlation_coefficient(a, b, j-i); // O(5n)
      if ((std::abs(r) > std::abs(maxR)) || 
          (std::abs(r) >= std::abs(maxR) && (j - i) > (lastIndex - startIndex)))
      {
        startIndex = i;
        lastIndex = j;
        maxR = r;
      }
    }
  }
  return triple<int, int, double>(startIndex, lastIndex, maxR);
}



// ========================================================================= //
// =================== Generic Implementation: Iterators =================== //
// ========================================================================= //

// Calculates the sum of a list of numbers, given the first and last iterator
//
// Preconditions:
//   * Addition on Value_type<I> has been defined
//   * Addition is associative
//   * id is the additive identity
//   * last is reachable from first
template<typename I, typename T>
  requires origin::Forward_iterator<I>()
       && Convertible<T, Value_type<I>>()
       && Regular<Value_type<I>>()
Value_type<I> sum(I first, I last, T id) {
  typedef Value_type<I> R;
  R x = R(id);
  while (first != last) {
    x = x + *first;
    ++first;
  }
  return x;
}

// Accumulates an operation on a series of numbers, given the first and last 
// iterator, as well as the operation to be performed.
// Example: Given addition, this calculates the sum
//
// Preconditions:
//   * Op on Value_type<I> has been defined
//   * Op is associative
//   * id is the op identity
//   * last is reachable from first
template<typename I, typename T, typename Op>
  requires origin::Forward_iterator<I>()
       && Convertible<T, Value_type<I>>()
       && Regular<Value_type<I>>()
       && Operation<Op, Value_type<I>, Value_type<I>>()
Value_type<I> accumulate(I first, I last, Op op, T id) {
  typedef Value_type<I> R;
  R x = R(id);
  while (first != last) {
    x = op(x, *first);
    ++first;
  }
  return x;
}

// Calculates the mean of a list of numbers, given the first and last iterator
//
// Preconditions:
//   * Addition on Value_type<I> has been defined
//   * Division on Value_type<I> has been defined
//   * Addition is associative
//   * id is the associative identity
//   * last is reachable from first
template<typename I, typename T>
  requires origin::Forward_iterator<I>()
        && Convertible<T, Value_type<I>>()
        && Regular<Value_type<I>>()
Value_type<I> mean(I first, I last, T id) {
  typedef Value_type<I> R;
  R n = R(id);
  while (first != last) {
    id = id + *first;
    ++n;
    ++first;
  }
  return id / n;
}

// Calculates the variance of a list of numbers, given the first and last
// iterator
//
// Preconditions:
//   * Subtraction on Value_type<I> has been defined
//   * Addition on Value_type<I> has been defined
//   * Multiplication on Value_type<I> has been defined
//   * Division on Value_type<I> has been defined
//   * Addition is associative
//   * id is the additive identity
//   * last is reachable from first
template<typename I, typename T>
  requires origin::Forward_iterator<I>()
        && Convertible<T, Value_type<I>>()
        && Regular<Value_type<I>>()
Value_type<I> variance(I first, I last, T id) {
  typedef Value_type<I> R;
  R count = R(id);
  R var = R(id);
  R m = mean(first, last, id);
  while (first != last) {
    R diff = (*first) - m;
    var += (diff * diff);
    ++count;
    ++first;
  }
  return var / (count - R(1));
}

// Calculates the standard deviation of a list of numbers, given the first and
// last iterator
//
// Preconditions:
//   * Subtraction on Value_type<I> has been defined
//   * Addition on Value_type<I> has been defined
//   * Multiplication on Value_type<I> has been defined
//   * Division on Value_type<I> has been defined
//   * Square root on Value_type<I> has been defined
//   * Addition is associative
//   * id is the additive identity
//   * last is reachable from first
template<typename I, typename T>
  requires origin::Forward_iterator<I>()
        && Convertible<T, Value_type<I>>()
        && Regular<Value_type<I>>()
Value_type<I> standard_deviation(I first, I last, T id) {
  return sqrt(variance(first, last, id));
}

// Calculates the correlation coefficient between two lists of numbers, given 
// the first and last iterator for each list
//
// Preconditions:
//   * The iterators point to lists of the same size
//   * Subtraction on Value_type<I> has been defined
//   * Addition on Value_type<I> has been defined
//   * Multiplication on Value_type<I> has been defined
//   * Division on Value_type<I> has been defined
//   * Square root on Value_type<I> has been defined
//   * Addition is associative
//   * id is the additive identity
//   * lastA is reachable from firstA
//   * lastB is reachable from firstB
template<typename I, typename T>
  requires origin::Forward_iterator<I>()
        && Convertible<T, Value_type<I>>()
        && Regular<Value_type<I>>()
Value_type<I> correlation_coefficient(I firstA, I lastA,
                                      I firstB, I lastB, T id) {
  typedef Value_type<I> R;
  R meanA = mean(firstA, lastA, id);
  R meanB = mean(firstB, lastB, id);
  R stddevA = standard_deviation(firstA, lastA, id);
  R stddevB = standard_deviation(firstB, lastB, id);
  R count = R(id);
  R total = R(id);
  while (firstA != lastA) {
    total += ((*firstA - meanA) / stddevA) * ((*firstB - meanB) / stddevB);
    ++firstA;
    ++firstB;
    ++count;
  }
  return total / (count - R(1));
}



// Calculate the location of the both longest subsequence in an ordered list of
// numbers that has the strongest correlation coefficient, meeting the 
// threshhold minumum sub-sequence length and minumum correlation coefficient
// across the sub-sequence.
//
// Returns a triplet of the starting iterator, the integer length of the
// sub-sequence, and the corresponding strongest correlation coefficient
//
// Preconditions:
//   * The iterators point to lists of the same size
//   * Subtraction on Value_type<I> has been defined
//   * Addition on Value_type<I> has been defined
//   * Multiplication on Value_type<I> has been defined
//   * Division on Value_type<I> has been defined
//   * Square root on Value_type<I> has been defined
//   * Absolute value on Value_type<I> has been defined
//   * Addition is associative
//   * id is the additive identity
//   * lastA is reachable from firstA
//   * lastB is reachable from firstB
//   * -1 <= minR <= 1
//   * 0 < minLength < length of lists
template<typename I, typename T, Integer N>
  requires origin::Forward_iterator<I>()
        && Convertible<T, Value_type<I>>()
        && Convertible<T, N>()
        && Weakly_ordered<Value_type<I>>()
        && Regular<Value_type<I>>()
triple<I, I, Value_type<I>>
strongest_correlation(I firstA, I lastA, I firstB, I lastB,
                    Value_type<I> minR, N minLength, T id) {
  typedef Value_type<I> R;
  N maxLength = minLength;
  R maxR = minR;
  I startIter = lastA;
  I endIter = lastA;

  N len = N(id);
  I tempFirstA = firstA;
  while (tempFirstA != lastA) {
    ++tempFirstA;
    ++len;
  }

  I tempFirstB = firstB;
  tempFirstA = firstA;

  for (N count1 = N(0); count1 <= len - minLength; ++count1) {
    for (N count2 = count1 + minLength; count2 <= len; ++count2) {
      // Increase ending iterators to their appropriate location
      I tempLastB = tempFirstB;
      I tempLastA = tempFirstA;
      N dist = count2 - count1;
      for (N count3 = 0; count3 < dist; ++count3){
        ++tempLastA;
        ++tempLastB;
      }

      // Determine correlation coefficient
      I temp1A = tempFirstA;
      I temp2A = tempLastA;
      I temp1B = tempFirstB;
      I temp2B = tempLastB;
      R r = correlation_coefficient(temp1A, temp2A, temp1B, temp2B, id);

      if ((std::abs(r) > std::abs(maxR)) ||
          (std::abs(r) >= std::abs(maxR) && (dist >= maxLength)))
      {
        startIter = tempFirstA;
        endIter   = tempLastA;
        maxR      = r;
        maxLength = dist;
      }
    }

    // Increase beginning iterators
    ++tempFirstA;
    ++tempFirstB;
  }
  return triple<I, I, R>(startIter, endIter, maxR);
}

#endif
