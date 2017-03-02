#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main (void) {
	int i;

	for (i = 0; i<20; i++) {
		cout << i << "\n";
	}
	
	cout << -100000 << "\n";

	while (i < 99999) {
		cout << i << "\n";
		i++;
	}

	return 0;
}
