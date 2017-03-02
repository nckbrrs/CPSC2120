/*
	Nicholas Barrs	
	nbarrs
	CPSC 2121-001
	1 September 2015
	stringset.cpp - function implementations for hash table for strings
*/

#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int hash(string s, int table_size)
{
	unsigned int i, h = 0;
	for (i=0; i<s.length(); i++)
	h = (h * 2917 + (unsigned int)s[i]) % table_size;
	return h;
}

/* Allocate a table of pointers to nodes, all initialized to NULL */
Node **allocate_table(int size)
{
	Node **table = new Node *[size];
	for (int i=0; i<size; i++)
	table[i] = NULL;
	return table;
}

Stringset::Stringset()
{
	size = 4; // initial size of table    
	table = allocate_table(size);
	num_elems = 0; 
}

Stringset::~Stringset()
{
	for (int i=0; i<size; i++) {
		while (table[i] != NULL) {
			Node *temp = table[i];
			table[i] = table[i]->next;
			delete temp;
		}
	}
	delete[] table;
}

/* Return true if key is in the set */
bool Stringset::find(string key)
{
	int h = hash(key, size);
	Node *n = table[h];
	while (n != NULL) {
		if (n->key == key) return true;
		n = n->next;
	}
	return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key)
{
	assert (!find(key));
	num_elems++;

	//allocates a new, bigger hash table if current hash table fills up
	if (num_elems == size) {
		cout << "Doubling size\n";

		Node **old_table = table;
		size *= 2;
		table = allocate_table(size);

		// transfer all elements from old_table into table
		for (int i=0; i<size/2; i++) {
			Node *n = old_table[i];
			while (n != NULL) {
				int h = hash(n->key, size);
				table[h] = new Node(n->key, table[h]);
				Node *to_delete = n;
				n = n->next;
				delete to_delete;
			}
		}

		// De-allocate old_table
		delete[] old_table;
		
	}

	int h = hash(key, size);
	table[h] = new Node(key, table[h]);
}

/* Removes a key.  It is an error if key isn't in the set */
void Stringset::remove(string key)
{
	assert (find(key));
	num_elems--;

	int h = hash(key, size);
	if (table[h]->key == key) {
		// delete first node
		Node *to_delete = table[h];
		table[h] = table[h]->next;
		delete to_delete;
	}
	else {
		// delete from rest of list
		Node *n = table[h];
		while (n->next->key != key) n = n->next;
		Node *to_delete = n->next;
		n->next = to_delete->next;
		delete to_delete;
	}
}

/* prints keys one linked list at a time */
void Stringset::print(void)
{
	for (int i = 0; i < size; i++) {
		Node *n = table[i];
		while (n != NULL) {
			cout << n->key << "\n";
			n = n->next;
		}
	}
}

