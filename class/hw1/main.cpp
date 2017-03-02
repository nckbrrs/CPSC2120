/*
	Nicholas Barrs
	nbarrs	
	CPSC 2121-001
	20 September 2015
	main.cpp - main file for hw1
*/

#include <string>
#include <fstream>
#include <iostream>
#include "pagelist.h"

using namespace std;

int main(void)
{
	ifstream fin1;
	ifstream fin2;
	string s1;
	string s2;
	int pagecount = 0;
	int linkcount = 0;
	int wordcount = 0;
	int currentpage = -1;

	fin1.open("webpages.txt");
	
	// first read-through to get size...
	while (fin1 >> s1) {
		if (s1 == "NEWPAGE") pagecount++;
		else if (s1[0]=='h'&&s1[1]=='t'&&s1[2]=='t'&& s1[3]=='p') linkcount++;
		else wordcount++;
	}
	cout << "first run complete \npagecount is " << pagecount << "\n";
	cout << "linkcount is " << linkcount << "\n";
	cout << "wordcount is " << wordcount << "\n";

	
	// allocate array of pages...
	pageList P(pagecount, wordcount);
	cout << "allocated array of pages... \n";
				
	fin1.close();

	// fill array...
	fin2.open("webpages.txt");

	while (fin2 >> s2) {
		if (s2 == "NEWPAGE") {
			currentpage++;
			fin2 >> s2;
			P.insertPage(s2, currentpage);
			linkcount = 0;
			wordcount = 0;
		}
		else if (s2[0] == 'h' && s2[1] == 't' && s2[2] == 't' && s2[3] == 'p') {
			P.insertLink(s2, currentpage, linkcount);
			linkcount++;
		}
		else {
			P.insertWord(s2, currentpage, wordcount);
			wordcount++;	
		}
	}

	cout << "array filled... \n";
	
	fin2.close();

	// assign weights to pages
	cout << "pagecount is " << pagecount << "\n";
	P.assign_weight(pagecount);
	cout << "weights assigned... \n";
	cout << "pagelist deconstructed... \n";
	
	return 0;
}
