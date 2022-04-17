#include <iostream>
using namespace std;

struct node {
	int val;
	node* next;
};

//comb sort
/*
Swapujemy kolejne elementy 

k = 1.3
*/

void combSort(node* &head);
void swapNotClose(node* p, node* e);
void bubbleSortEffective(node* &head);
void add(node* &head, int new_val);
void addToEndGuard(node* &head, int new_val);
void print(node* head);
void combSwap(node* &head,int k);

int main(void) {
	node* head = nullptr;
	int toAdd[8] = {1,5,7,-19,3,5,6,-10};
	for (int i = 0; i < 8; i++) addToEndGuard(head, toAdd[i]);
	print(head);
	combSwap(head, 2);
	print(head);

	//system("PAUSE");
	return 0;
}

void combSort(node* &head) {
	node* p = head;
	int n = 0;
	while (p != nullptr) {
		n++;
		p = p->next;
	}

	int k = (int)(n / 1.3);
	// do {
	// 	k = n / 1.3;
	// 	combSwap(head, k);
	// } while (k > 1);
	while (k != 1) {
		combSwap(head, k);
		k = (int)(k / 1.3);
	}
	cout << "koniec petli" << endl;
	// bubbleSortEffective(head);
}	

void swapNotClose(node* p, node* e) {
	node* b = e->next->next;
	node* a = p->next;
	p->next = e->next;
	e->next = a;
	p->next->next = a->next;
	a->next = b;
}

void combSwap(node* &head,int k) {
	if (head == nullptr)
		return;
	node* first = head;
	node* tail = head;
	int counter = 0;
	while (tail != nullptr && counter != k) {
		tail = tail->next;
		counter++;
	}
	cout << "wartosc taila: " << tail->val << endl;


	while (tail != nullptr) {
		cout << "wartosc first: " << first->val << ", wartosc tail: " << tail->val << endl;
		if (first->val > tail->val) {
			cout << "wartosc" << endl;
			swapNotClose(first, tail);
		}
		tail = tail->next;
		first = first->next;
	}
}

void bubbleSortEffective(node* &head) {
	if (head == nullptr)
		return;

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
		}
	}
}

void addToEndGuard(node* &head, int new_val) {
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
		add(p->next, new_val);
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
		add(p->next, new_val);
	}
}

void add(node* &head, int new_val) {
	node* p = new node;
	p->val = new_val;
	p->next = head;
	head = p;
}

void print(node* head) {
	node* p = head;
	cout << "H->";
	while (p != nullptr) {
		cout << p->val << "->";
		p = p->next;
	}
	cout << "NULL" << endl;
}