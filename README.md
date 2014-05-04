fraud
=====

A generic library used for determining the longest sequence that a calculation
on partially ordered sets meets a threshold value.


### Example Usage

This project was originally created with a specific example in mind. A list of
commits to a Git repository, ordered by the date and time which the change was
pushed, has been obtained. Let us call this set A, with elements {a1, ..., an},
provided that there are n commits. Each commit entry contains numerical data
such as the number of lines, number of hunks, and number of files that were
modified. We have calculated the correlation coefficient between these values
over the span of the entire repository's life, for files and hunks, lines and
hunks, and files and lines.

We wished to calculate the location and length of the sub-sequence whose
commit entry data met a provided threshold value for an expected correlation
coefficient, as well as a threshhold value for the length of the sub-sequence.
In this manner, we intend to discover the time periods of an open-source
software's history in which the size of the commit was closely correlated with
other commit size metrics. By providing a threshhold value for the correlation
coefficient, we ensure that the sub-sequence will represent a correlation
whose strength can vary but meets the expectation of a strong correlation. In
addition, the threshhold value for the length of the subsequence ensures that we
disregard small sequences, whose correlation is likely much higher due to the
lack of sufficient data.


## Template functions

#### `sum(I first, I last, T id)`

Computes the <a href="http://en.wikipedia.org/wiki/Summation">summation</a> of a 
list of numbers, ranging from [first, last). User must
provide the additive identity. The returning sum is the same value type as the
elements to which the iterators point. 


##### requirements

  * `first` and `last` are forward iterators
  * `T` is convertible to the value type of the iterator
  * `id` is the additive identity
  * `last` is reachable from `first`


#### `mean(I first, I last, T id)`

Calculates the <a href="http://en.wikipedia.org/wiki/Arithmetic_mean">arithmetic
mean</a> of a list of numbers, ranging from [first, last). User must
provide the additive identity. The returning mean is the same value type as the
elements to which the iterators point. 


##### requirements

  * `first` and `last` are forward iterators
  * `T` is convertible to the value type of the iterator
  * `id` is the additive identity
  * `last` is reachable from `first`


#### `variance(I first, I last, T id)`

Calculates the <a href="http://en.wikipedia.org/wiki/Variance">variance</a>
of a list of numbers, ranging from [first, last). User must
provide the additive identity. The returning variance is the same value type as the
elements to which the iterators point. 


##### requirements

  * `first` and `last` are forward iterators
  * `T` is convertible to the value type of the iterator
  * `id` is the additive identity
  * `last` is reachable from `first`


#### `standard_deviation(I first, I last, T id)`

Calculates the <a href="http://en.wikipedia.org/wiki/Standard_deviation">standard
deviation</a> in a sequence of elements, ranging from
[first, last). User must provide the additive identity. The returning standard
deviation is the same value type as the
elements to which the iterators point. The sequence does
not need to be ordered. Standard deviation is calculated by the square of the
variance. Variance is determined by the sum of the square of the difference
between the ith element of sequence A and the mean of A, all divided by n - 1.


##### requirements

  * `first` and `last` are forward iterators
  * `T` is convertible to the value type of the iterator
  * `id` is the additive identity
  * `last` is reachable from `first`
  * Addition, multiplication, and division have been defined for iterator value type


#### `correlation_coefficient(I firstA, I lastA, I firstB, I lastB, T id)`

Calculates the <a href="http://en.wikipedia.org/wiki/Pearson_product-moment_correlation_coefficient">
correlation coefficient</a> between the two sequences, a and b. Both
a and b must be the same type: containers which are each partially ordered and
hold some numerical values. The return
type is the iterator value type, and is a number between -1.0 and +1.0. A -1 value
indicates a strong reverse correlation, 0 indicates no correlation, and +1
indicates a strong positive correlation.

The correlation coefficient between two sequences A and B of length n is
calculated by subtracting (n * mean(A) * mean(B)) from the sum of the cross
product of all respective elements a.1 and b.1 up to a.n and b.n, all divided
by (n * standard_deviation(A) * standard_deviation(B)). It should be noted that
correlation does not imply causality.


##### requirements

  * `firstA`, `lastA`, `firstB`, and `lastB` are forward iterators
  * `T` is convertible to the value type of the iterator
  * `id` is the additive identity
  * `lastA` is reachable from `firstA`
  * The ranges [firstA, lastA) and [firstB, lastB) have the same size
  * Addition, multiplication, and division have been defined for iterator value type


#### `strongest_correlation(I firstA, I lastA, I firstB, I lastB, Value_type<I> minR, N minLength, T id)`

Calculates the longest corresponding subsequence of two sequences, a and b, in
which that subsequence gives the strongest positive or strongest negative correlation
coefficient for sequence a.sub and b.sub. The minimum threshhold length for the
subsequence, and the minimum threshhold magnitude for the correlation coefficient are provided.
The return type is a triple, whose m0 value is the beginning iterator to the
subsequence, m1 value is the last (non-inclusive) iterator to the subsequence,
and m2 value is the resulting strongest correlation coefficient for that longest
subsequence which satisfies the two minimum threshholds.


##### requirements

  * `firstA`, `lastA`, `firstB`, and `lastB` are forward iterators
  * `T` is convertible to the value type of the iterator
  * `id` is the additive identity
  * `lastA` is reachable from `firstA`
  * The ranges [firstA, lastA) and [firstB, lastB) have the same size
  * Addition, multiplication, and division have been defined for iterator value type


### Dependencies

Fraud requires the currently experimental
<a href=http://concepts.axiomatics.org/w/index.php5/GCC-c%2B%2B-concepts>
GCC C++ Concepts compiler</a>. It is hoped that GCC 4.9 will ship with these
features available. Prior to building with CMake, the CXX flag must be set to
the location of this compiler.
