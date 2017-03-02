/*
	Nicholas Barrs
	CPSC 2121-001
	nbarrs
	Oct 21, 2015
	Lab 7 - traveling salesperson "solution"
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <cmath>
#define N 50
#define NTRIALS 100

using namespace std;

struct Point {
	double x, y;
};

Point P[N];

double tour_len(int *T)
{
	double total = 0.0;
	for (int i=0; i<N; i++) {
		double dx = P[T[i]].x - P[T[(i+1)%N]].x;
		double dy = P[T[i]].y - P[T[(i+1)%N]].y;
		total += sqrt(dx*dx + dy*dy);
	}
	return total;
}

void randomize_tour (int *T)
{
	for (int i=0; i<N; i++) {
		T[i] = i;
		swap(T[i], T[rand() % (i+1)]);
	}
}

void reverse (int *T, int a, int b)
{
	if (a>= b) return;
	swap (T[a], T[b]);
	reverse (T, a+1, b-1);
}

bool refine (int *T)
{
	double orig_len = tour_len(T);
	for (int a =0; a<N; a++)
		for (int b=a+2; b<N; b++) {
			reverse(T, a+1, b);
			if (tour_len(T) < orig_len) return true;
			reverse(T, a+1, b);
		}
	return false;
}

int main (void)
{
	ifstream fin("tsp_points.txt");
	for (int i=0; i<N; i++)
		fin >> P[i].x >> P[i].y;
	fin.close();

	int tour[N], best_tour[N];
	double best = 99999;
	for (int i=0; i<NTRIALS; i++) {
		randomize_tour(tour);
		while (refine(tour));
		if (tour_len(tour) < best) {
			best = tour_len(tour);
			for (int j=0; j<N; j++) best_tour[j] = tour[j];
		}
	}

	cout << "Best tour length: " << best << "\n";
	for (int i=0; i<N; i++)
		cout << best_tour[i] << " ";
	cout << "\n";

	return 0;
}
