#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
#define MAX 10000
#define TRUE 1

int comparisonHeapSort, comparisonQuickSort;
int assignmentsHeapSort, assignmentsQuickSort;
FILE *fileQuickSort = fopen("../HeapSort.txt", "w");
FILE *fileHeapSort = fopen("../QuickSort.txt", "w");

void quickSort(int vector[], int left, int right){
    int temp, min, max, mid;
    mid = vector[left + (right - left)/2];
    min = left;
    max = right;
    do{
        while (vector[min] < mid) min++;
        while (vector[max] > mid) max--;

        if (min <= max){
            temp = vector[min];
            vector[min++] = vector[max];
            vector[max--] = temp;
        }
    }while(min < max);
    if (left < max) quickSort(vector, left, max);
    if (right > min) quickSort(vector, min, right);

    int sum = comparisonQuickSort + assignmentsQuickSort;
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sum);
}


int max (int *array, int size, int i, int left, int right) {
    int index = i;
    if (left < size && array[left] > array[index]) {
        index = left;
    }
    if (right < size && array[right] > array[index]) {
        index = right;
    }
    return index;
}

void heapify(int *array, int size, int i) {
    while (TRUE) {
        int maxIndex = max(array, size, i, 2 * i + 1, 2 * i + 2);
        if (maxIndex == i) {
            break;
        }
        int temp = array[i];
        array[i] = array[maxIndex];
        array[maxIndex] = temp;
        i = maxIndex;
    }
}


void heapSort(int *array, int size) {
    int i;
    for (i = (size - 2) / 2; i >= 0; i--) {
        heapify(array, size, i);
    }
    for (i = 0; i < size; i++) {
        ///Swap
        int temp = array[size - i - 1];
        array[size - i - 1] = array[0];
        array[0] = temp;
        ///recall
        heapify(array, size - i - 1, 0);
    }
    int sum = comparisonHeapSort + assignmentsHeapSort;
    fprintf(fileHeapSort, "%d,%d,%d\n", comparisonHeapSort, assignmentsHeapSort, sum);
}

void generateAvgCase(int arraySize){
    int firstArray[arraySize];
    int secondArray[arraySize];

    /**
     *  I keep track with comparison, and assignment numbers of each algorithm.
     * **/
    comparisonHeapSort = 0;
    comparisonQuickSort = 0;
    assignmentsHeapSort = 0;
    assignmentsQuickSort = 0;

    for (int i = 0; i < arraySize; ++i) {
        firstArray[i] = rand()%(MAX) + 1;
        secondArray[i] = firstArray[i];
    }

    heapSort(firstArray, arraySize);

    for (int i = 0; i < arraySize; ++i) {
        firstArray[i] = secondArray[i];
    }

    quickSort(firstArray, 0, arraySize - 1);
}



int main() {
    for (int i = 100; i < MAX ; i+=100) {
        generateAvgCase(i);
    }
    
    return 0;
}