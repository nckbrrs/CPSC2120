/*
	Nicholas Barrs
	nbarrs	
	CPSC 2121-001
	1 September 2015
	main.cpp - includes main function for lab 2, spellcheck, which compares
	user-inputted strings to a bank of word in words.txt and prints words whose
	spelling is only one letter off
*/

#include <string>
#include <fstream>
#include <iostream>
#include "stringset.h"

using namespace std;

void spellcheck(void)
{
	Stringset S;
	string word;

	ifstream wordfile("words.txt");
	while (wordfile >> word)
		S.insert(word);
	wordfile.close();

	cout << "Dictionary loaded.  Please enter words to spell check.\n";

	while (cin >> word) {
	cout << "Possible alternatives for word '" << word << "':\n";
		for (int i = 0; i < word.length(); i++) {
			char old_char = word[i];
			for (char c = 'a'; c <= 'z'; c++) {
				word[i] = c;
				if (c != old_char && S.find(word)) { cout << word << endl; }
			}
			word[i] = old_char;
		}
	}
}

void test(void)
{
  Stringset S;
  string key, command;

  while(cin >> command) {
    
    if (command == "insert") {
      
      cin >> key;
      if (S.find(key))
	cout << "Error!  Key " << key << " already in structure!\n";
      else
	S.insert(key);

    } else if (command == "remove") {
      
      cin >> key;
      if (!S.find(key)) 
	cout << "Error!  Key " << key << " not in structure!\n";
      else
	S.remove(key);

    } else if (command == "find") {

      cin >> key;
      if (S.find(key))
	cout << "Key " << key << " present.\n";
      else
	cout << "Key " << key << " absent.\n";

    } else if (command == "print") {

      cout << "Contents of structure:\n";
      S.print();

    } else if (command == "quit") {

      break;

    } else {

      cout << "Error!  Unknown command '" << command << "'!\n";

    }
  }
}

int main(void)
{
	//test();
	spellcheck();
	return 0;
}
