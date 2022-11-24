#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node {
    int to;
    int dist;
    node* next;
};

struct edge {
    int from;
    int to;
    int dist;
    edge* next;
};

int** readMatrix(fstream &hf, string fname, int** matrix) {
    hf.open(fname);
    if (!hf.good()) {
        cout << "Can't open the file" << endl;
        return nullptr;
    }
    int size;
    hf >> size;

    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    int i = 0, j = 0, n = 0;
    while (hf >> matrix[i][j]) {
        if (++j >= size) {
            j = 0;
            i++;
        }
        n++;
        if (n >= size*size) break;
    }
    hf.close();
    return matrix;
}

void addToEnd(node* &head, int to, int dist) {
    node* p = new node;
    p->to = to;
    p->dist = dist;
    p->next = nullptr;
    if (head == nullptr) head = p;
    else {
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = p;
    }
}

node** createNeighbourList(int** matrix, int size, node** tab) {
    tab = new node*[size] {nullptr};
    for (int i = 0; i < size; i++) {
        node* head = nullptr;
        tab[i] = head;
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != 0) {
                addToEnd(tab[i], j, matrix[i][j]);
            }
        }
    }
    return tab;
}