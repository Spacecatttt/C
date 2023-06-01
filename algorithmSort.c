#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithmSort.h"
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void InsertSort(int *arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void CombSort(int *arr, int n)
{
    int gap = n;
    int swapped = 1;
    while (gap != 1 || swapped)
    {
        gap = gap / 1.3;
        if (gap < 1)
            gap = 1;

        swapped = 0;
        for (int i = 0; i + gap < n; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}
void BucketSort(int *arr, int n)
{
    // Determine the maximum and minimum values in the array
    int maxVal = arr[0];
    int minVal = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
        if (arr[i] < minVal)
        {
            minVal = arr[i];
        }
    }
    // Create an array of buckets
    int range = maxVal - minVal + 1;
    int numBuckets = range;
    int *buckets = (int *)malloc(numBuckets * sizeof(int));
    // Initialize each bucket with 0
    for (int i = 0; i < numBuckets; i++)
    {
        buckets[i] = 0;
    }
    // Count the occurrences of each element
    for (int i = 0; i < n; i++)
    {
        buckets[arr[i] - minVal]++;
    }
    // Sort the elements by iterating through the buckets
    int index = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        while (buckets[i] > 0)
        {
            arr[index++] = i + minVal;
            buckets[i]--;
        }
    }
    // Free the memory allocated for the buckets
    free(buckets);
}
void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0, j = 0, k = 0;
    // Merge the subarrays back into arr
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }
    // Copy any remaining elements of left[]
    while (i < leftSize)
    {
        arr[k++] = left[i++];
    }
    // Copy any remaining elements of right[]
    while (j < rightSize)
    {
        arr[k++] = right[j++];
    }
}
void MergeSort(int *arr, int n)
{
    if (n <= 1)
    {
        return; // Base case: array is already sorted
    }
    int mid = n / 2;
    // Create left and right subarrays
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((n - mid) * sizeof(int));
    // Copy data to left and right subarrays
    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < n; i++)
    {
        right[i - mid] = arr[i];
    }

    // Recursive calls to sort the subarrays
    MergeSort(left, mid);
    MergeSort(right, n - mid);

    // Merge the sorted subarrays
    merge(arr, left, mid, right, n - mid);

    // Free the memory allocated for left and right subarrays
    free(left);
    free(right);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void QuickSort(int arr[], int low, int high) {if (low < high) {
        int pivotIndex = partition(arr, low, high);
        QuickSort(arr, low, pivotIndex - 1);
        QuickSort(arr, pivotIndex + 1, high);
    }
}