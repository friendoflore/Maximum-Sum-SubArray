#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

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
	alg1_output.open("MSS_Results.txt");
	alg1_output << endl << "Beginning algorithm 1" << endl << endl; 


	// These are used to store the runtime of the algorithm
	clock_t t1, t2;
	double runtime;
	
	// For each problem from the set of problems
	for(int u = 0; u < input_arrays.size(); u++) {
		
		// "Start" the clock at the beginning of the algorithm
		t1 = clock();

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
		
		// "Stop" the clock at the end of the algorithm
		t2 = clock();
		runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;
		
		// These print the algorithm results in "Algorithm_1_Results.txt"
		print_array(input_arrays[u], 0, input_arrays[u].size(), &alg1_output);
		print_array(input_arrays[u], low, high + 1, &alg1_output);
		alg1_output << best << endl;
		alg1_output << "algorithm ran in " << runtime << " seconds for input of " << input_arrays[u].size() << "." << endl; 
		
		// Reset "best" for another run of the algorithm
		best = 0;
	}

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

	// We will put Algorithm 2's results in the file below.
	ofstream alg2_output;
	alg2_output.open("MSS_Results.txt", ios::out | ios::app);
	alg2_output << endl << "Beginning algorithm 2" << endl << endl; 

	// These are used to store the runtime of the algorithm
	clock_t t1, t2;
	double runtime;
	
	// For each problem from the set of problems
	for(int u = 0; u < input_arrays.size(); u++) {
	
	// "Start" the clock at the beginning of the algorithm
	t1 = clock();
  	
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
		
		// "Stop" the clock at the end of the algorithm
		t2 = clock();
		runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;
		
		// These print the algorithm results in "Algorithm_2_Results.txt"
		print_array(input_arrays[u], 0, input_arrays[u].size(), &alg2_output);
		print_array(input_arrays[u], low, high + 1, &alg2_output);
		alg2_output << best << endl;
		alg2_output << "algorithm ran in " << runtime << " seconds for input of " << input_arrays[u].size() << "." << endl; 
		

		// Reset "best" for another run of the algorithm
		best = 0;
	}
	
	alg2_output.close();
}

