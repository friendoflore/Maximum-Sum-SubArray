# Maximum-Sum-SubArray
## I. File list
Maximum_Sub_Array.cpp&nbsp;&nbsp;&nbsp;&nbsp;Algorithm implementation<br />
MSS_Programs.txt&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sample problem set <br />
README.md&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This file<br />


## II. Program instructions

#### A. Program Overview

Given an array of integers of the form

	[a_0, a_1, a_2, ... , a_n]

this program returns the contiguous subarray with the maximum sum. This program
accepts input from a file, the name of which is hard-coded, or the program can 
be put into "evaluation mode", which causes the program to generate a series 
of random arrays to test the runtime of the algorithms involved in the program.

This program outputs the original array, the maximum subarray, the sum of that
subarray, and the runtime for 4 different algorithms that all accomplish the
same thing, namely finding that max sum. All output is put into a file that
is hard-coded as well.

#### B. Running the program

This program consists only of the primary CPP file. To compile, I will use
"max_sum" as the object file name placeholder. From the command line, while in
the directory of the CPP file, enter the following:

	"g++ Maximum_Sub_Array.cpp -o max_sum"

In running the program, there are two options. Either run in the default state,
which takes input from the file "MSS_Problems.txt" or in "evaluation mode" 
which is entered if any argument is provided while executing the object file.

If the default input from the file is desired, run the file as follows:

	"./max_sum"

If "evaluation mode" is desired, run the file as follows:

	"./max_sum 1"

The output of both program run styles can be found in "MSS_Results.txt".

#### C. Program output

For each of the four algorithms, this program outputs the original array, the
maximum subarray, the sum of that subarray, and the time (in seconds) that the
algorithm took to complete. The output will look as follows:

	Beginning algorithm 1

	[a_0, a_1, a_2, ... , a_n]
	[a_i, a_j, ... , a_m]
	a_i + a_j + ... + a_m
	algorithm ran in [1e-05] seconds for input of [n]
	.
	.
	.

where i >= 0 and m <= n. Algorithms 1 - 4 all print their results one
after the other in the same output file.


## III. Algorithm implementation

#### A. Enumeration

This algorithm runs in Theta(n^3) time and uses three nested for loops to
calculate and test the sums of each subarray.

#### B. Better Enumeration

This algorithm runs in Theta(n^2) time and uses two nested for loops to
calculate and test the sums of each subarray.

#### C. Divide and Conquer

This algorithm runs in Theta(n log n) time and uses a recurrence relation of
the form:
	
	"T(n) = 2T(n/2) + Theta(n)"

i.e. breaks the problem into two subproblems each of size n/2, combining the
solutions in Theta(n) time.

#### D. Linear

This algorithms takes Theta(n) time and uses a single for loop to calculate the
maximum sum subarray.


## IV. Implementation notes

The algorithms return a vector containing three attributes that give us our 
desired file output - the low index and the high index of the maximum subarray
range and the sum of that range.


## V. Authors

This program was written for CS 325 at Oregon State University, Project Group 
14, Fall 2015.

Benjamin Olson<br />
David Profio<br />
Timothy Robinson
