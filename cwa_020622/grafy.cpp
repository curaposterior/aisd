#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
node** LS = new node* [size]
for (int i = 0, i < size, i++)
    LS[i] = nullptr;

Algorytm Prima:
- szukanie drogi z kazdego wierzcholka do kazdego (najkroceJ)!
- potrzebne rzeczy:
    lista sasiedztwa/tablica kolorow/lista wynikowa (lista poszczegolnych krawedzi)

zasada dzialania:
1. okreslenie wierzcholka startowego (s)
2. zmieniamy kolor wierzcholka

Algorytm Kruskala:
potrzebne rzeczy:
    - tablica kolorow
    - tablica lasow
    - lista posorotwanych krawedzi
    - lista wynikowa krawedzi
*/

struct node {
    int too; // index wezla
    int dystans; // wartosc grafu
    node* next;
};

struct lista {
    int index; //poczatek
    int too;  // koniec
    int dystans; //wartosc krawedzi
    lista* next;
};


void printMacierz(int** wsk, int rozmiar);
void wypelnijMacierz(int** wsk, int n);

int** wczytaj(fstream &plik, string nazwa, int** macierz);
node** stworzListeSasiedztwa(int** macierz, int size, node** head);
int** zamienListeNaMacierz(node** head, int size, int** macierz);
lista* wczytajListeKrawedzi(fstream &plik, string nazwa);
node** zamienListeKrawedziNaListeSasiedztwa(lista* head, node** listaSasiedztwa, int size);
int** zamienListeKrawedziNaMacierz(lista* head, int** macierz, int size);
node* Prim(node** LE, int size, int s);

void printTab(node** head, int size);
void add(node* &head, int too, int dystans);
void addToEnd(node* &head, int too, int dystans);
void wyczyscMatrix(int** wsk, int n);
void wypiszListeKrawedzi(lista* head);

int main(void) {
    // fstream plik;
    // const int size = 5;

    // int** a = nullptr;

    // a = wczytaj(plik, "data.txt", a);
    // printMacierz(a, size);

    // node** lista = nullptr;
    // lista = stworzListeSasiedztwa(a, size, lista);
    
    // printTab(lista, 5);
    
    // int** macierz = nullptr;
    // macierz = zamienListeNaMacierz(lista, 5, macierz);
    // printMacierz(macierz, 5);

    // wyczyscMatrix(a, size);

    fstream p;
    lista* head = nullptr;
    head = wczytajListeKrawedzi(p, "lista_krawedzi.txt");
    wypiszListeKrawedzi(head);
    int** macierz = nullptr;
    macierz = zamienListeKrawedziNaMacierz(head, macierz, 5);
    printMacierz(macierz, 5);

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
            wsk[i][j] = 0;
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

void insertAtEnd3Elems(lista* &first, int index, int too, int dystans) {
    lista* temp = new lista;
    
    temp->index = index;
    temp->too = too;
    temp->dystans = dystans;
    temp->next = nullptr;

    if(!first) { // empty list becomes the new node
        first = temp;
        return;
    } else { // find last and link the new node
        lista* last = first;
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
    hf >> size;  // wczytaj rozmiar macierzy (size 2    x size)
    
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
                //insertAtEnd(tab[i], j+1, macierz[i][j]) (alternatywna metoda);
            }
        }
    }
    return tab;
}

int** zamienListeNaMacierz(node** lista, int size, int** macierz) {
    //tworze macierz dynamicznie i wypelniam ja zerami:
    macierz = new int*[size]; //row
    for (int i = 0; i < size; ++i)
        macierz[i] = new int[size];  //col
    
    wypelnijMacierz(macierz, size);

    // przypisanie elementow do odpowiednich miejsc
    for (int i = 0; i < size; i++) {
        node* head = nullptr;
        head = lista[i];
        while (head != nullptr) { //tu przechodzimy po elementach tablicy wsk (po headach)
            macierz[i][(head->too)-1] = head->dystans;
            head = head->next;
        }
    }
    return macierz;
}

lista* wczytajListeKrawedzi(fstream &hf, string nazwa) {
    hf.open(nazwa);
    if (!hf.good()) {
        cout << "Odmowa dostępu..." << endl;
        return nullptr;
    }
    lista* head = nullptr;
    int size = 0, el1 = 0, el2 = 0, el3 = 0;

    hf >> size;
    while (hf) {
        //wczytaj po kolei index/too/dystans
        hf >> el1;
        hf >> el2;
        hf >> el3;
        insertAtEnd3Elems(head, el1, el2, el3);
    }
    return head;
}

void wypiszListeKrawedzi(lista* head) {
    lista* p = head;
    cout << "H-> ";
    while (p != nullptr) {
        cout << p->index << "/" << p->too << "/" << p->dystans << " -> ";
        p = p->next;
    }
    cout << "NULL" <<  endl;
}

int** zamienListeKrawedziNaMacierz(lista* head, int** macierz, int size) {
    if (head == nullptr) {
        cout << "Lista jest pusta" << endl;
        return nullptr;
    }

    macierz = new int*[size]; //row
    for (int i = 0; i < size; ++i)
        macierz[i] = new int[size];  //col
    
    wypelnijMacierz(macierz, size); //wypelnienie macierzy zerami

    lista* p = head;

    while (p != nullptr) {
        cout << (p->index-1) << " " << p->too-1 << " " << p->dystans << endl;
        macierz[p->index-1][p->too-1] = p->dystans;
        p = p->next;
    }

    return macierz;
}

//Algorytm Prima: (s - wierzcholek od ktorego zaczynamy)
node* algorytmPrima(node** listaSasiedztwa, int size, int s) {

    int* tablicaKolorow = new int[size] {0};
    node* tabWynikowa = nullptr;

    //ustawienie poczatkowego stanu tablicy kolorow
    tablicaKolorow[s] = 1;

    for (int i = 0; i < size; i++) {
        node* curr = listaSasiedztwa[i]; //kolejna lista z tablicy wskaznikow

        if (tablicaKolorow[i] == 0) {
            //szukamy minimum dla szarych wierzcholkow
            node* p = curr;
            int min;
            while (p != nullptr) {
                if (tablicaKolorow[p->too] == 1) {
                    p = p->next;
                }

            }
        }

        else {
            while (curr != nullptr) {

            }
        }

    }



    return tabWynikowa; //
}

node* Prim(node** LE, int size, int s) {
    int* ColorTable = new int[size] {0};

    node* LR = nullptr; //lista wynikowa
    ColorTable[s] = 1;
    for (int i = 0; i < size; i++) { //dopoki cala tablica kolorow nie jest 1
        for (int j = 0; i < size; i++) {
            /*
            jeżeli kolor w tablicy ColorTable[j] jest szary przeglądamy LE tego wierzchołka
            i szukamy minimalnej krawędzi K prowadzącej do białego wierzchołk
            
            */
        }
        /*
        Drugi wierzchołek krawędzi K kolorujemy na szary
        Krawędź K dodajemy do listy wynikowych krawędzi LR;
        */
    }
    return LR;
}