#include <iostream>
using std::cout;
using std::endl;

void quicksort(int* T, int left, int right);
int setPivot(int* T, int left, int right);
void printArray(int* T, int n);

int main(void) {

    int* T = new int[10] {8, 1, 2, 3, 7, 8, 2, 1, 8, 9};
    quicksort(T, 0, 9);
    printArray(T, 10);

    return 0;
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


void quicksort(int* T, int left, int right) {
    if (left < right) {
        int pivot = setPivot(T, left, right);
        quicksort(T, left, pivot - 1);
        quicksort(T, pivot + 1, right);
    }
}


void printArray(int* T, int n) {
    for (int i = 0; i < n; i++) {
        cout << T[i] << " ";
    }
    cout << endl;
}