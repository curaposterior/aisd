/*
Lista jednokierunkowa
(czesc kodu zostala przygotowana przez prowadzacego zajecia)

TODO:
- guard
- dodawanie dwoch list
- zadania na kolosa
*/

#include <iostream>
using namespace std;


struct node
{
	int val;
	node* next;
};


void add(node* &head, int new_val);

void addBehind(node* &structure, int new_val);

void del_structure(node* &head);

void addToEnd(node* &head, int new_val);

void addToEndGuard(node* &head, int new_val);

void print(node* head);

void replace(node* &x, node* &y);

void copy_elems1(node* head);

void addBehindNum(node* &head, int x, int y);

void copy_elems2(node* head);

void swap(node* &head);

void sub_x(node* &head, int x);

void insertAccordingly(node *&H, int val);

void kinda_sort(node* &head);

void swapFirstLast(node* &head);

void addElemsAndSwap(node* &head);

void addSwapElems_code(node* &head);

void split(node* &head, node* &head1, node* &head2);

void addTwoLists(node* &head, node* &head1, node* &head2);

int main() {
	node* head = NULL;
	cout << head << endl;

	add(head, 1);
	/*
	addToEnd(head, 2);
	addToEnd(head, 3);
	addToEnd(head, 4);
	addToEnd(head, 5);
	*/
	for (int i = 2; i < 7; i++)
		addToEnd(head, i);
	print(head);

	//swapFirstLast(head);

	//print(head);

	//kinda_sort(head);
	//print(head);
	print(head);
	node* head1 = nullptr;
	node* head2 = nullptr;
	split(head, head1, head2);
	print(head1);
	print(head2);
	//split(head, head1, head2);
	//print(head1);
	//print(head2);

	// print(head);
	// kinda_sort(head);
	// print(head);
	// copy_elems2(head);
	// print(head);

	// zamienMiejscami(head->next);
	// print(head);

	// sub_x(head, 1);
	// print(head);
	system("PAUSE");
	return 0;
}


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

void swap(node* &head) {
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
			swap(head);
		}
		else {
			node* p = head;
			while (p->next != NULL && p->next->val != x) {
				p = p->next;
			}
			if (p->next && p->next->next)
				swap(p->next);
		}
	}
}

void insertAccordingly(node *&H, int val) { //dzieki kuba
	node *t = new node;
	t->next = H;
	H = t;

	node *p = H;
	while (p->next && p->next->val < val)
		p = p->next;

	node *e = new node;
	e->next = p->next;
	e->val = val;
	p->next = e;

	node *d = t;
	H = d->next;
	delete d;
}

void kinda_sort(node* &head) {
	node* p = head;
	node* pom = new node;
	pom->val = p->val;
	pom->next = nullptr;
	p = p->next;

	while (p != nullptr) {
		insertAccordingly(pom, p->val);
		p = p->next;
	}
	head = pom;
}

void swapFirstLast(node* &head) {
	if (head != NULL && head->next != NULL) {
		node* p = head;
		while (p->next->next != nullptr)
			p = p->next;

		node* pom_head = new node;
		pom_head->val = head->val;
		pom_head->next = p->next;
		p->next = pom_head;

		p = p->next;
		p->next->next = head->next;
		head = p->next;
		p->next = nullptr;
	}

}

//naprawic to
void addElemsAndSwap(node* &head) {
	node* p = head;

	for (int i = 5; i > 0; i--) {
		add(head, i);
	}
	while (p && p->next) {
		swap(p, p->next);
	}
	print(head);
}

void addSwapElems_code(node* &head) {
	if (head && head->next) {
		swap(head);
	}
	else return;
	node* tmp = head->next;
	while (tmp->next && tmp->next->next) {
		swap(tmp->next);
		tmp = tmp->next->next;
	}
}

void split(node* &head, node* &head1, node* &head2) {
	if (head == NULL)
		return;
	else if (head != NULL && head->next == NULL) {
		head1 = head;
		head = NULL;
	}
	else {
		int n = 0;
		node* p = head;
		while (p != NULL) {
			n++;
			p = p->next;
		}

		cout << n << endl;

		node* pom = head;
		int iter = 1;
		while (iter < n / 2) {
			pom = pom->next;
			iter++;
		}

		head2 = pom->next;
		pom->next = NULL;
		head1 = head;
		head = NULL;
	}
}

void addTwoLists(node* &head, node* &head1, node* &head2) {

}