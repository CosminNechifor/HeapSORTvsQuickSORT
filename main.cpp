#include <iostream>
#include <cstdlib>
#include <cstdio>

#define MAX 20
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


int main() {
    int vector[MAX];
    for (int i = 0; i < MAX ; ++i) {
        vector[i] = rand()%(1000) + 1;
    }
    printf("\n\nVector inainte de QuickSort:");
    for (int k = 0; k < 20; ++k) {
        printf("%d ", vector[k]);
    }

    quickSort(vector, 0, MAX-1);

    printf("\n\nVector dupa QUICKSORT:");
    for (int k = 0; k < 20; ++k) {
        printf("%d ", vector[k]);
    }
    return 0;
}