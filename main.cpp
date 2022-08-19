#include <iostream>
#include <chrono>
#include "generateData.h"
#include "sortAlgorithm.h"
using namespace std;
using namespace std::chrono;

int main()
{
	//Selection Sort:
	int arr[10] = { 0 };
	int n = 10;
	int compare = 0;
	GenerateData(arr, n, 4);
	auto start = high_resolution_clock::now();
	selectionSort(arr, n, compare);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	printArray(arr, n);
	cout << "\nTime taken by function: " << duration.count() << " miliseconds" << endl;
	cout << "Number of comparisions: " << compare << endl;


	/*
	Insertion Sort:

	int arr[10] = { 0 };
	int n = 10;
	int compare = 0;
	GenerateData(arr, n, 1);
	auto start = high_resolution_clock::now();
	insertionSort(arr, n, compare);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	printArray(arr, n);
	cout << "\nTime taken by function: " << duration.count() << " miliseconds" << endl;
	cout << "Number of comparisions: " << compare << endl;
	*/

	/*int arr[10] = { 0 };
	int n = 10;
	int compare = 0;
	GenerateData(arr, n, 0);
	auto start = high_resolution_clock::now();
	bubbleSort(arr, n, compare);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	printArray(arr, n);
	cout << "\nTime taken by function: " << duration.count() << " miliseconds" << endl;
	cout << "Number of comparisions: " << compare << endl;*/

	return 0;
}