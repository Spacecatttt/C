#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//**********************************************************************************************
//0 - to not view array before and after sorting
//1 - to view array before and after sorting
int isPrintArray = 0;

void swap(int *a, int *b);
void InsertSort(int *arr, int n);
void CombSort(int *arr, int n);
void BucketSort(int *arr, int n);
void MergeSort(int *arr, int n);
void merge(int arr[], int left[], int leftSize, int right[], int rightSize);
int partition(int arr[], int low, int high);
void QuickSort(int arr[], int low, int high);

void executeSort(int ch, int *arr, int n);
void printArray(int *arr, int n);

int chooseSort()
{
  int choice;
  while (1)
  {
    printf("1. Insert sort\n");
    printf("2. Comb sort\n");
    printf("3. Bucket sort\n");
    printf("4. Merge sort\n");
    printf("5. Quick sort\n");
    printf("0. Exit\n");
    scanf("%d", &choice);
    if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5)
      return choice;
    else if (choice == 0)
      return 0;
    else
    {
      printf("Invalid choice. Please try again.\n");
      fflush(stdin);
      printf("\n--- Choose algorithm sort ---\n");
    }
  }
}
int *chooseArr(int *n)
{
  int choice;
  int *arr = NULL;
  while (1)
  {
    printf("\n--- Enter regime ---\n");
    printf("1. To enter the array manually\n");
    printf("2. To generate it automatically\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("Enter the number of elements: ");
      scanf("%d", n);

      arr = malloc((*n) * sizeof(int));
      printf("Enter the elements: \n");
      for (int i = 0; i < *n; i++)
      {
        scanf("%d", &arr[i]);
      }
      return arr;
    case 2:
      printf("Enter the number of elements: ");
      scanf("%d", n);

      arr = malloc((*n) * sizeof(int));
      srand(time(0));
      for (int i = 0; i < *n; i++)
      {
        arr[i] = rand() % 100; // Generating random numbers between 0 and 99
      }
      printf("Your array: ");
      printArray(arr, *n);
      return arr;
    default:
      printf("Invalid choice. Exiting...\n");
      fflush(stdin);
      break;
    }
  }
}
void measureTimeAlgorithm()
{
  printf("\n--- Choose algorithm sort ---\n");
  int ch = chooseSort();
  if (ch == 0)
    return;
  int num = 0;
  int *arr = chooseArr(&num);
  clock_t start, end;
  double cpu_time_used;

  start = clock(); // Start the timer
  executeSort(ch, arr, num);
  end = clock(); // Stop the timer
  cpu_time_used = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;

  printf("Execution time: %f miliseconds\n", cpu_time_used);
  printf("Sorted array: ");
  printArray(arr, num);
  free(arr); // Free the memory allocated for the array
}
void compareAlgorithms()
{
  int first;
  int second;
  printf("\n--- Choose first algorithm sort ---\n");
  first = chooseSort();
  if (first == 0)
    return;
  printf("\n--- Choose second algorithm sort ---\n");
  second = chooseSort();
  if (second == 0)
    return;
  int n = 0;
  int *firstArray = chooseArr(&n);
  int *secondArray = malloc(n * sizeof(int));
  // copy array
  for (int i = 0; i < n; i++)
  {
    secondArray[i] = firstArray[i];
  }

  clock_t start, end;

  start = clock(); // Start the timer
  executeSort(first, firstArray, n);
  end = clock(); // Stop the timer
  double cpu_time_used1 = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;

  start = clock(); // Start the timer
  executeSort(second, secondArray, n);
  end = clock(); // Stop the timer
  double cpu_time_used2 = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;

  printf("Execution time the first algorithm: %f miliseconds\n", cpu_time_used1);
  printf("Execution time the second algorithm: %f miliseconds\n", cpu_time_used2);

  printf("The array is sorted by the first algorithm: ");
  printArray(firstArray, n);
  printf("The array is sorted by the second algorithm: ");
  printArray(secondArray, n);

  // Free the memory allocated for the array
  free(firstArray);
  free(secondArray);
}
int main()
{
  int choice;
  while (1)
  {
    printf("\n--- Menu ---\n");
    printf("1. Measure time for an algorithm\n");
    printf("2. Compare two algorithms\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      measureTimeAlgorithm();
      break;
    case 2:
      compareAlgorithms();
      break;
    case 0:
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
      fflush(stdin);
      break;
    }
  }
  return 0;
}

void executeSort(int ch, int *arr, int n)
{
  switch (ch)
  {
  case 1:
    InsertSort(arr, n);
    break;
  case 2:
    CombSort(arr, n);
    break;
  case 3:
    BucketSort(arr, n);
    break;
  case 4:
    MergeSort(arr, n);
    break;
  case 5:
    QuickSort(arr, 0, n - 1);
    break;
  }
}
void printArray(int *arr, int n)
{
  if (isPrintArray)
    for (int i = 0; i < n; i++)
    {
      printf("%d ", arr[i]);
    }
  printf("\n");
}
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

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}
void QuickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int pivotIndex = partition(arr, low, high);
    QuickSort(arr, low, pivotIndex - 1);
    QuickSort(arr, pivotIndex + 1, high);
  }
}