// Algorithm 3
// Divide and Conquer
vector<int> Find_Max_Crossing_Subarray(vector<int> input_array, 
	int low, int mid, int high) {

	vector<int> result;

	int left_sum = numeric_limits<int>::min();
	int right_sum = numeric_limits<int>::min();
	int sum = 0;

	int max_left;
	int max_right;
	
	for(int i = mid; i >= low; i--) {
		sum = sum + input_array[i];
		if(sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	sum = 0;

	for(int i = mid + 1; i <= high; i++) {
		sum = sum + input_array[i];
		if(sum > right_sum) {
			right_sum = sum;
			max_right = i;
		}
	}

	result.push_back(max_left);
	result.push_back(max_right);
	result.push_back(left_sum + right_sum);

	return result;
}

vector<int> Find_Max_Subarray(vector<int> input_array, int low, 
	int high) {

	vector<int> left_result;
	vector<int> right_result;
	vector<int> cross_result;
	vector<int> result;

	int left_low = 0, left_high = 0, left_sum = 0; 
	int right_low = 0, right_high = 0, right_sum = 0;
	int cross_low = 0, cross_high = 0, cross_sum = 0;
	int mid = 0;

	if(high == low) {
		result.push_back(low);
		result.push_back(high);
		result.push_back(input_array[low]);
		return result;
	} else {
		mid = (low + high) / 2;
		left_result = Find_Max_Subarray(input_array, low, mid);
		left_sum = left_result[2];

		right_result = Find_Max_Subarray(input_array, mid + 1, high);
		right_sum = right_result[2];

		cross_result = Find_Max_Crossing_Subarray(input_array, low, mid, high);
		cross_sum = cross_result[2];

	}

	if((left_sum >= right_sum) && (left_sum >= cross_sum))
		return left_result;
	else if((right_sum >= left_sum) && (right_sum >= cross_sum))
		return right_result;
	else 
		return cross_result;
	
}

void algorithm_3(vector< vector<int> > input_arrays) {

	vector<int> result;

	// We will put Algorithm 4's results in the file below.
	ofstream alg3_output;
	alg3_output.open("MSS_Results.txt", ios::out | ios::app);
	alg3_output  << endl << "Beginning algorithm 3" << endl << endl; 

	// These are used to store the runtime of the algorithm
	clock_t t1, t2;
	double runtime; 

	for(int u = 0; u < input_arrays.size(); u++) {
		result.clear();

		int low = 0;
		int high = input_arrays[u].size() - 1;
		int max = 0;

		// "Start" the clock at the beginning of the algorithm
		t1 = clock();

		result = Find_Max_Subarray(input_arrays[u], low, high);

		// "Stop" the clock at the end of the algorithm
		t2 = clock();
		runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;

		low = result[0];
		high = result[1];
		max = result[2];

		// These print the algorithm results in "MSS_Results.txt"
		print_array(input_arrays[u], 0, input_arrays[u].size(), &alg3_output);
		print_array(input_arrays[u], low, high + 1, &alg3_output);
		alg3_output << max << endl;
		alg3_output << "algorithm ran in " << runtime << " seconds for input of " << input_arrays[u].size() << "." << endl; 
	}
}

// Algorithm 4
// Linear-time
void algorithm_4(vector< vector<int> > input_arrays) {
	// used to store the contiguous subarray of the max  and temporary sum 
	int max;
	int sum;

	// These store the low index and high index of the Maximum Sum SubArray
	int low = 0;
	int high = 0;
	
	// We will put Algorithm 4's results in the file below.
	ofstream alg4_output;
	alg4_output.open("MSS_Results.txt", ios::out | ios::app);
	alg4_output  << endl << "Beginning algorithm 4" << endl << endl; 

	// These are used to store the runtime of the algorithm
	clock_t t1, t2;
	double runtime; 

	// For each problem from the set of problems
	for(int u = 0; u < input_arrays.size(); u++) {
		
		max = -1; // max-sum 
		sum = -1; // ending-here-sum
		low = 0; 
		high = 0;
		int temp_low = -1;
		int temp_high = -1;

   	// "Start" the clock at the beginning of the algorithm
		t1 = clock();

		for(int i = 0; i < input_arrays[u].size(); i++) {
		  temp_high = i;
		  if (sum > 0) {
			sum = sum + input_arrays[u][i];
		  } else {
			temp_low = i;
			sum = input_arrays[u][i];
		  }
		  if (sum > max) {
			max = sum;
			low = temp_low;
			high = temp_high;
		  }
      
    }
		// "Stop" the clock at the end of the algorithm
		t2 = clock();
		runtime = (t2 - t1) / (double) CLOCKS_PER_SEC;

		// These print the algorithm results in "Algorithm_4_Results.txt"
		print_array(input_arrays[u], 0, input_arrays[u].size(), &alg4_output);
		print_array(input_arrays[u], low, high + 1, &alg4_output);
		alg4_output << max << endl;
		alg4_output << "algorithm ran in " << runtime << " seconds for input of " << input_arrays[u].size() << "." << endl; 
		
	}

	alg4_output.close(); 
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

// generate the random input for the evaluation 
vector <vector<int> > generateRandInput(int inputs[], int size)
{
	vector< vector<int> > randNumbers; 
	vector<int> temp;
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < inputs[i]; j++)
		{
			temp.push_back(rand() % 199 - 100); 
		}
		
		randNumbers.push_back(temp);
		temp.clear(); 
	}
	
	return randNumbers;
}

int main(int argc, char *argv[]) {
	// seed random generator
	srand(time(0));

	// This stores the problem arrays that we will use to do calculations
	vector< vector<int> > input_arrays;
	
	// This stores the all problems lines of file input
	vector<string> problem_set;

	// This stores each string as we read it in from file
	string input_string;

	// if there is a command line argument use evaluation mode where test numbers are randomly generated
	if(argc > 1)
	{
		cout << "Evaluation mode: Generating random input strings of varying sizes." << endl; 
		
		int alg1inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
		int alg2inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
		int alg3inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
		int alg4inputs[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500};

		// input_arrays for algorithm 1 
		input_arrays = generateRandInput(alg1inputs, 10); 
		
		// Call algorithm 1
		algorithm_1(input_arrays);
		
		// clear input arrays 
		for (int i = 0; i < input_arrays.size(); i++)
		{
			input_arrays[i].clear(); 
		}
		
		input_arrays.clear();
		
		// input arrays for algorithm 2
		input_arrays = generateRandInput(alg2inputs, 10); 

		// Call algorithm 2
		algorithm_2(input_arrays);
		
		// clear input arrays 
		for (int i = 0; i < input_arrays.size(); i++)
		{
			input_arrays[i].clear(); 
		}
		
		input_arrays.clear();
		
		// input arrays for algorithm 3
		input_arrays = generateRandInput(alg3inputs, 10);
		
		// Call algorithm 3

		// clear input arrays 
		for (int i = 0; i < input_arrays.size(); i++)
		{
			input_arrays[i].clear();
		}

		input_arrays.clear();

		// input arrays for algorithm 4
		input_arrays = generateRandInput(alg4inputs, 10);
		
		// Call algorithm 4
		algorithm_4(input_arrays);
		
	}
	// else use provided test problems file 
	else
	{
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
		algorithm_3(input_arrays);

		// Call algorithm 4
		algorithm_4(input_arrays);
	}

	return 0;
}