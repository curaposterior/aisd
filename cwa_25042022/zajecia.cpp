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

int main(void) {
    

    return 0;
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