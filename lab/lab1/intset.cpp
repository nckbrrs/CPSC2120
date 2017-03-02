/*
	Nicholas Barrs
	nbarrs
	CPSC 2121-001
	25 August 2015
	intset.cpp - c++ data structure for representing a set of integers; includes
		code that finds, inserts, removes, and prints set of integers
*/

#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

/* Intset constructor */
Intset::Intset()
{
	head = new Node(0, NULL);
}	

/* Intset deconstructor */
Intset::~Intset()
{
	Node *temp;
	while (head != NULL) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

/* Return true if key is in the set */
bool Intset::find (int key)
{
	Node *n = head->next;
	while (n != NULL) {
		if (n->key == key) return true; // key has been found
		n = n->next;
	}
	return false;
}

/* Inserts a new key. It is an error if key is already in the set. */
void Intset::insert (int key)
{
	assert (!find(key));
	Node *temp = head;
	while (temp->next != NULL && temp->next->key < key)
		temp = temp->next;
	temp->next = new Node(key, temp->next);
}
	
/* Removes a key. It is an error if key isn't in the set */
void Intset::remove (int key)
{
	assert (find(key));

	Node *temp = head;
	while (temp->key != key)
		temp = temp->next;
	Node *to_delete = temp->next;
	temp->next = to_delete->next;
	delete to_delete;
}

	

/* Prints set of integers */
void Intset::print(void)
{
	Node *current = head->next;
	while (current != NULL) {
		cout << current->key << "\n";
		current = current->next;
	}
}
