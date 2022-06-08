#include <iostream>
#include <fstream>

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

//dziena: https://github.com/DarkRec/Algo/ (shout-out to jakub)

int** readMatrix(fstream &plik, string fname, int** matrix);
edge* readEdgeList(fstream &hf, string fname);
node** createNeighbourList(int** matrix, int size, node** tab);
int** listToMatrix(node** head, int size, int** matrix);
int** edgeListToMatrix(edge* head, int** matrix, int size);
edge* matrixToEdgeList(int** matrix, int size, edge* head);

//prim algorithm
edge* prim(node** List, int size, int s);
node* searchMin(node* List, int* Color);
node* searchMax(node* list, int* Color);

//algorytm kruskala
void Del(edge *&H);
void swap(edge* &head);
void BubbleSort(edge* &H);
void removeDuplicates(edge* &head);
edge* kruskal(edge* List, int size);

void addToEnd(node* &head, int to, int dist);
void addEdge(edge* &head, int from, int to, int dist);
void show(node* head);
void showNTab(node** head, int size);
void showEdgeList(edge* head);
int edgeLength(edge* edgeList);
void printMatrix(int** matrix, int n);
void fillMatrixWithZeros(int** matrix, int n);


int main(void) {
    fstream plik;
    const int size = 8;
    int** matrix = readMatrix(plik, "data.txt", matrix);
    printMatrix(matrix, 8);
    node** head = createNeighbourList(matrix, size, head);
    showNTab(head, size);
    edge* primTable = prim(head, size, 2);
    cout << "Prim table" << endl;
    showEdgeList(primTable);

    edge* edgeList = matrixToEdgeList(matrix, size, edgeList);
    BubbleSort(edgeList);
    edge* kruskalTab = kruskal(edgeList, size);
    cout << "Kruskal table" << endl;
    showEdgeList(kruskalTab); 
    return 0;
}

int** readMatrix(fstream &hf, string fname, int** matrix) {
    hf.open(fname);
    if (!hf.good()) {
        cout << "Can't open the file" << endl;
        return nullptr;
    }
    int size;
    hf >> size;

    matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
    }

    int i = 0, j = 0, n = 0;
    while (hf >> matrix[i][j]) {
        if (++j >= size) {
            j = 0;
            i++;
        }
        n++;
        if (n>=size*size) break;
    }
    hf.close();
    return matrix;
}

edge* readEdgeList(fstream &hf, string fname) {
    hf.open(fname);
    if (!hf.good()) {
        cout << "Odmowa dostępu..." << endl;
        return nullptr;
    }
    edge* head = nullptr;
    int size = 0, el1 = 0, el2 = 0, el3 = 0;

    hf >> size;
    while (hf) {
        //wczytaj po kolei index/too/dystans
        hf >> el1;
        hf >> el2;
        hf >> el3;
        addEdge(head, el1, el2, el3);
    }
    return head;
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void fillMatrixWithZeros(int** wsk, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            wsk[i][j] = 0;
        }
    }
}

