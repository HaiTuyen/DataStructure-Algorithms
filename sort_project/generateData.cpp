#include "generateData.h"
template <class T>
void Swap(T& a, T& b) {
	T x = a;
	a = b;
	b = x;
}

// Function to generate random data array
void GenerateRandomData(int a[], int n) { 
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// Function to generate sorted data array (ascending order) 
void GenerateSortedData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Function to generate reverse sorted data array (descending order)
void GenerateReverseData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Function to generate nearly sorted data array 
void GenerateNearlySortedData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		Swap(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType) {
	switch (dataType)
	{
	case 0:	// Randomized data
		GenerateRandomData(a, n);
		break;
	case 1:	// Sorted data 
		GenerateSortedData(a, n);
		break;
	case 2:	// Reverse sorted data
		GenerateReverseData(a, n);
		break;
	case 3:	// Nearly sorted data
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}
