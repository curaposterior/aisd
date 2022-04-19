#include <iostream>

using std::cout;
using std::endl;

struct node {
    int val;
    node* next;
};

void add(node* &head, int new_val);
void addToEndGuard(node* &head, int new_val);
void print(node* head);
void bubbleSortEffective(node* &head);

//fix swap function (or just delete it)
void swap(node* p, node* e);
int len(node* head);
void add_simplifier(node* &phead, int val);
void delete_simplifier(node* &phead);

//comb sort functions:
void combSort(node* &head);
void combSwap(node* &head, int gap);



int main() {
    node* head = nullptr;
    srand(time(0));
    for (int i = 0; i < 10; i++) addToEndGuard(head, rand() % 100 + 1);
    print(head);

    combSort(head);

	print(head);
    return 0;
}

void combSort(node* &head) {
    if (head == nullptr)
        return;
    else if (head && head->next == nullptr)
        return;
    else {
        int k = len(head) / 1.3;
		cout << "poczatkowe k=" << k << endl;
		while (k >= 1) {
			cout << k << "'e wykonanie petli" << endl;
			// combSwap(head, k);
			k = k / 1.3;
		}
		bubbleSortEffective(head);
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

//doesn't work like i want it to
void swap(node* p, node* e) {
	node* b = e->next->next;
	node* a = p->next;
	p->next = e->next;
	e->next = a;
	p->next->next = a->next;
	a->next = b;
}

int len(node* head) {
    int n = 0;
    node* p = head;
    while (p != nullptr) {
        n++;
        p = p->next;
    }
    return n;
}

void combSwap(node* &head, int gap) {
	add_simplifier(head, 0);
	node* left = head;
	node* right = head;

	while (true) {
		if (gap == 1)
			break;
		else if (gap > 1) {

			for (int i = 0; i < gap; i++) {
				if (right->next == nullptr)
					break;
				right = right->next;
			}
			// jestem na pozycji jeden przed zmiana
			if (left->val > right->next->val)
				swap(left, right->next); //doesn't work (messes up pointers)

			left = left->next;
			right = right->next;
		}
	}
	delete_simplifier(head);
}

void add_simplifier(node* &phead, int val) {
	node* obj = new node;
	obj->val = val;

	if(phead == NULL) {
		obj->next = NULL;
		phead = obj;
	}
	else {
   		obj->next = phead;
    	phead = obj;
	}
}

void delete_simplifier(node* &phead) {
	if((phead != NULL)&&(phead->next != NULL)) {
    	node* obj = phead;
    	phead = phead->next;
    	delete(obj);
	}
	else {
		cout<< "nie ma co usuwać"<<endl;
	}
}