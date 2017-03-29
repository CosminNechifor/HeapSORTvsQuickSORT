#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
#define MAX 20
#define TRUE 1

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
}



int main() {
    int firstArray[MAX];
    int secondArray[MAX];
    for (int i = 0; i < MAX ; ++i) {
        firstArray[i] = rand()%(1000) + 1;
        secondArray[i] = firstArray[i];
    }
    cout << "\nInitial array:";
    for (int k = 0; k < 20; ++k) {
        cout << firstArray[k] << " ";
    }

    quickSort(firstArray, 0, MAX-1);

    cout << "\n\nSorted with quicksort!\n";
    for (int k = 0; k < MAX; ++k) {
        cout << firstArray[k] << " ";
    }

    for (int i = 0; i < MAX; ++i) {
        firstArray[i] = secondArray[i];
    }


    heapSort(firstArray, MAX);
    cout << "\n\nSorted with heapsort!\n";
    for (int i = 0; i < MAX; ++i) {
        cout << firstArray[i] << " ";
    }


    return 0;
}