#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
node** LS = new node* [size]
for (int i = 0, i < size, i++)
    LS[i] = nullptr;

ADD(H, S) -> ADD(LS[0], 5) - zaimplementowac funkcje dodajaca na tablice list


stowrzyc tablice z zerami
i jezeli element istnieje to dopisuje naura (pamietac zeby odjac 1)
*/

struct node {
    int too; // index wezla
    int dystans; // wartosc grafu
    node* next;
};

struct connect {
    int index;
    int too;
    int dystanst;
    connect* next;
};

//int wczytajMacierz(fstream &plik, macierz &matrix, int size);
//void wypiszMacierz(macierz & m); //ze struktura
void printMacierz(int** wsk, int rozmiar);
void wypelnijMacierz(int** wsk, int n);
node* wczytajListeKrawedzi(fstream &plik, string nazwa);

int** wczytaj(fstream &plik, string nazwa, int** macierz);
node** stworzListeSasiedztwa(int** macierz, int size, node** head);
void printTab(node** head, int size);
void add(node* &head, int too, int dystans);
void addToEnd(node* &head, int too, int dystans);
void wyczyscMatrix(int** wsk, int n);

int main(void) {
    fstream plik;
    const int size = 5;

    int** a = nullptr;

    a = wczytaj(plik, "data.txt", a);
    printMacierz(a, size);

    node** lista = nullptr;
    lista = stworzListeSasiedztwa(a, size, lista);
    // cout << lista[0]->next->dystans << endl;
    printTab(lista, 5);
    

    wyczyscMatrix(a, size);
    return 0;
}

void printMacierz(int** wsk, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << wsk[i][j] << " ";
        }
        cout << endl;
    }
}

void wypelnijMacierz(int** wsk, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            wsk[i][j] = i;
        }
    }
}

void wyczyscMatrix(int** wsk, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] wsk[i];
    }
    delete[] wsk;
}

void add(node* &head, int too, int dystans) {
    node* p = new node;
    p->too = too;
    p->dystans = dystans;
    p->next = head;
    head = p;
}

void addToEnd(node* &head, int too, int dystans) {
    if (head == NULL) {
        node* guard = new node;
        guard->next = head;
        head = guard;

        node* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        add(p->next, too, dystans);
        head = head->next;
        delete guard;
    }
    else {
        node* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        add(p->next, too, dystans);
    }
}

//https://stackoverflow.com/questions/20125477/linked-list-insert-at-the-end-c
void insertAtEnd(node* &first, int too, int dystans) {
    // create node
    node* temp = new node;
    temp->too = too;
    temp->dystans = dystans;
    temp->next = nullptr;

    if(!first) { // empty list becomes the new node
        first = temp;
        return;
    } else { // find last and link the new node
        node* last = first;
        while(last->next) last=last->next;
        last->next = temp;
    }
}

void print(node* head) {
    cout << "H->";
    node* p = head;
    while (p != NULL) {
        cout << p->too << "/" << p->dystans << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void printTab(node** head, int size) {
    for (int i = 0; i < size; i++) {
        print(head[i]);
    }
    cout << endl;
}

//https://cpp0x.pl/forum/temat/?id=14308
int** wczytaj(fstream &hf, string nazwa, int** a) {
    hf.open(nazwa);
    if( !hf.good() ) {
        cout << "Odmowa dostepu!" << endl;
        return nullptr;
    }
    int size;
    hf >> size;  // wczytaj rozmiar macierzy (size x size)
    
    a = new int*[size]; //row
    for (int i = 0; i < size; ++i)
        a[i] = new int[size]; //col


    int i = 0, j = 0, n = 0; // liczniki do petli, n - liczba elementow
    while( hf >> a[ i ][ j ] ) {
        if( ++j >= size ) {
            j = 0;
            i++;
        }
        n++;
        if( n >= size*size ) break; // zabezpieczenie przed wczytaniem nadmiaru informacji
       
    }
    hf.close();
    return a;
}

node** stworzListeSasiedztwa(int** macierz, int size, node** tab) {
    tab = new node*[size] {nullptr}; //https://stackoverflow.com/questions/2265664/how-to-dynamically-allocate-an-array-of-pointers-in-c
    for (int i = 0; i < size; i++) {
        node* head = nullptr;
        tab[i] = head;
        for (int j = 0; j < size; j++) {
            if (macierz[i][j] != 0) {
                addToEnd(tab[i], j+1, macierz[i][j]);
                //insertAtEnd(tab[i], j+1, macierz[i][j]);
            }
        }
    }
    return tab;
}

node* wczytajListeKrawedzi(fstream &hf, string nazwa) {
    hf.open(nazwa);
    if (!hf.good()) {
        cout << "Odmowa dostępu..." << endl;
        return nullptr;
    }
    node* head = nullptr;
    //while (hf >> )
}