/*
	Nicholas Barrs	
	nbarrs
	CPSC 2121-001
	20 September 2015
	pagelist.cpp - function implementations for mini search engine
*/

#include <iostream>
#include <string.h>
#include <assert.h>
#include "pagelist.h"

using namespace std;

/* Return a hash for the string s in the range 0..pageList_size-1 */
int hash(string s, int pages_size)
{
	unsigned int i, h = 0;
	for (i=0; i<s.length(); i++)
		h = (h * 2917 + (unsigned int)s[i]) % pages_size;
	
	return h;
}

/* Allocate a table of pointers to nodes, all initialized to NULL */
Page **allocate_pageList(int size)
{
	Page **pages = new Page *[size];
	for (int i=0; i<size; i++) pages[i] = NULL;
	return pages;
}

URL_ID **allocate_url_id_list(int size)
{
	URL_ID **url_ids = new URL_ID *[size];
	for (int j = 0; j<size; j++) url_ids[j] = NULL;
	return url_ids;
}

Word **allocate_word_index(int size)
{	
	Word **word_index = new Word *[size];
	for (int w = 0; w < size; w++) word_index[w] = NULL;
	return word_index;
}

pageList::pageList(int pagecount, int wordcount)
{
	size = pagecount;
	index_size = wordcount;

	pages = allocate_pageList(size);
	url_ids = allocate_url_id_list(size);
	word_index = allocate_word_index(index_size);
}

pageList::~pageList()
{
	cout << "in deconstructor... \n";

	for (int i = 0; i < size; i++) {
		while (pages[i]->WordList != NULL) {
			Word *temp = pages[i]->WordList;
			pages[i]->WordList = pages[i]->WordList->nextWord;
			delete temp;
		}
		while (pages[i]->LinkList != NULL) {
			Link *temp = pages[i]->LinkList;
			pages[i]->LinkList = pages[i]->LinkList->nextLink;
			delete temp;
		}
	}

	delete[] url_ids;
	cout << "url_ids deleted. \n";
	delete[] pages;
	cout << "pages deleted. \n";
	
}


/* Return page number that corresponds to key, if it exists in pages */
int pageList::findPage(string key)
{
	int h = hash(key, size);
	URL_ID *i = url_ids[h];

	if (i == NULL) return -1;
	else if (i->pageURL == key) return i->page_number;
	else return -1;
}

/* Inserts a new page.  It is an error if url is already in pages. */
void pageList::insertPage(string url, int pagenum)
{
	assert (findPage(url) == -1);

	//inserts new element
	int val = hash(url, size);
	Page *newPage = new Page(url, val);
	newPage->LinkList = NULL;
	newPage->WordList = NULL;
	newPage->wordcount = 0;
	newPage->linkcount = 0;
	pages[pagenum] = newPage;
	
	URL_ID *newURL = new URL_ID;
	newURL->pageURL = url;
	newURL->page_number = pagenum;
	url_ids[val] = newURL;

	return;
}

void pageList::insertLink(string url, int pagenum, int val)
{
	assert (pages[pagenum] != NULL);
	Link *newLink = new Link;
	newLink->linkURL = url;
	newLink->val = val;
	newLink->nextLink = pages[pagenum]->LinkList;
	(pages[pagenum]->linkcount)++;
	pages[pagenum]->LinkList = newLink;
	return;
}

void pageList::insertWord(string word, int pagenum, int val)
{
	Word *newWord = new Word(word, val, pages[pagenum]->WordList);
	(pages[pagenum]->wordcount)++;
	pages[pagenum]->WordList = newWord;
	return;
}

void pageList::assign_weight(int pagecount)
{
	cout << "in assign_weight... \n";
	int valid_links = 0;
	cout << "pagecount is " << pagecount << "\n";
	
	// initialize each pages weight to 1 / number of pages
	for (int w = 0; w < pagecount; w++) {
		pages[w]->weight = (1 / pagecount);
	}

	// weight algorithm
	for (int a = 0; a < 50; a++) {
		for (int i = 0; i < pagecount; i++) {
			Page *p = pages[i];
			p->new_weight = (0.1 / pagecount);	
		
			// find how many valid links are in each page's list of links
			num_valid_links(pagecount);
			
			// increase each valid link's new_weight
			while (p->LinkList != NULL) {
				int h = hash(p->LinkList->linkURL, size);
				if (url_ids[h] == NULL) {
					break;
				}
				if (url_ids[h]->pageURL == p->LinkList->linkURL) {
					pages[(url_ids[h]->page_number)]->new_weight += 
											((0.9 * p->weight) / p->valid_links);
					p->LinkList = p->LinkList->nextLink;
				}
				else {
					p->LinkList = p->LinkList->nextLink;
				}

			}
			p->weight = p->new_weight;
		}
	}
	return;
}

void pageList::num_valid_links(int pagecount)
{
	for (int i = 0; i < pagecount; i++) {
		Page *p = pages[i];
		int h = hash(p->LinkList->linkURL, size);
		if (url_ids[h] == NULL || p->LinkList == NULL) return;
		if (url_ids[h]->pageURL == p->LinkList->linkURL) {
			(p->valid_links) += 1;
		}
		p->LinkList = p->LinkList->nextLink;
	}
}
