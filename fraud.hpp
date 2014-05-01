// Heather Michaud

#ifndef FRAUD_HPP
#define FRAUD_HPP

#include "concepts.hpp"
#include "composite.hpp"
#include <cmath>
#include <math.h>

// ========================================================================= //
// =============== Concrete Implementation: Double Array =================== //
// ========================================================================= //

// Calculates the sum of a list of numbers in an array
double sum(double a[], int n) {
	double s = 0;
	for (int i = 0; i < n; ++i)						// O(n)
		s += a[i];
	return s;
}

// Calculates the mean of a list of numbers in an array
double mean(double a[], int n) {
	double s = sum(a, n);							// O(n)
	return s / (double) n;
}

// Calculates the variance in a list of numbers in an array in O(2n)
double variance(double a[], int n) {
	double m = mean(a, n);							// O(n)
	double sumSquares = 0;
	for (int i = 0; i < n; ++i) {					// O(n)
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
	double meanA = mean(a, n);						// O(n)
	double meanB = mean(b, n);						// O(n)
	double stddevA = standard_deviation(a, n);		// O(2n)
	double stddevB = standard_deviation(b, n);		// O(2n)
	double total = 0;
	for (int i = 0; i < n; ++i) {					// O(n)
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
	for (int i = 0; i < n - minLength; ++i) {				// O(n - minLength)
		for (int j = i + minLength; j < n; ++j) {           // O(n - minLength)
			double r = correlation_coefficient(a, b, j-i);	// O(5n)
			if (std::abs(r) > std::abs(maxR)) {
				startIndex = i;
				lastIndex = j;
				maxR = r;
			}
			else if (std::abs(r) >= std::abs(maxR) && 
				    (j - i) > (lastIndex - startIndex)) {
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

// TODO: preconditions for ... everything

// Calculates the sum of a list of numbers, given the first and last iterator
//
template<Iterator I, Real T>
T sum(I first, I last, T id) {
	while (first != last) {
		id = id + *first;
		++first;
	}
	return id;
}

// Calculates the mean of a list of numbers, given the first and last iterator
//
template<Iterator I, Real T>
T mean(I first, I last, T id) {
	T n = id;
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
template<Iterator I, Real T>
T variance(I first, I last, T id) {
	T count = id;
	T m = mean(first, last, id);
	while (first != last) {
		T diff = *first - m;
		id += (diff * diff);
		++count;
		++first;
	}
	return id / (count - T(1));
}

// Calculates the standard deviation of a list of numbers, given the first and
// last iterator
//
template<Iterator I, Real T>
T standard_deviation(I first, I last, T id) {
	return sqrt(variance(first, last, id));
}

// Calculates the correlation coefficient between two lists of numbers, given 
// the first and last iterator for each list
//
// Precondition: The iterators point to lists of the same size
template<Iterator I, Real T>
T correlation_coefficient(I firstA, I lastA, I firstB, I lastB, T id) {
	T meanA = mean(firstA, lastA, id);
	T meanB = mean(firstB, lastB, id);
	T stddevA = standard_deviation(firstA, lastA, id);
	T stddevB = standard_deviation(firstB, lastB, id);
	T count = id;
	while (firstA != lastA) {
		T diffA = (*firstA - meanA) / stddevA;
		T diffB = (*firstB - meanB) / stddevB;
		id += (diffA * diffB);
		++firstA;
		++firstB;
		++count;
	}
	return id / (count - T(1));
}

// Calculates the number of elements in a list, provided the first and the last
// iterator for the list
//
// Precondition: last is reachable from first
template<Real I, typename N>
  requires Integer<N>()
N length(I& first, I& last, N zero) {
	while (first != last) {
		zero += N(1);
		++first;
	}
	return zero;
}

// Calculate the location of the both longest subsequence in an ordered list of
// numbers that has the strongest correlation coefficient, meeting the 
// threshhold minumum sub-sequence length and minumum correlation coefficient
// across the sub-sequence.
//
// Returns a triplet of the starting iterator, the integer length of the
// sub-sequence, and the corresponding strongest correlation coefficient
//

/*
template<Iterator I, Real T, Integer N>
triple<I, N, T>
strongest_correlation(I firstA, I lastA, I firstB, I lastB,
	                  T minR, N minLength, T id) {
	N maxLength = N(0);
	T maxR = minR;
	I startIter = lastA;
	N len = length(*firstA, *lastA, N(0));
	N indexI = N(0);
	
	I ia = firstA;
	I ib = firstB;

	while (ia != lastA && indexI < len - minLength) {
		I ja = ia;
		I jb = ib;
		N indexJ = indexI + minLength;

		while (ja != lastA && indexJ < indexI + minLength) {
			++ja;
			++jb;
			indexJ += N(1);
		}
		while (ja != lastA && indexJ < len) {
			T r = correlation_coefficient(ia, ja, ib, jb, id);
			if (std::abs(r) > std::abs(maxR)) {
				maxR = r;
				startIter = ia;
				maxLength = indexJ - indexI;
			}
			else if (std::abs(r) >= std::abs(maxR) && (indexJ - indexI) > maxLength) {
				maxR = r;
				startIter = ia;
				maxLength = indexJ - indexI;
			}
			indexJ += N(1);
			++ja;
			++jb;
		}

		indexI += N(1);
		++ia;
		++ib;
	}
	return triple<I, N, T>(startIter, maxLength, maxR);
}
*/


#endif
