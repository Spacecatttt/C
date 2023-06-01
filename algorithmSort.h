#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);
void InsertSort(int *arr, int n);
void CombSort(int *arr, int n);
void BucketSort(int *arr, int n);
void MergeSort(int *arr, int n);
void merge(int arr[], int left[], int leftSize, int right[], int rightSize);
int partition(int arr[], int low, int high);
void QuickSort(int arr[], int low, int high);

#endif