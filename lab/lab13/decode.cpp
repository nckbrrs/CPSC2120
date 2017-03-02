/*
	Nicholas Barrs
	nbarrs
	CPSC 2121-001
	1 December 2015
	decode.cpp - LZ78 decoder; takes in pairs of ints representing characters
		and converts them into its original string
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

struct Node {
	int letter;
	int parent;
	Node(int p, int l) { letter = l; parent = p; }
};

vector<Node> nodes;

void print_path(int i)
{
	// recursively print path
	if (i == 0) return;
	print_path(nodes[i].parent);
	if (nodes[i].letter != EOF)
		cout << (char)nodes[i].letter;
}

int main (void)
{
	nodes.push_back(Node(-1, 0));
	int i, l;

	while (cin >> i >> l) {
		nodes.push_back(Node(i, l));	
		print_path(nodes.size() - 1);	
	}
 
	return 0;
}
