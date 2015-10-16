#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <ctime>

using namespace std;

/** Function: print_array *****************************************************
 **	Description: This function prints a vector's contents to the filestream 
 **		passed in. "print_array" is the vector we print from. "low_idx" and 
 **		"high_idx" is the index range this function prints. "* alg_file" is the
 **		address of an open ofstream to which the array will be printed.
 ** Parameters: vector<int> print_array, int low_idx, int high_idx,
 **		ofstream * alg_file
 **	Preconditions: The ofstream argument must be open when passed in.
 **	Postconditions: This function prints the range of the array passed in to
 **		the open filestream passed in, formatted by the form:
 **
 **												[i, j, k, ..., t]
 **
 *****************************************************************************/
void print_array(vector<int> print_array, int low_idx, 
	int high_idx, ofstream * alg_file) {

	// Print each array to the file, formatted
	*alg_file << "[";
	for(int i = low_idx; i < high_idx; i++) {

		// Print each value
		*alg_file << print_array[i];

		if(i != (high_idx - 1))
			*alg_file << ", ";
	}

	*alg_file << "]" << endl;
}

// Algorithm 1
// Enumeration
void algorithm_1(vector< vector <int> > input_arrays) {

	// This stores the best sum of each sub array 
	int best = -1;
	int sum = 0;

	// These store the low index and high index of the Maximum Sum SubArray
	int low = -1;
	int high = -1;

	// We will put Algorithm 1's results in the file below.
	ofstream alg1_output;
	alg1_output.open("Algorithm_1_Results.txt");

	// These are used to store the runtime of the algorithm
	clock_t t1, t2, runtime;

	// "Start" the clock at the beginning of the algorithm
	t1 = clock();
	
	// For each problem from the set of problems
	for(int u = 0; u < input_arrays.size(); u++) {

  	// This is Algorithm 1
		for(int i = 0; i < input_arrays[u].size(); i++) {
			for(int j = i; j < input_arrays[u].size(); j++) {
				
				sum = 0;

				for(int k = i; k <= j; k++)
					sum += input_arrays[u][k];
				
				if(sum > best) {
					low = i;
					high = j;
					best = sum;
				}
			}
		}
		
		// These print the algorithm results in "Algorithm_1_Results.txt"
		print_array(input_arrays[u], 0, input_arrays[u].size(), &alg1_output);
		print_array(input_arrays[u], low, high, &alg1_output);
		alg1_output << best << endl;

		// Reset "best" for another run of the algorithm
		best = 0;
	}

	// "Stop" the clock at the end of the algorithm
	t2 = clock();
	runtime = t2 - t1;

	// Print the runtime to the file
	alg1_output << "Runtime: " << runtime << endl;

	alg1_output.close();
}

// Algorithm 2
// Better Enumeration
void algorithm_2(vector< vector<int> > input_arrays) {
	// This stores the best sum of each sub array 
	int best = -1;
	int sum = 0;

	// These store the low index and high index of the Maximum Sum SubArray
	int low = -1;
	int high = -1;

	// We will put Algorithm 1's results in the file below.
	ofstream alg2_output;
	alg2_output.open("Algorithm_2_Results.txt");

	// These are used to store the runtime of the algorithm
	clock_t t1, t2, runtime;

	// "Start" the clock at the beginning of the algorithm
	t1 = clock();
	
	// For each problem from the set of problems
	for(int u = 0; u < input_arrays.size(); u++) {

  	// This is Algorithm 2
		for(int i = 0; i < input_arrays[u].size(); i++) {
			sum = 0;
			
			for(int j = i; j < input_arrays[u].size(); j++) {
				sum += input_arrays[u][j];
				
				if(sum > best) {
					low = i;
					high = j;
					best = sum;
				}
			}
		}
		
		// These print the algorithm results in "Algorithm_1_Results.txt"
		print_array(input_arrays[u], 0, input_arrays[u].size(), &alg2_output);
		print_array(input_arrays[u], low, high, &alg2_output);
		alg2_output << best << endl;

		// Reset "best" for another run of the algorithm
		best = 0;
	}

	// "Stop" the clock at the end of the algorithm
	t2 = clock();
	runtime = t2 - t1;

	// Print the runtime to the file
	alg2_output << "Runtime: " << runtime << endl;

	alg2_output.close();
}

// Algorithm 3
// Divide and Conquer
void algorithm_3(vector< vector<int> > input_arrays) {
	
}

// Algorithm 4
// Linear-time
void algorithm_4(vector< vector<int> > input_arrays) {
	
}

// Parse the string into vectors
vector< vector <int> > parse_input(vector<string> input_strings) {
	// This will store the parsed input arrays
	vector< vector<int> > input_arrays;

	// This stores each integer to parse the file input
	string tmp_string;

	// This stores each problem set, each of which we will put in "input_arrays"
	vector<int> tmp_vector;

	// Iterators
	int u = 0;
	int v = 0;

	for(u = 0; u < input_strings.size(); u++) {
		for(v = 0; v < input_strings[u].length(); v++) {
			if((input_strings[u][v] == '[') || (input_strings[u][v] == ' ')) {
				// Do nothing
			} else if((isdigit(input_strings[u][v])) || (input_strings[u][v] == '-')) {
				tmp_string.push_back(input_strings[u][v]);
			} else if((input_strings[u][v] == ',') || (input_strings[u][v] == ']')) {
				tmp_vector.push_back(atoi(tmp_string.c_str()));
				tmp_string = "";
			}
		}

		input_arrays.push_back(tmp_vector);
		tmp_vector.clear();
		tmp_string = "";
	}

	return input_arrays;
}

int main() {

	// This stores the problem arrays that we will use to do calculations
	vector< vector<int> > input_arrays;
	
	// This stores the all problems lines of file input
	vector<string> problem_set;

	// This stores each string as we read it in from file
	string input_string;

	// Open problems text
	ifstream problems ("MSS_TestProblems.txt", ifstream::in);

	while(problems.good()) {
		getline(problems, input_string);
		problem_set.push_back(input_string);
	}

	input_arrays = parse_input(problem_set);

	// Use "input_arrays" to do the calculations for each of the algorithms

	// Call algorithm 1
	algorithm_1(input_arrays);

	// Call algorithm 2
	algorithm_2(input_arrays);

	// Call algorithm 3


	// Call algorithm 4


	return 0;
}