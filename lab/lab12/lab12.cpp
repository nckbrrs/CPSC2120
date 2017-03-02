/*
	Nicholas Barrs
	nbarrs
	CPSC 2121-001
	27 November 2015
	Lab 12 - diameter of USA using Dijkstra's algorithm
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <vector>
#define McA 17731931
#define INF 99999999

using namespace std;

struct Edge {
	int src; 
	int dst;
	float travel_time;
};

int N;
int M;
Edge *E;
vector<int> first_edge;

// compare two edges based on their source nodes; break ties using dest nodes
bool comp(Edge e1, Edge e2)
{
  if (e1.src == e2.src) return e1.dst < e2.dst;
  return e1.src < e2.src;
}

void read_input(void)
{
  FILE *fp = popen ("zcat /tmp/usa_network.txt.gz", "r");
  fscanf (fp, "%d %d", &N, &M);
  E = new Edge[M];

  printf ("Reading input");
  for (int i=0; i<M; i++) {
    fscanf (fp, "%d %d %f", &E[i].src, &E[i].dst, &E[i].travel_time);
    if (i % 1000000 == 0) { printf ("."); fflush(stdout); }
  }

  fclose(fp);
  printf (" Done.\n" ); fflush(stdout); 
}

void fill_first_edge(void)
{
	first_edge.clear();
	first_edge.push_back(0);
	for (int i=1; i<M; i++) 
		if (E[i].src > E[i-1].src)
			first_edge.push_back(i);
}

void swap_E(void)
{
	int temp;

	for (int i=0; i<M; i++) {
		temp = E[i].src;
		E[i].src = E[i].dst;
		E[i].dst = temp;		
	}
}

float dijkstra(int start)
{
	float max = 0;
	float *D = new float[N];

	// set distance from source to source to 0, all others to infinity
	for (int i=0; i<N; i++) D[i] = INF;
	D[start] = 0;
	
	// build priority queue of float,int pairs
	priority_queue< pair<float, int> > Q;
	Q.push(pair<float,int>(0, start));

	// algorithm
	while (!Q.empty()) {
		pair<float, int> q = Q.top();
		Q.pop();
      
		if (D[q.second] > max) max = D[q.second];

		for (int j=first_edge[q.second]; j < M && E[j].src == q.second; j++) {
			if ((D[q.second] + E[j].travel_time) < D[E[j].dst]) {
				D[E[j].dst] = D[q.second] + E[j].travel_time;
				Q.push(pair<float, int>(-1 * D[E[j].dst], E[j].dst));
			}			
		}
	}

	return max;
}

int main(void)
{
	read_input();
	sort(E, E+M, comp);
	fill_first_edge();
	float X = dijkstra(McA);	
	
	swap_E();
	sort(E, E+M, comp);
	fill_first_edge();
	float Y = dijkstra(McA);
		
	cout << endl << (X+Y) / 2 << " " << X+Y << endl;

	return 0;
}
