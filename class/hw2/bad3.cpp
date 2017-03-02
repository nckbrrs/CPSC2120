/*
	Nicholas Barrs	
	nbarrs
	CPSC 2120-001
	26 September 2015
	HW2: bad3.cpp - generates a series of numbers that makes "prog3.cpp" run
		slowly
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
	cout << "Usage: bad3 <input size>\n";
	return 0;
	}

	int N = atoi(argv[1]);  // get first command-line argument
	if (N<1 || N>100000) {
		cout << "Invalid input size!\n";
		return 0;
	}
  
	// Generate and print bad input of size N for prog3
	cout << N << "\n";

	int *input = new int[N];
	int collision;
	fill(input, input+N, -1);

	// inserts integers 0 up to N-1 in "input" such that prog3 will choose
	// the lowest value available as the pivot in each iteration of "partition"
	for (int j=0; j<N; j++) {
		if (input[123456789%(N-j)] != -1) { // if spot is already filled...
			collision = 123456789%(N-j);		
			while (input[collision] != -1) {	// scan until next "empty" slot
				collision++;
			}
			input[collision] = j;				// and insert there
		}	
		else input[123456789%(N-j)] = j;		// otherwise simply insert
	}

	for (int l=0; l<N; l++) {
		cout << input[l] << "\n";
	}

	delete[] input;
}
