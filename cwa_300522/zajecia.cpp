#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
node** LS = new node* [size]
for (int i = 0, i < size, i++)
    LS[i] = nullptr;

ADD(H, S) -> ADD(LS[0], 5) - zaimplementowac funkcje dodajaca na tablice list

*/

struct node {
    int too;
    int dystans;
    node* next;
};


//int wczytajMacierz(fstream &plik, macierz &matrix, int size);
//void wypiszMacierz(macierz & m); //ze struktura
void printMacierz(int** wsk, int rozmiar);
void wypelnijMacierz(int** wsk, int n);

void wczytaj(fstream &plik, string nazwa, int** macierz);
void stworzListeSasiedztwa(int** macierz, int size, node* &head);

int main(void) {
    //macierz matrix;
    fstream plik;
    const int size = 5;
    //wczytajMacierz(plik, matrix, size);
    //wypiszMacierz(matrix);

    int** a = new int*[size]; //row
    for (int i = 0; i < size; ++i)
        a[i] = new int[size]; //col

    wczytaj(plik, "cos.txt", a);
    printMacierz(a, 5);



    system("PAUSE");
    return 0;
}

int wczytajMacierz(fstream &plik, int** tab, int size) {
    plik.open("cos.txt");
    if (!plik.good())
    {
        cout << "Odmowa dostepu!" << endl;
        return 0;
    }
    int i = 0, j = 0, n = 0;
    while (plik >> tab[i][j]) {
        if (++j >= size) {
            j = 0;
            i++;
        }
        n++;
        if (n >= size*size) break; // zabezpieczenie przed wczytaniem nadmiaru informacji

    }
    plik.close();
    return n; // zwracamy ilosc wczytanych liczb
}
/*
void wypiszMacierz(macierz & m) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << m.tab[i][j] << " ";

        cout << endl;
    }
}
*/

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
        /*
        node* e = new node;
        e->val = new_val;
        e->next = NULL;
        p->next = e;
        */
        add(p->next, too, dystans);
        head = head->next;
        delete guard;
    }
    else {
        node* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        /*
        node* e = new node;
        e->val = new_val;
        e->next = NULL;
        p->next = e;
        */
        add(p->next, too, dystans);
    }
}

void print(node* head) {
    cout << "H->";
    node* p = head;
    while (p != NULL) {
        cout << p->too << " " << p->dystans << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void printTab(node* head, int size) {
    for (int i = 0; i < size; i++) {
        print(head);
    }
    cout << endl;
}

void wczytaj(fstream &plik, string nazwa, int** macierz) {
    int size;
    plik.open(nazwa);
    if (!plik.good()) {
        cout << "Odmowa dostepu" << endl;
        return;
    }
    plik >> size;
    int elem;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (plik >> elem) {
                macierz[i][j] = elem;
            }
        }
    }
}

void stworzListeSasiedztwa(int** macierz, int size, node* &head) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (macierz[i][j] != 0) {
                // addToEnd();
            }
        }
    }
}