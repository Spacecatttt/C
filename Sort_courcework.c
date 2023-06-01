#include "functions.h"
#include "algorithmSort.h"

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