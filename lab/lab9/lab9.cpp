/*
	Nicholas Barrs
	nbarrs
	CPSC 2121-001
	4 Nov 2015
	lab 9 - recursive search: flling water jugs
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

int A, B, X; // size of jug1, size of jug2, desired exact amount of water

struct State {
	int jug1, jug2;
	bool beenthere;
	State(int a, int b) { jug1 = a; jug2 = b;	}
	State() { jug1 = 0; jug2 = 0; }
};

struct sol_step {
	string move;
	int jug1, jug2;
	sol_step *next;
	sol_step(string s, int a, int b, sol_step *n) {
		move = s;
		jug1 = a;
		jug2 = b;
		next = n;
	}
};

State **states;
sol_step *sol_steps = new sol_step("start", -1, -1, NULL);

bool solve(int a, int b, string prev_move)
{
	int temp_a;
	int temp_b;

	// base case: found goal!
	if (a + b == X) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	// other base case: been here before 
	if (states[a][b].beenthere == true) return false;

	// mark this state as visited
	states[a][b].beenthere = true;
	
	// fill A
	if (solve(A,b, "fill jug 1  ")) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	// empty A
	if (solve(0,b, "empty jug 1 ")) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	// pour A into B
	temp_a = a;
	temp_b = b;

	int B_left_to_fill = B - temp_b;
	if (B_left_to_fill > temp_a) { temp_b += temp_a; temp_a = 0; }
	else { temp_b = B; temp_a -= B_left_to_fill; }
	
	if (solve(temp_a,temp_b, "pour 1->2   ")) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	// fill B
	if (solve(a,B, "fill jug 2  ")) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	// empty B
	if (solve(a,0, "empty jug 2 ")) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	// pour B into A
	temp_a = a;
	temp_b = b;

	int A_left_to_fill = A - temp_a;
	if (A_left_to_fill >= temp_b) { temp_a += temp_b; temp_b = 0; }
	else { temp_a = A; temp_b -= A_left_to_fill; }

	if (solve(temp_a, temp_b, "pour 2->1   ")) {
		sol_steps = new sol_step(prev_move, a, b, sol_steps);
		return true;
	}

	else return false;
}

void print_solution(void)
{
	while (sol_steps->next != NULL) {
		cout << sol_steps->move;
		cout << " [a=" << sol_steps->jug1;
		cout << ", b=" << sol_steps->jug2;
		cout << "]\n";
		sol_steps = sol_steps->next;
	}
}

int main (void)
{
	//read in inputs for A, B, X
	cout << "Enter A: ";	cin >> A;
	cout << "Enter B: "; cin >> B;
	cout << "Enter X: "; cin >> X;
	cout << endl;

	// if, from the start, you know that the desired amount of water is greater
	// than the total capacity of both jugs, print "impossible!" and return
	if (X > A + B) { cout << "Impossible!\n"; return 0; }

	// create a 2D array of states
	states = new State*[A+1];
	for (int i=0; i<A+1; i++) states[i] = new State[B+1];

	// initialize each state's "beenthere" values to false
	for (int a=0; a<A; a++) {
		for (int b=0; b<B; b++) {
			states[a][b].beenthere = false;
		}
	}
	
	// solve and print solution or, if no solution, "impossible"
	if (solve(0,0, "start")) print_solution();
	else cout << "Impossible!\n";
	return 0;
}
