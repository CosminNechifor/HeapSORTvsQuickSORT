#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
#define MAX 10000
#define TRUE 1

int comparisonHeapSort, comparisonQuickSort;
int assignmentsHeapSort, assignmentsQuickSort;
FILE *fileHeapSort = fopen("../HeapSort.txt", "w");
FILE *fileQuickSort = fopen("../QuickSort.txt", "w");

void quickSort(int array[], int left, int right){
    int temp, min, max, mid;
    mid = array[left + (right - left)/2];
    assignmentsQuickSort++;
    min = left;
    max = right;
    do{
        while (array[min] < mid) {
            min++;
            comparisonQuickSort++;
        }

        while (array[max] > mid) {
            max--;
            comparisonQuickSort++;
        }


        if (min <= max){
            temp = array[min];
            array[min++] = array[max];
            array[max--] = temp;
            assignmentsQuickSort+=3;

        }
    }while(min < max);
    if (left < max) quickSort(array, left, max);
    if (right > min) quickSort(array, min, right);
}


int max(int *array, int size, int i, int left, int right) {
    int index = i;
    if (left < size && array[left] > array[index]) {
        comparisonHeapSort++;
        index = left;
    }
    if (right < size && array[right] > array[index]) {
        comparisonHeapSort++;
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
        assignmentsHeapSort += 3;
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
        assignmentsHeapSort += 3;
        ///recall
        heapify(array, size - i - 1, 0);
    }
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
    int sumHeapSort = comparisonHeapSort + assignmentsHeapSort;
    fprintf(fileHeapSort, "%d,%d,%d\n", comparisonHeapSort, assignmentsHeapSort, sumHeapSort);

    for (int i = 0; i < arraySize; ++i) {
        firstArray[i] = secondArray[i];
    }

    quickSort(firstArray, 0, arraySize - 1);
    int sumQuickSort = comparisonQuickSort + assignmentsQuickSort;
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sumQuickSort);
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
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sum);

}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition_worst(int *array, int low, int high)
{
    int pivot = array[high];    // pivot
    assignmentsQuickSort++;
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (array[j] <= pivot)
        {
            comparisonQuickSort++;
            i++;    // increment index of smaller element
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            assignmentsQuickSort += 3;
        }
    }
    int temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;
    assignmentsQuickSort += 3;
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort_worst(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition_worst(arr, low, high);

        // Separately sort elements before
        // partition and after partition_worst
        quickSort_worst(arr, low, pi - 1);
        quickSort_worst(arr, pi + 1, high);
    }
}

void generateWorst_QuickSort(int arraySize){
    int array[arraySize];

    comparisonHeapSort = 0;
    comparisonQuickSort = 0;
    assignmentsHeapSort = 0;
    assignmentsQuickSort = 0;

    /**
     * Worst case is when the array is sorted in descending order
     * **/
    int number = arraySize;

    for (int i = 0; i < arraySize; ++i) {
        array[i] = number;
        number--;
    }

    quickSort_worst(array, 0, arraySize-1);

    int sum = comparisonQuickSort + assignmentsQuickSort;
    fprintf(fileQuickSort, "%d,%d,%d\n", comparisonQuickSort, assignmentsQuickSort, sum);
}



///partition used at quick select
int partition(int* array, int left, int right)
{
    int pivot = array[right];

    while ( left < right )
    {
        while ( array[left] < pivot )
            left++;

        while ( array[right] > pivot )
            right--;

        if ( array[left] == array[right] )
            left++;
        else if ( left < right ) {
            int tmp = array[left];
            array[left] = array[right];
            array[right] = tmp;
        }
    }
    return right;
}

///quick select
int quick_select(int* array, int left, int right, int k)
{
    if ( left == right )
        return array[left];

    int j = partition(array, left, right);
    int length = j - left + 1;

    if ( length == k )
        return array[j];
    else if ( k < length )
        return quick_select(array, left, j - 1, k);
    else
        return quick_select(array, j + 1, right, k - length);
}


int main() {
    fprintf(fileQuickSort, "\nQuickSort Avg case\n");
    fprintf(fileHeapSort, "\nHeapSort Avg case\n");
    for (int i = 100; i < MAX ; i+=100) {
        //printf("\n%d", i);
        generateAvgCase(i);
    }

    fprintf(fileQuickSort, "\nQuickSort Best case\n");
    for (int i = 100; i < MAX; i+=100) {
        //printf("\n%d", i);
        generateBest_QuickSort(i);
    }

    fprintf(fileQuickSort, "\n\nQuickSort Worst case\n");
    for (int i = 0; i < MAX; i += 100) {
        //printf("\n%d", i);
        generateWorst_QuickSort(i);
    }

//    int array[] = {12, 11, 5, 3, 20, 1};
//    printf("Second elemnt is %d.", quick_select(array, 0, 5, 2));

    return 0;
}