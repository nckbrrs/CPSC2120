/*
	Nicholas Barrs	
	nbarrs
	CPSC 2120-001
	26 September 2015
	HW2: bad2.cpp - generates a series of numbers that makes "prog2.cpp" run
		slowly
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
	cout << "Usage: bad2 <input size>\n";
	return 0;
	}

	int N = atoi(argv[1]);  // get first command-line argument
	if (N<1 || N>100000) {
		cout << "Invalid input size!\n";
		return 0;
	}
  
	// Generate and print bad input of size N for prog2
	cout << N << "\n";

	// Prints multiples of 10000 beacuse the hash function in prog2.cpp mods each
	// input by 10000; thus each number in input2 file will hash to the same
	// array index and make prog2's find function read the entire input
	// array every time it is called
	for (int i=1; i<=N; i++)
		cout << i * 10000 << "\n";
  
	return 0;
}
