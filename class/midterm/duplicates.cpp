#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

/* All of the following is the professor's work; I didn't get this working
	at all */
bool compare_files(int x, int y)
{
	ifstream fin1, fin2;
	char filename1[100];
	char filename2[100];
	sprintf (filename1, "/tmp/manyfiles/%d.txt", x);
	sprintf (filename2, "/tmp/manyfiles/%d.txt", y);

	fin1.open(filename1);
	fin2.open(filename2);

	string s1, s2;
	bool same = true;
	for (int i=0; i < 100000; i++) {
		fin1 >> s1;
		fin2 >> s2;
		if (s1 != s2)
		// more stuff... finish copying code from BlackBoard
}

int hash_file (int x)
{
	ifstream fin;
	char filename[100];
	sprintf (filename, "/tmp/manyfiles/%d.txt", x);
	fin.open(filename);

	string s;

	unsigned int i, h = 0;

	while (fin >> s) {
		for (i=0; i<s.length(); i++)
			h = (h * 2917 + (unsigned int)s[i]) % 1000000;
	}

	fin.close();
	return h;
}

int main(void)
{
	int N = 10000;
	int *H = new int[N];
	for (int i=0; i<N; i++) {
		if (i % 100 == 0)	
			cout << i << "\n"; // prints every 100th element...
		H[i] = hash_file(i);
	}	


	fin.close();
	}
	return 0;
}
