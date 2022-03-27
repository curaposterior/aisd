#include <iostream>
#include <random>
//#include <string>
using namespace std;

struct node {
    int val;
    node* next;
};

void print(node* head);
void add(node* &head, int new_val);
void addToEnd(node* &head, int new_val);
void swap(node* &head);
void bubbleSort(node* &head);
void bubbleSortEffective(node* &head);

int main(void) {
    node* head1 = nullptr;
    node* head2 = nullptr;
    cout << head1 << endl;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1,100);
    for (int i = 0; i < 10; i++) {
        addToEnd(head1, dist6(rng));
        addToEnd(head2, dist6(rng));
    }
    
    print(head1);
    print(head2);
    bubbleSort(head1);
    bubbleSortEffective(head2);
    print(head1);
    print(head2);
    return 0;
}

void print(node* head) {
    node* p = head;
    cout << "H->";
    if (p != NULL) {
        while (p != NULL) {
            cout << p->val;
            cout << "->";
            p = p->next; 
        }
    }
    cout << "NULL" << endl;
}

void add(node* &head, int new_val) {
    node* p = new node;
    p->val = new_val;
    p->next = head;
    head = p;
}

void addToEnd(node* &head, int new_val) {
    node* e = new node;
    e->next = head;
    head = e;

    node* p = e;
    while (p->next != nullptr)
        p = p->next;
    add(p->next, new_val);

    head = head->next;
    delete e;
}

void swap(node* &head) {
	//zamiana drugiego z pierwszym
	if (head && head->next) {
		node* p = head;
		head = head->next;
		p->next = head->next; //p->next->next;
		head->next = p;
	}
}

void bubbleSort(node* &head) {
    if (head == nullptr)
        return;

    int wykonania_petli = 0;
    int counter = 0; // ilosc elementow
    node* p = head;
    node* curr = nullptr;
    node* trail = nullptr;
    node* temp = nullptr;

    while (p != NULL) {
        counter++;
        p = p->next;
        // wykonania_petli++;
    }

    for (int i = 0; i < counter; i++) {
        curr = head;
        trail = head;
        
        while (curr->next != NULL) {
            if (curr->val > curr->next->val) {
                temp = curr->next;
                curr->next = curr->next->next;
                temp->next = curr;

                if (curr == head) { // jesli zamieniany byl pierwszy element (na glowie)
                    head = temp;
                    trail = temp;
                }
                else
                    trail->next = temp;
                curr = temp;
            }
            trail = curr;
            curr = curr->next;

            wykonania_petli++;
        }
        wykonania_petli++;
    }
    cout << "Ilosc wykonan petli (wersja zwykla): " << wykonania_petli << endl;
}

void bubbleSortEffective(node* &head) {
        if (head == nullptr)
        return;

    int wykonania_petli = 0;
    int counter = 0; // ilosc elementow
    node* p = head;
    node* curr = nullptr;
    node* trail = nullptr;
    node* temp = nullptr;
    node* lastSwap = nullptr;

    while (p != NULL) {
        counter++;
        p = p->next;
        // wykonania_petli++;
    }

    for (int i = 0; i < counter; i++) {
        curr = head;
        trail = head;
        
        while (curr->next != NULL && curr != lastSwap) {
            if (curr->val > curr->next->val) {
                temp = curr->next;
                curr->next = curr->next->next;
                temp->next = curr;

                if (curr == head) { // jesli zamieniany byl pierwszy element (na glowie)
                    head = temp;
                    trail = temp;
                }
                else
                    trail->next = temp;
                curr = temp;
                lastSwap = temp;
            }
            trail = curr;
            curr = curr->next;

            wykonania_petli++;
        }
        wykonania_petli++;
    }
    cout << "Ilosc wykonan petli (wersja effective): " << wykonania_petli << endl;
}