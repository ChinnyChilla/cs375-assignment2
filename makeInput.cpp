#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
// testing
	// open an inputfile
	FILE* file = fopen("input.txt", "w");
	if (file == NULL) {
		printf("Error opening file\n");
		return 1;
	}
	int n = 10000;

	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
			continue;
		fprintf(file, "%d %f %d\n", i, sqrt(pow(9999, 2) - pow(i - 10000, 2)), i);
	};
}