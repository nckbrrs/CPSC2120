/*
	Nicholas Barrs
	nbarrs
	CPSC 2121-001
	17 November 2015
	lab 11 - breadth-first search to find eccentricity of contiguous u.s. states
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#define INF 50

using namespace std;

struct State {
	string name;
	vector<string> nbrs;
};

map<string, State *> Nodes;
map<string, int> dists;
vector< pair<int, string> > eccens;

void read_input(void)
{
	ifstream input("usa_48_state_graph.txt");
	string name;
	string neighbor;

	// read input into Nodes, allocating new state memory if it doesn't exist yet
	while (input >> name >> neighbor) {
		if (Nodes.count(name) <= 0) {
			Nodes[name] = new State;
			Nodes[name]->name = name;
		}

		if (Nodes.count(neighbor) <= 0) {
			Nodes[neighbor] = new State;
			Nodes[neighbor]->name = neighbor;
		}
		
		// assign states as neighbors of one another
		Nodes[name]->nbrs.push_back(neighbor);
		Nodes[neighbor]->nbrs.push_back(name);	
	}	
}

void solve (string name)
{
	// initialize all states' distances from source node to infinity
	// to mean that none have been "visited" yet
	map<string, State*>::iterator init;
	for (init = Nodes.begin(); init != Nodes.end(); init++)
		dists[init->first] = INF;

	// initialize distance from source to itself to 0
	dists[name] = 0;

	// breadth-first search to find distances from source to all states,
	// stored in dists vector
	queue<string> Q;
	Q.push(name);
	while (!Q.empty()) {
		string s = Q.front();
		Q.pop();
		vector<string>::iterator it;
		for (it=Nodes[s]->nbrs.begin(); it != Nodes[s]->nbrs.end(); it++)
			// if state has not been "visited", set its distance from source to
			// 1 + distance from source to state before it
			if (dists[*it] == INF) {
				dists[*it] = dists[s]+1;
				Q.push(*it);
			}
	}
}


int main (void)
{
	read_input();
	map<string, State *>::iterator nodes_it;
	map<string, int>::iterator dists_it;

	// for each state, find distance to furthest away state
	for (nodes_it = Nodes.begin(); nodes_it != Nodes.end(); nodes_it++) {
		int largest = 0;
		solve(nodes_it->first);
		for (dists_it = dists.begin(); dists_it != dists.end(); dists_it++)
			if (dists_it->second > largest) largest = dists_it->second;
	
		// insert state paired with its eccentricity into eccens vector	
		pair<int, string> furthest(largest, nodes_it->first);
		eccens.push_back(furthest);
	}

	// sort eccens vector and print out states and their eccens
	sort (eccens.begin(), eccens.end());
	for (int i=0; i<eccens.size(); i++)
		cout << eccens[i].second << " " << eccens[i].first << endl;

	return 0;
}
