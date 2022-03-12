#include <iostream>

using namespace std;

/*
TODO:
- wstawianie pomiedzy elementy w kolejce
- ustawienie tail na tyl (zmodyfikowanie funkcji enqueue)
*/

struct node
{
	int val;
	node* next;
};

void enqueue(node* &head, int new_val);	//dodaje element na poczatek kolejki

int dequeue(node* &head);	//FIFO (usuwa pierwszy dodany element)

bool isEmpty(node* head);	//zwraca 1 jesli jest pusta lub 0 jest nie jest

node* front(node* &head);	//zwraca adres pierwszego elementu

void print(node* head);		//wyswietla elementy kolejki
							//(bez uwzglednienia zasad dzialania kolejki)

int main(void) {
	node* head = nullptr;
	node* tail = nullptr;
	
	enqueue(head, 10);
    enqueue(head, 20);
	enqueue(head, 30);
	print(head);
	front(head);
	dequeue(head);
	print(head);
	enqueue(head, 10);
	print(head);

    return 0;
}

node* front(node *&head)
{
    if (front != NULL)
    {
        cout << "przod: " << head->val << endl;
        return head->next;
    }
}

void enqueue(node* &head, int new_val) {
	node* t = new node;
	t->next = head;
	head = t;

	node* p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	node* e = new node;
	e->val = new_val;
	e->next = NULL;
	p->next = e;
	dequeue(head);
}

bool isEmpty(node* head) {
	if (head == nullptr)
		return true;
	else
		return false; 
}

int dequeue(node* &head) {
	int val;
	if (head != NULL) {
		node* p = head;
		head = p->next;
		val = p->val;
		delete p;
		return val;
	}
	return -1;
}

void print(node* head) {
	cout << "H->";
	node* p = head;
	while (p != NULL) {
		cout << p->val << "->";
		p = p->next;
	}
	cout << "NULL" << endl;
}
