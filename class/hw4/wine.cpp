/*
	Nicholas Barrs
	nbarrs
	CPSC 2120-001
	18 November 2015
	HW 4 - Nearest Neighbor Classification using KD-tree
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#define E 2.71828182846

using namespace std;

int N; // number of points
int D; // number of dimensions per point
int K; // number of nearest neighbors to find/analyze

struct kd_node {
	double *point, distance, actual_rating, guess_rating;
	kd_node *left, *right;
	kd_node (double *p) {
		point = new double[D+1];
		for (int i=0; i<D+1; i++) point[i] = p[i]; 
		left = right = NULL;
		actual_rating = point[0];
	}
};

struct n_nbr {
	double dist;
	double *point;
	n_nbr(double d, double *p) { dist = d; point = p; }
	n_nbr() { dist = 1000; point = NULL; }
};

double **points;
kd_node *tree;
n_nbr *knns;
double ASE_sum = 0;

// read data from input file
void read_input(char *k)
{
	// initialize knns as an array of n_nbrs with distances 1000 and indices -1
	K = atoi(k);
	knns = new n_nbr[K];
	for (int i=0; i<K; i++) knns[i] = n_nbr();
	
	ifstream input("wine.txt");
	input >> N >> D;

	// create 2D array of points
	points = new double*[N];
	for (int i=0; i<N; i++) 
		points[i] = new double[D+1];

	// fill in point values
	for (int i=0; i<N; i++) {
		for (int j=0; j<D+1; j++) {
			input >> points[i][j];
		}
	}
}

// translate data so that, across all points, each dimension value has
// zero mean and unit variance by subtracting mean of dimension 
// from each dimension value and dividing each dimension value by 
// standard deviation of dimension
void standardize(void)
{
	double sum, mean, variance, std_dev;

	for (int d=1; d<D+1; d++) {
		sum = 0; mean = 0; variance = 0; std_dev = 0;
		for (int i=0; i<N; i++) 
			sum += points[i][d];
		mean = sum / N;

		for (int j=0; j<N; j++) 
			variance += ((points[j][d] - mean) * (points[j][d] - mean));
		variance = (variance / (N-1));
		std_dev = sqrt(variance);

		for (int k=0; k<N; k++) 
			points[k][d] = ((points[k][d] - mean) / std_dev);
	}
}

// insert a point into kd_tree by splitting on random value for each
// dimension
kd_node *insert (kd_node *T, double *point, int d)
{
	if (d%D == 0) d = 11;
	else d = d%D;

	if (T==NULL) return new kd_node(point);
	if (point[d] < T->point[d]) T->left = insert(T->left, point, d+1);
	else T->right = insert(T->right, point, d+1);
	return T;
}

// compute Euclidean distance between two points
double pt_dist(double *P1, double *P2)
{
	double d_diff, sum = 0;

	for (int d=1; d<D+1; d++) {
		d_diff = (P2[d] - P1[d]);
		d_diff *= d_diff;
		sum += d_diff;
	}

	return sqrt(sum);
}

// sort array of k nearest neighbors
void knn_sort(double *P)
{
	for (int i=0; i<K-1; i++) 
		while (knns[i].dist > knns[i+1].dist) {
			n_nbr *temp = &knns[i];
			knns[i] = knns[i+1];
			knns[i+1] = *temp;
		}
}

// if two points are identical, return true
bool compare(double *P1, double *P2) 
{
	if (P1[0] == P2[0] &&
		 P1[1] == P2[1] &&
		 P1[2] == P2[2] &&
		 P1[3] == P2[3] &&
		 P1[4] == P2[4] &&
		 P1[5] == P2[5] &&
		 P1[6] == P2[6] &&
		 P1[7] == P2[7] &&
		 P1[8] == P2[8] &&
		 P1[9] == P2[9] &&
		 P1[10] == P2[10] &&
		 P1[11] == P2[11]) return true;
	else return false;	
}

// find kd_node that holds point P
kd_node *find(double *P, kd_node *T, int d)
{
	if (d%D == 0) d = 11;
	else d = d%D;

	if (compare(P, T->point)) return T;
	if (P[d] < T->point[d]) return find (P, T->left, d+1);
	else return find(P, T->right, d+1);
}

// compute guessed rating based on weighted average of actual ratings of 
// k nearest neighbors
void guess_rating (kd_node *P)
{
	double sum = 0;
	double weight;
	double weight_sum = 0;

	for (int i=0; i<K; i++) {
		weight = pow(E, -1*knns[i].dist);
		sum += (weight * (find(knns[i].point, tree, 1)->actual_rating));
		weight_sum += weight;
	}
	P->guess_rating = sum / weight_sum;
}	

// k nearest neighbor algorithm
int solve(double *P, kd_node *T, int d, string dir)
{
	int check_other;		

	if (T == NULL) return 0;
	
	if (P[d] < tree->point[d]) check_other = solve (P, T->left, d+1, "left");
	if (P[d] >= tree->point[d]) check_other = solve (P, T->right, d+1, "right");
	if (check_other == 1) {
		if (dir == "right") 
			check_other = solve(P, T->left, d+1, "left");
		else 
			check_other = solve (P, T->right, d+1, "right");
	}

	// check if T is a nearer neighbor than current nearest neighbors
	// if so, insert it and shift rest of knns over
	if (!compare(P, T->point)) {
		for (int i=0; i<K; i++) {
			if (pt_dist(P, T->point) < knns[i].dist) {
				for (int j=K; j-2>=i; j--) {	
					knns[j-1].dist = knns[j-2].dist;
					knns[j-1].point = knns[j-2].point;
				}
				knns[i].dist = pt_dist(P, T->point);
				knns[i].point = T->point;
				knn_sort(P);
				break;
			}
		}
	}

	// if distance to furthest neighbor is greater than distance to splitting
	// point, check other side
	if (knns[K-1].dist > abs(P[d] - T->point[d])) return 1;
	
	knn_sort(P);
}

// compute average squared error of the final classification
void avg_sq_error(kd_node *T)
{
	if (T==NULL) return;
	avg_sq_error(T->left);
	double guess_diff = (T->actual_rating - T->guess_rating);
	ASE_sum += (guess_diff * guess_diff); 
	avg_sq_error(T->right);
}

int main (int argc, char *argv[])
{
	read_input(argv[1]); 
	standardize(); 

	// randomize order of points
	for (int i=0; i<N; i++) swap(points[i], points[rand() % (i+1)]); 

	// insert points into kd-tree
	for (int i=0; i<N; i++) 
		tree = insert(tree, points[i], 1);

	// solve!
	for (int i=0; i<N; i++) {
		for (int j=0; j<K; j++) { knns[j].dist = 1000; knns[j].point = NULL; }
		solve(points[i], tree, 0, "right");	
		guess_rating(find(points[i], tree, 1));
	}
	
	avg_sq_error(tree);
	cout << "average squared error: " << ASE_sum / N << endl;
	return 0;
}
