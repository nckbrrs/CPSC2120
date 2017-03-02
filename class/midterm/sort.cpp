#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

int main (void) {
	int size = 100000;
	int *nums = new int[size];
	int i=0;

	while (cin >> nums[i]) i++;
	assert (i == size);
	cout << "ints read into array...\n";

	for (int i=0; i<size-1; i++) {
		if (nums[i] > nums[i+1]) {
			int temp = nums[i+1];
			nums[i+1] = nums[i];
			nums[i] = temp;
		}
	}

	for (int i=0; i<size; i++)
		cout << nums[i] << "\n";

	return 0;
}
			
