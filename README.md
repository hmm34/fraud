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

#### sum

Blah blah blah.


#### mean

Calculates the mean of all n elements in the sequence a. The return type is the
same type as the elements within the container U. The sequence does not need
to be ordered. Addition must be defined for the type T. The mean is determined
by the sum of all elements divided by n.


#### variance

Blah blah blah.


#### standard deviation

Calculates the standard deviation in the sequence a of n elements. The return
type is the same type as the elements within the container U. The sequence does
not need to be ordered. Addition, multiplication, and integer division must be
defined for the type T. Standard deviation is calculated by the square of the
variance. Variance is determined by the sum of the square of the difference
between the ith element of sequence A and the mean of A, all divided by n - 1.


#### correlation_coefficient

Calculates the correlation coefficient between the two sequences, a and b. Both
a and b must be the same type: containers which are each partially ordered and
hold some numerical values. The third parameter, n, is the number of elements
in each container. The sequences a and b must be of the same size. The return
type is a signed floating point number between -1.0 and +1.0. A -1 value
indicates a strong reverse correlation, 0 indicates no correlation, and +1
indicates a strong positive correlation.

The correlation coefficient between two sequences A and B of length n is
calculated by subtracting (n * mean(A) * mean(B)) from the sum of the cross
product of all respective elements a.1 and b.1 up to a.n and b.n, all divided
by (n * standard_deviation(A) * standard_deviation(B)). It should be noted that
correlation does not imply causality.


#### strongest_correlation

Blah blah blah.


### Dependencies

Fraud requires the currently experimental
<a href=http://concepts.axiomatics.org/w/index.php5/GCC-c%2B%2B-concepts>
GCC C++ Concepts compiler</a>. It is hoped that GCC 4.9 will ship with these
features available. Prior to building with CMake, the CXX flag must be set to
the location of this compiler.
