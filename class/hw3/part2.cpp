/*
	Nicholas Barrs
	CPSC 2120-001
	nbarrs
	Oct 30 2015
	HW3i part 2 - linearization of a graph by relaxation and rounding
*/

/* I tried my best! */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#define N 936

using namespace std;

struct Node {
	int nbr;
	Node *next;
	Node (int x, Node *n) { nbr = x; next = n; }
};

struct Position {
	int nbrs_index;
	double pos;
};

double best_dist = 9007199254740992;
Node *nbrs[N];

int square(int x)
{
	return x * x;
}

void read_input (void)
{
	for (int i=0; i<N; i++)
		nbrs[i] = NULL;

	int x, y;
	while (cin >> x >> y)
		nbrs[x] = new Node(y, nbrs[x]);	
}

void assign_node_random_pos(Position *p)
{
	for (int i=0; i<N; i++) {
		p[i].nbrs_index = i;
		p[i].pos = (double((rand() % N)) / double((rand() % N)));
	}
}

/* for use in qsort
int compare (const void *a, const void *b)
{
	if ( *(int*)a < *(int*)b ) return -1;
	if ( *(int*)a == *(int*)b ) return 0;
	if ( *(int*) a > *(int*)b ) return 1;
}
*/

int get_nbrs_index (double x, Position *p)
{
	for (int i=0; i<N; i++) {
		if (p[i].pos == x) return i;
	}
}

int partition (double *A, int len)
{
	int pivot = rand() % len;
	double *temp = new double[len];
	int j=0;
	for (int i=0; i<len; i++)
		if (A[i] < A[pivot]) temp[j++] = A[i];
	int where_pivot_first = j;
	for (int i=0; i<len; i++)
		if (A[i] == A[pivot]) temp[j++] = A[i];
	int where_pivot_last = j-1;
	for (int i=0; i<len; i++)
		if (A[i] > A[pivot]) temp[j++] = A[i];
	for (int i=0; i<len; i++)
		A[i] = temp[i];
	delete[] temp;
	return (where_pivot_first + where_pivot_last / 2);
}

void quicksort (double *A, int len)
{
	if (len<=1) return;
	int p = partition(A, len);
	quicksort(A, p);
	quicksort(A+p+1, len-p-1);
}

void fill_pos_array (int *order, Position *p)
{
	cout << "in fill\n";
	double d_order[N];

	// put all positions in an array of doubles
	for (int i=0; i<N; i++)
		d_order[i] = p[i].pos;

	cout << "d_order filled\n";

	// sort array
	cout << "before sort\n";
	quicksort(d_order, N);
	cout << "after sort\n";	

	// copy position's corresponding node number into position array from 0 to N
	for (int i=0; i<N; i++) {
		cout << i << "'s pos: " << d_order[i] << endl;
		order[i] = get_nbrs_index(d_order[i], p);
	}	
	cout << "after filling order\n";
	return;
}

double average_nbr_pos(int x, Position *p)
{
	int nbr_count = 0;
	double sum = 0;
	double average;
	
	Node *temp = nbrs[x];
	while (temp != NULL) {
		sum += square(p[temp->nbr].pos - p[x].pos);
		nbr_count++;
		temp = temp->next;
	}
	
	delete temp;
	average = (double(sum) / double(nbr_count));
	return average;
}

void refine (Position *p)
{
	int a = (rand() % N);
	int b = ((1000 * a) % N);

	p[a].pos = 0;
	p[b].pos = N;

	double orig_pos;
	double new_pos;
	double pos_diff = N;
	
	while (pos_diff > 0.00001 || pos_diff < -0.00001) {	
		for (int i=0; i<N; i++) {
			if (i != a && i != b) {
				orig_pos = p[i].pos;
				p[i].pos = average_nbr_pos(i, p);
				new_pos = p[i].pos;
				pos_diff = new_pos - orig_pos;
			}
		}
	}
}

int total_sum (int *order, Position *p)
{
	cout << "in total_sum\n";
	int sum = 0;
	Node *temp;

	for (int i=0; i<N; i++) {
		temp = nbrs[order[i]];
		cout << "temp assigned\n";
		while (temp != NULL) {
			sum += square(p[temp->nbr].pos - p[i].pos);
			temp = temp->next;
		}
	}	

	return sum;
}

int main (void)
{
	read_input();
	int new_sum;
	int best_sum;
	Position pos[N];
	int order[N];
	int best_order[N];

	for (int i=0; i<500; i++) {
		cout << "in main for loop, before assign_node_random_pos\n";
		assign_node_random_pos(pos);
		cout << "after assign_nod_random_pos, before refine\n";
		refine(pos);
		cout << "after refine, before fill\n";
		fill_pos_array(order, pos);
		cout << "after fill, before calculating new_sum\n";
		new_sum = total_sum(order, pos);
		cout << "new_sum calculated\n";
		if (new_sum < best_sum) {
			best_sum = new_sum;
			for (int j=0; j<N; j++) { best_order[j] = order[j]; }
		}		
	}

	for (int i=0; i<N; i++) {
		cout << best_order[i] << endl;
	}
	cout << best_sum << endl;
	return 0;
}

