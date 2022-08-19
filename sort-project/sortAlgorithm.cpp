#include "sortAlgorithm.h"

void selectionSort(int arr[], int n , int& count_compare)
{
    int i, j, min_idx;
    // One by one move boundary of
    // unsorted subarray
    
    for (i = 0; ++count_compare && i < n - 1; i++)
    {
        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; ++count_compare && j < n; j++)
            if (++count_compare && arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        Swap(arr[min_idx], arr[i]);
    }
}

// Function to sort an array using insertion sort
void insertionSort(int arr[], int n, int& count_compare)
{
    int i, key, j;
    for (i = 1; ++count_compare && i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        // Move elements of arr[0..i-1],that are greater than key, to one
        // position ahead of their current position
        while ((++count_compare && j >= 0) && (++count_compare && arr[j] > key))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n, int& count_compare)
{
    int i, j;
    for (i = 0; ++count_compare && i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; ++count_compare && j < n - i - 1; j++)
            if (++count_compare && arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

//Function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
