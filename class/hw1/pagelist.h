#ifndef PAGELIST_H /* Prevent multiple inclusion... */
#define PAGELIST_H

#include <string>
using namespace std;

struct Word {
	string word;
	int val;
	Word *nextWord;
	Word(string w, int v, Word *n) { word = w; val = v; nextWord = n; }
	Word() { word = ""; val = -1; nextWord = NULL; }
};

struct Link {
	string linkURL;
	int val;
	Link *nextLink;
	Link(string l, int v, Link *n) { linkURL = l; val = v; nextLink = n; }
	Link() { linkURL = ""; val = -1; nextLink = NULL; }
};

struct Page {
	string pageURL;
	int val;
	double weight;
	double new_weight;
	Word *WordList;
	int wordcount;
	Link *LinkList;
	int linkcount;
	int valid_links;
	Page(string url, int v) { pageURL = url; val = v; }
};
	
struct URL_ID {
	string pageURL;
	int page_number;
};

class pageList {
	
	private: 
		Page **pages;  	// array of pointers to Pages
		URL_ID **url_ids; // array of pointers to url integer IDs
		Word **word_index;// array of pointers to words
		int size;      	// size of table, as currently allocated
		int index_size;	// size of inverted index
	
	public:
		pageList(int size, int wordcount);
		~pageList();
		int findPage(string key);
		void insertPage(string url, int val);
		void insertLink(string url, int pagenum, int val);
		void insertWord(string word, int pagenum, int val);
		void num_valid_links (int pagecount);
		void assign_weight(int num_pages); 
};

#endif
