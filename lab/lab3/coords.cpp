#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
	double x, y;
};

struct Node {
	Point p;
	Node *next;
	Node (Point _p, Node *n) { p = _p; next = n; }
};

const int b = 1000;
Node ***A;

void allocate_table(void)
{
	int i, j;

	A = new Node **[b];
	for (i=0; i<b; i++)
		A[i] = new Node *[b];

	for (i=0; i<b; i++)
		for (j=0; j<b; j++)
			A[i][j] = NULL;
}

void free_table(void)
{
	int i, j;
	for (i=0; i<b; i++) {
		for (j=0; j<b; j++) {
			while (A[i][j] != NULL) {
				Node *to_delete = A[i][j];
				A[i][j] = A[i][j]->next;
				delete to_delete;
			}
		}
	}

	for (i=0; i<b; i++)
		delete[] A[i];

	delete[] A;
}

void read_input(void)
{
	ifstream fin;
	fin.open ("points.txt");
	Point p;
	int i, j;
	while (fin >> p.x >> p.y) {
		i = (int)(p.x * b);
		j = (int)(p.y * b);
		A[i][j] = new Node(p, A[i][j]);
	}
	fin.close();
}

double dist (Point p, Point q)
{
	double dx = p.x-q.x, dy = p.y-q.y;
	return sqrt(dx*dx + dy*dy);
}

double find_closest_point(Point p)
{
	int i = p.x*b, j = p.y*b;
	double m = 2.0;

	for (int di=-1; di<=1; di++) {
		for (int dj=-1; dj<=1; dj++) {
			if (i+di>=0 && i+di<b && j+dj >=0 && j+dj<b) {
				for (Node *temp = A[i+di][j+dj]; temp != NULL; temp = temp->next) {
					if (dist(p, temp->p)>0)	{
						m = min(m, dist(p, temp->p));
					}
				}
			}
		}
	}
	return m;
}

double find_closest(void)
{
	double m = 2.0;
	for (int i=0; i<b; i++) {
		for (int j=0; j<b; j++) {
			for (Node *current = A[i][j]; current != NULL;
					current = current->next) {
				m = min(m, find_closest_point(current->p));
			}
		}
	}
	return m;
}

int main (void)
{
	allocate_table();
	read_input();
	cout << find_closest() << "\n";
	free_table();
}
