/*
	Nicholas Barrs
	nbarrs
	CPSC 2120-001
	Oct 30 2015
	HW3 part 1-linearization of a graph by iterative refinement
*/

/* I tried my best! */

#include <iostream>		
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#define N 936
#define M 2664

using namespace std;

struct Node {
	int nbr;
	Node *next;
	Node() { nbr = -1; next = NULL; }
	Node(int x, Node *n) { nbr = x; next = n; }
};

int best_dist = 2147483647;
int pos[N];
int best[N];
Node *nbrs[N];

int square(int x) 
{
	return x * x; 
}

void read_input(void)
{
	for (int i=0; i<N; i++)
		nbrs[i] = NULL;
	
	int x, y;
	while (cin >> x >> y) 
		nbrs[x] = new Node(y, nbrs[x]);
}

void randomize(int A[])
{
	for (int i=0; i<N; i++) {
		A[i] = i;
		swap (A[i], A[rand() % (i+1)]);
	}
}

int get_pos(int x, int p[])
{
	for (int i=0; i<N; i++)
		if (p[i] == x) return i;

	cout << x << " not found.\n";
}

int total_sum(int p[])
{
	int sum = 0;
	for (int i=0; i<N; i++) {
		Node *temp = nbrs[i];
		while (temp != NULL) {
			sum += square(get_pos(temp->nbr, p) - get_pos(i, p));
			temp = temp->next;
		}
	}
	return sum;
}

void swap (int p[], int a, int b)
{
	int temp = p[a];
	p[a] = p[b];
	p[b] = temp;

}

int two_node_sum(int p[], int a, int b)
{
	int a_sum = 0, b_sum = 0;
	Node *temp;

	// get sum of edges of node a and its neighbors pre-swap
	temp = nbrs[p[a]];
	while (temp != NULL) {
		a_sum += square(get_pos(temp->nbr, p) - get_pos(a, p));
		temp = temp->next;
	}

	// get sum of edges of node b and it neighbors pre-swap; adding to orig_sum
	temp = nbrs[p[b]];
	while (temp != NULL) {
		b_sum += square(get_pos(temp->nbr, p) - get_pos(b, p));
		temp = temp->next;
	}
	
	return a_sum + b_sum;
}

bool refine (int *p)
{
	int a, b, pre, post, new_dist;
	int orig = total_sum(p);

	for (a=0; a<N-2; a++) {
		for (b=a+2; b<N; b++) {
			if (b != a && nbrs[p[a]] != NULL && nbrs[p[b]] != NULL) {
				pre = two_node_sum (p, a, b);
				swap(p, a, b);
				post = two_node_sum (p, a, b);
				if (post < pre) {
					new_dist = total_sum(p);
					if (new_dist < orig) {
						orig = new_dist;
						return true;
					}
				}
				else {
					swap(p, a, b);
				}
			}
		}
	}
	cout << "at end of refine\n";
	return false;
}

int main (void)
{
	read_input();
	int new_dist;

	for (int i=0; i<10; i++) {
		randomize(pos);
		cout << "starting dist: " << total_sum(pos) << endl;
		for (int j=0; j<N; j++)	best[j] = pos[j];
		while (refine(pos));
		new_dist = total_sum(pos);
		cout << "new dist is " << new_dist << endl;
		if (new_dist < best_dist) {
			best_dist = new_dist;
			for (int j=0; j<N; j++) best[j] = pos[j];
		}
	}

	for (int i=0; i<N; i++) {
		cout << best[i] << endl;
	}

	cout << best_dist << endl;
	return 0;

}
