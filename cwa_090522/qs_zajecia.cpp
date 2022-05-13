#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

/*
TODO:
- quicksort z mediana elementow
- quicksort hybrydowy:
    - dodanie warunku na koniec
    - sortowanie quicksortem jak jest mala tablica

*/

int* readNumbers(string filename);
void swap(int *xp, int *yp);
void bubbleSort(int* arr, int n, int l, int p); //zobaczyc czy dziala
void printArray(int* T, int n);
int setPivot(int* T, int left, int right);
void quickSortHybrid(int* T, int left, int right);
void quicksort(int* t, int left, int right);

int main(void) {
    int* T = readNumbers("numbers.txt");
    clock_t tStart = clock();
    quicksort(T, 0, 99999);
    printf("Czas wykonania: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    // printArray(T, n);


    return 0;
}


void printArray(int* T, int n) {
    for (int i = 0; i < n; i++) {
        cout << T[i] << " ";
    }
    cout << endl;
}


void bubbleSort(int* arr, int l, int p) {
   int i, j;
   int n = p + 1;
   bool swapped;
   for (i = l; i < p+1; i++)
   {
     swapped = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(arr[j], arr[j+1]);
           swapped = true;
        }
     }
  
     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
   }
}


void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


int setPivot(int* T, int left, int right) {
    int border = left;
    int pivot = right;
    for (int i = left; i < right; i++) {
        if (T[i] < T[pivot]) {
            int swap = T[i];
            T[i] = T[border];
            T[border] = swap;
            border = border + 1;
        }
    }
    int swapPivot = T[border];
    T[border] = T[pivot];
    T[pivot] = swapPivot;

    return border;
}


void quickSortHybrid(int* T, int left, int right) {
    if (left - right > 10) {
        int pivot = setPivot(T, left, right);
        quickSortHybrid(T, left, pivot - 1);
        quickSortHybrid(T, pivot + 1, right);
    }
    else {
        bubbleSort(T, left, right);
    }
}

void quicksort(int* T, int left, int right) {
    if (left < right) {
        int pivot = setPivot(T, left, right);
        quicksort(T, left, pivot - 1);
        quicksort(T, pivot + 1, right);
    }

}

int* readNumbers(string filename) {
    fstream myfile(filename, std::ios_base::in);

    int* T = new int(100001);
    int a,i;
    i = 0;
    while (myfile >> a && i != 100001) {
        T[i] = a;
    }
    myfile.close();
    return T;
}