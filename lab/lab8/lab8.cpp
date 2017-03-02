/*
	Nicholas Barrs
	nbarrs
	CPSC 2121-001
	27 October 2015
	lab 8 - n queens problem: takes in input size n from user and prints number
				of possible solutions to n-queens problem
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int **board;
int N;
int solutions = 0;

bool safe(int row, int col, int N)
{
	int i, j;
	
	// check if rest of row is empty
	for (i=0; i<N; i++)
		if (board[i][col] == 1) return false;

	// check if diagonals are empty
	for (i=row, j=col; i>=0 && j>=0; i--, j--)
		if (board[i][j] == 1) return false;

	for (i=row, j=col; j<N && i>=0; i--, j++)
		if (board[i][j] == 1) return false;

	return true;
}

void check_row(int row, int N)
{
	// base case
	if (row >= N) { solutions++; return;}

	// recursively check all possible solutions
	for (int col=0; col<N; col++) {
		if (safe(row, col, N) == true) {
			board[row][col] = 1;
			check_row(row+1, N);
			board[row][col] = 0;
		}
	}
}

int main (int argc, char *argv[])
{
	// user inputs size of board
	N = atoi(argv[1]);

	// initialize 2D array, "board", of size N
	board = new int*[N];
	for (int i=0; i<N; i++) board[i] = new int[N];

	// start off by filling board with 0s
	for (int i=0; i<N; i++) { 
		for (int j=0; j<N; j++) {
			board[i][j] = 0; 
		}
	}

	// solve 
	check_row(0, N);

	// print solution
	cout << "there are " <<	solutions << " solutions. \n";
}