void addToEnd(node* &head, int to, int dist) {
    node* p = new node;
    p->to = to;
    p->dist = dist;
    p->next = nullptr;
    if (head == nullptr) head = p;
    else {
        node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
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

//wypisywanie listy
void show(node* head) {
    cout << "H->";
    node* p = head;
    while (p != nullptr) {
        cout << p->to+1 << "/" << p->dist << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

//wypisywanie listy sasiedztwa
void showNTab(node** head, int size) {
    for (int i = 0; i < size; i++) {
        show(head[i]);
    }
    cout << endl;
}

void addEdge(edge* &head, int from, int to, int dist) {
    edge* temp = new edge;

    temp->from = from;
    temp->to = to;
    temp->dist = dist;
    temp->next = nullptr;

    if (!head) {
        head = temp;
        return;
    }
    else {
        edge* last = head;
        while (last->next) last = last->next;
        last->next = temp;
    }
}

void showEdgeList(edge* head) {
    edge* p = head;
    cout << "H -> ";
    while (p != nullptr) {
        cout << p->from+1 << "/" << p->to+1 << "/" << p->dist << " -> ";
        p = p->next;
    }
    cout << "NULL" << endl;
}

int** edgeListToMatrix(edge* head, int** matrix, int size) {
    if (head == nullptr) {
        cout << "Lista jest pusta" << endl;
        return nullptr;
    }

    matrix = new int*[size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new int[size];
    fillMatrixWithZeros(matrix, size);
    
    edge* p = head;
    while (p != nullptr) {
        matrix[p->from][p->to] = p->dist;
        p = p->next;
    }
    return matrix;
}

int edgeLength(edge* edgeList) {
    edge* p = edgeList;
    int size = 0;
    while (p) {
        size++;
        p = p->next;
    }
    return size;
}

int** listToMatrix(node** head, int size, int** matrix) {
    matrix = new int*[size]; //row
    for (int i = 0; i < size; ++i)
        matrix[i] = new int[size];  //col

    fillMatrixWithZeros(matrix, size);

    for (int i = 0; i < size; i++) {
        node* p = nullptr;
        p = head[i];
        while (p != nullptr) {
            matrix[i][p->to] = p->dist;
            p = p->next;
        }
    }
    return matrix;
}

node **EdgeListToList(edge *EdgeList, int size) {// convert edgelist to matrix 
    edge *p = EdgeList;
    node **LS = new node *[size];
    for (int i = 0; i < size; i++)
        LS[i] = NULL;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (p->from == i && p->to == j)
            {
                addToEnd(LS[i], j, p->dist);
                if (p->next)
                    p = p->next;
            }
        }
    return LS;
}

edge* prim(node** List, int size, int s) {
    edge* tabToReturn = nullptr;
    int* colorTable = new int[size] {0};
    colorTable[s] = 1;

    node* min = searchMin(List[s], colorTable);
    colorTable[min->to] = 1;
    addEdge(tabToReturn, s, min->to, min->dist);
    
    while (edgeLength(tabToReturn) != size - 1) {
        node *MIN = new node;
        MIN->dist = 0;
        int pos;
        node *MinList = nullptr;
        for (int i = 0; i < size; i++)
        {
            if (colorTable[i] == 1)
            {
                node *NewMin = searchMin(List[i], colorTable);
                if (NewMin == nullptr)
                    continue;
                if (MIN->dist > NewMin->dist || MIN->dist == 0)
                {
                    MIN = NewMin;
                    pos = i;
                }
            }
        }
        colorTable[MIN->to] = 1;
        addEdge(tabToReturn, pos, MIN->to, MIN->dist);
    }
    return tabToReturn;
}

node* searchMax(node* List, int* Color) {
    node* p = List;
    node* max = new node;
    max->dist = 0;
    while (p) {
        if (max->dist < p->dist && Color[p->to] == 0)
            max = p;
        p = p->next;
    }
    if (max->dist == 0)
        return nullptr;
    return max;
}

node* searchMin(node* List, int* Color) {
    node* p = List;
    node* max = searchMax(List, Color);
    if (max == nullptr) return nullptr;

    node* min = max;
    for (int i = 0; p; i++, p = p->next) {
        if (min->dist > p->dist && Color[p->to] == 0)
            min = p;
    }
    return min;
}

//algorytm kruskala ---------------------------------------------------------
void swap(edge* &head) {
    if (head && head->next) {
        edge* e = head->next;
        head->next = head->next->next;
        e->next = head->next->next;
        head->next->next = e;
    }
}

void Del(edge *&H)
{
    if (H != NULL)
    {
        edge *p = H;
        H = p->next; // H = H->next
        delete p;
    }
}

void BubbleSort(edge *&H)
{
    if (H != NULL && H->next != NULL)
    {
        edge *last = NULL;
        edge *p = H;
        while (p->next != last)
        {
            edge *p = H;
            while (p->next->next != last)
            {
                if (p->next->dist > p->next->next->dist)
                {
                    swap(p);
                }
                p = p->next;
            }
            last = p->next;
        }
    }
    Del(H);
}

void removeDuplicates(edge* &head) {
    edge *p, *q, *dup;
    p = head;
    while (p != nullptr && p->next != nullptr) {
        q = p;
        while (q->next != nullptr) {
            if (p->from == q->next->to && p->to == q->next->from) {
                dup = q->next;
                q->next = q->next->next;
                delete dup;
            }
            else
                q = q->next;
        }
        p = p->next;
    }
}

edge* kruskal(edge* List, int size) {
    edge* tabToReturn = nullptr;
    BubbleSort(List);
    int forest = 1;

    int* colorTable = new int[size] {0};
    int* forestTable = new int[size] {0};

    // for (int i = 0; i < size; i++) {
    //     colorTable[i] = 0;
    //     forestTable[i] = 0;
    // }
    while (List != nullptr) {
        if (colorTable[List->from] == 0 && colorTable[List->to] == 0) {
            forestTable[List->from] = forest;
            forestTable[List->to] = forest;
            colorTable[List->from] = 1;
            colorTable[List->to] = 1;
            forest++;
            addEdge(tabToReturn, List->from, List->to, List->dist);
        }
        else if (colorTable[List->from] == 0 && colorTable[List->to] == 1) {
            colorTable[List->from] = 1;
            forestTable[List->from] = forestTable[List->to];
            addEdge(tabToReturn, List->from, List->to, List->dist);
        }
        else if (colorTable[List->from] == 1 && colorTable[List->to] == 0) {
            colorTable[List->to] = 1;
            forestTable[List->to] = forestTable[List->from];
            addEdge(tabToReturn, List->from, List->to, List->dist);
        }
        else if (colorTable[List->from] == 1 && colorTable[List->to] == 1 && forestTable[List->from] != forestTable[List->to]) {
            int forest1 = forestTable[List->from];
            int forest2 = forestTable[List->to];
            for (int i = 0; i < size; i++) {
                if (forestTable[i] == forest1 || forestTable[i] == forest2) {
                    forestTable[i] = forest;
                }
            }
            forest++;
            addEdge(tabToReturn, List->from, List->to, List->dist);
        }
        Del(List);
    }
    return tabToReturn;
}

edge* matrixToEdgeList(int** matrix, int size, edge* head) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != 0) {
                addEdge(head, i, j, matrix[i][j]);
                count++;
            }
        }
    }
    return head;
}