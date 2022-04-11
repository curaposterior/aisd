#include <iostream>
using namespace std;

struct node {
	int val;
	node* next;
};

void swapNotClose(node* p, node* e);
void bubbleSortEffective(node* &head);


int main(void) {


	system("PAUSE");
	return 0;
}



void swapNotClose(node* p, node* e) {
	node* b = e->next->next;
	node* a = p->next;
	p->next = e->next;
	e->next = a;
	p->next->next = a->next;
	a->next = b;
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