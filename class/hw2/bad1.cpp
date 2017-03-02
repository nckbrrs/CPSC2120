/*
	Nicholas Barrs	
	nbarrs
	CPSC 2120-001
	26 September 2015
	HW2: bad1.cpp - generates a series of numbers that makes "prog1.cpp" run
		slowly
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
	cout << "Usage: bad1 <input size>\n";
	return 0;
	}

	int N = atoi(argv[1]);  // get first command-line argument
	if (N<1 || N>100000) {
		cout << "Invalid input size!\n";
		return 0;
	}
  
	// Generate and print bad input of size N for prog1
	cout << N << "\n";
	
	// First tower is "height" N
	cout << N << "\n";

	// Second tower is "height" 1; each successive tower is 1 height-unit taller
	// so "best" distance is re-calculated each time
	for (int i=1; i<N; i++)
		cout << i << "\n";
  
	return 0;
}
