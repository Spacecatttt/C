#include "functions.h"

void printArray(int *arr, int n)
{
  if (isPrintArray)
    for (int i = 0; i < n; i++)
    {
      printf("%d ", arr[i]);
    }
  printf("\n");
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