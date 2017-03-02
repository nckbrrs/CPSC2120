/*
	Nicholas Barrs
	nbarrs
	CPSC 2120-001
	25 August 2015
	intset.h - header file for intset.cpp
*/

#ifndef INTSET_H /*Prevent multiple inclusion... */
#define INTSET_H

struct Node {
	int key;
	Node *next;
	Node (int k, Node *n) { key = k; next = n; }
	Node() { key = 0; next = NULL; }
};

class Intset {
	private:
		Node *head;

	public:
		Intset();
		~Intset();
		bool find(int key);
		void insert(int key);
		void remove(int key);
		void print(void);
};

#endif
