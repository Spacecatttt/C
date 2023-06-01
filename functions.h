#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "algorithmSort.h"
#include "config.h"

void measureTimeAlgorithm();
void compareAlgorithms();
void printArray(int *arr, int n);

int *chooseArr(int *n);
int chooseSort();
void executeSort(int ch, int *arr, int n);

#endif