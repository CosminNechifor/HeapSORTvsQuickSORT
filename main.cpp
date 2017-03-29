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
}


int max(int *array, int size, int i, int left, int right) {
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
    int sum = comparisonQuickSort + assignmentsQuickSort;
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sum);
}

void generateWorst_QuickSort(int arraySize){
    int firstArray[arraySize];

    comparisonHeapSort = 0;
    comparisonQuickSort = 0;
    assignmentsHeapSort = 0;
    assignmentsQuickSort = 0;

    /**
     * Worst case is when the array is sorted in descending order
     * **/

    int number = 0;
    for (int i = 0; i < arraySize / 2; ++i) {
        firstArray[i] = number;
        number++;
    }

    firstArray[arraySize/2] = number;
    number--;
    for (int i = arraySize/2 + 1; i < arraySize; ++i) {
        firstArray[i] = number;
        number--;
    }

    quickSort(firstArray, 0, arraySize-1);
    int sum = comparisonQuickSort + assignmentsQuickSort;
    fprintf(fileQuickSort, "\nQuickSort Worst case\n");
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sum);
}

void generateBest_QuickSort(int arraySize){
    int firstArray[arraySize];

    comparisonHeapSort = 0;
    comparisonQuickSort = 0;
    assignmentsHeapSort = 0;
    assignmentsQuickSort = 0;

    for (int i = 0; i < arraySize; ++i) {
        firstArray[i] = i;
    }

    quickSort(firstArray, 0, arraySize - 1);

    int sum = comparisonQuickSort + assignmentsQuickSort;
    fprintf(fileQuickSort, "\nQuickSort Best case\n");
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sum);

}

int main() {

    for (int i = 100; i < MAX ; i+=100) {
        printf("\n%d", i);
        generateAvgCase(i);
    }

    for (int i = 100; i < MAX; i+=100) {
        printf("\n%d", i);
        generateBest_QuickSort(i);
    }

    for (int i = 0; i < MAX; i += 100) {
        printf("\n%d", i);
        generateWorst_QuickSort(i);
    }


    return 0;
}