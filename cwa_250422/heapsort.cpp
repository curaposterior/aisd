#include <iostream>
using namespace std;

void heapify(int, int, int*);
void buildheap(int, int*);
void heapsort(int, int*);
void swap(int*, int*);
void print(int* T, int n);

int main(void) {
	int pom[10] = { -100,-5,15,8,4,20,2,16,9,7 };
	int* T = pom;
	
	print(T, 10);
	heapsort(10, T);
	print(T, 10);

	system("PAUSE");
	return 0;
}

/*
Zwraca najwiekszy element na gore kopca
*/
void heapify(int o, int heapsize, int* T) { 
	int largest;

	int L = 2 * o;
	int R = 2 * o + 1;
	if (L <= heapsize && T[L] > T[o])
		largest = L;
	else
		largest = o;

	if (R <= heapsize && T[R] > T[largest])
		largest = R;
	if (largest != o) {
		swap(T[o], T[largest]);
		heapify(L, heapsize, T);
	}
}

void buildheap(int heapsize, int* T) {
	for (int i = heapsize; i > 0; i--)
		heapify(i, heapsize, T);
}

/*
Indeksowanie od 1
*/
void heapsort(int size, int* T) {
	int heapsize = size;
	buildheap(heapsize, T);

	for (int i = heapsize-1; i > 0; i--) {
		swap(T[1], T[i]);
		heapify(1, i , T);
	}
}

void swap(int* n1, int* n2) {
	int temp;
	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void print(int* T, int n) {
	for (int i = 0; i < n; i++) {
		cout << *(T + i) << " ";
	}
	cout << endl;
}
