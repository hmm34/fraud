// Heather Michaud

#ifndef FRAUD_HPP
#define FRAUD_HPP

#include "concepts.hpp"
#include <math.h>

// ========================================================================= //
// =============== Concrete Implementation: Double Array =================== //
// ========================================================================= //

// Calculates the sum of a list of numbers in an array
double sum(double a[], int n) {
	double s = 0;
	for (int i = 0; i < n; ++i)
		s += a[i];
	return s;
}

// Calculates the mean of a list of numbers in an array
double mean(double a[], int n) {
	double s = sum(a, n);
	return s / (double) n;
}

// Calculates the variance in a list of numbers in an array
double variance(double a[], int n) {
	double m = mean(a, n);
	double sumSquares = 0;
	for (int i = 0; i < n; ++i) {
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
double correlation_coefficient(double a[], double b[], int n) {
	double meanA = mean(a, n);
	double meanB = mean(b, n);
	double stddevA = standard_deviation(a, n);
	double stddevB = standard_deviation(b, n);
	double total = 0;
	for (int i = 0; i < n; ++i) {
		total += ((a[i] - meanA) / stddevA) * ((b[i] - meanB) / stddevB);
	}
	return total / (double) (n - 1);
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

// Calculates the correlation coefficient between two lists of numbors, given 
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


#endif
