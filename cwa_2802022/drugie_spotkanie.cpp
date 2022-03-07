#include <iostream>
using namespace std;

/*
Lista jednokierunkowa
(czesc kodu zostala przygotowana przez prowadzacego zajecia)
*/

struct node
{
	int val;
	node* next;
};


void add(node* &head, int new_val) {
	node* p = new node;
	p->val = new_val;
	p->next = head;
	head = p;
}


void addBehind(node* &structure, int new_val) {
	node* p = new node;
	p->next = structure->next;
	p->val = new_val;
	structure->next = p;
}


void del_structure(node* &head) {
	if (head != NULL) {
		node* p = head;
		head = head->next;
		delete p;
	}
}


void addToEnd(node* &head, int new_val) {
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


void print(node* head) {
	cout << "H->";
	node* p = head;
	while (p != NULL) {
		cout << p->val << "->";
		p = p->next;
	}
	cout << "NULL" << endl;
}

void replace(node* &x, node* &y) {
	node* pom = new node;
	pom->val = x->val;
	pom->next = y->next;
	y->next = pom;
	node* pom2 = x;
	x = pom2->next;
	delete pom2;
}


void copy_elems1(node* head) {
	//H->1->3->8->NULL
	//H->1->1->3->3->8->8->NULL
	node* p = head;
	while (p != NULL) {
		node* pp = new node;
		pp->val = p->val;
		pp->next = p->next;
		p->next = pp;
		p = pp->next;
	}
}


void addBehindNum(node* &head, int x, int y) {
	if (head != NULL) {
		node* p = head;
		while (p->next != NULL && p->next->val != y) {
			p = p->next;
		}
		if (p->next != NULL) {
			node* e = new node;
			e->val = x;
			e->next = p->next;
			p->next = e;
		}
	}
}


void copy_elems2(node* head) {
	//H->1->3->8->NULL
	//H->1->3->3->3->8->8->8->8->8->8->8->8->NULL
	node* p = head;
	while (p != NULL) {
		for (int i = 0; i < p->val - 1; i++) {
			addBehind(p, p->val);
			p = p->next;
		}
		p = p->next;
	}
}


void zamienMiejscami(node* &head) {
	//zamiana drugiego z pierwszym
	if (head && head->next) {
		node* p = head;
		head = head->next;
		p->next = head->next; //p->next->next;
		head->next = p;
	}
}

void sub_x(node* &head, int x) { //zamiana elementu x ze swoim nastepnikiem
	if (head != NULL && head->next != NULL) {
		if (head->val == x && head->next) { //sprawdzenie jezeli szukana liczba jest na pierwszym miejscu
			zamienMiejscami(head);
		}
		else {
			node* p = head;
			while (p->next != NULL && p->next->val != x) {
				p = p->next;
			}
			if (p->next && p->next->next)
				zamienMiejscami(p->next);
		}
	}
}

int main() {
	node* head = NULL;
	cout << head << endl;
	add(head, 1);
	addToEnd(head, 2);
	addToEnd(head, 3);
	print(head);
	
	copy_elems2(head);
	print(head);
	
	zamienMiejscami(head->next);
	print(head);
	
	sub_x(head, 1);
	print(head);
	system("PAUSE");
	return 0;
}
