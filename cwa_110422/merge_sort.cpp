#include <iostream>
using namespace std;

struct node {
	int val;
	node* next;
};

void MS(node* &H);
void split(node* &head, node* &head1, node* &head2);
void add(node* &head, int new_val);
void addToEndGuard(node* &head, int new_val);
void print(node*);
node* addTwoLists(node* H1, node* H2);
void merge(node* &dest, node* &src1, node* &src2);
void addAndShift(node* &tail, node* &src);


int main(void) {
	node* l1 = nullptr;
	node* l2 = nullptr;

	addToEndGuard(l1, 4);
	addToEndGuard(l1, 2);
	addToEndGuard(l1, 1);
	print(l1);
	addToEndGuard(l2, 5);
	addToEndGuard(l2, 14);
	addToEndGuard(l2, 2);
	addToEndGuard(l2, 123);
	addToEndGuard(l2, 56);
	addToEndGuard(l2, 34);
	addToEndGuard(l2, 678);
	addToEndGuard(l2, 64);
	addToEndGuard(l2, 78);
	print(l2);

	node* twoLists = nullptr;
	twoLists = addTwoLists(l1, l2);
	//print(twoLists);

	MS(twoLists);
	print(twoLists);



	system("PAUSE");
	return 0;
}

void MS(node* &H) {
	if (H->next == nullptr) return;
	node* L = nullptr;
	node* R = nullptr;
	split(H, L, R);
	MS(L);
	MS(R);
	merge(H, L, R);
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

		//cout << n << endl;

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

node* addTwoLists(node* H1, node* H2) {
	node* p1 = H1;
	while (p1->next != NULL) {
		p1 = p1->next;
	}
	p1->next = H2;
	return H1;
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

//kod merge_sort

void merge(node* &dest, node* &src1, node* &src2) {
	node* tmp1 = src1;
	node* tmp2 = src2;

	if (tmp1->val <= tmp2->val) {
		dest = tmp1;
		tmp1 = tmp1->next;
	}
	else {
		dest = tmp2;
		tmp2 = tmp2->next;
	}
	node* tail = dest;
	while (tmp1 && tmp2) {
		if (tmp1->val <= tmp2->val) {
			addAndShift(tail, tmp1);
		}
		else
			addAndShift(tail, tmp2);
	}
	if (tmp1) {
		tail->next = tmp1;
	}
	else tail->next = tmp2;

	src1 = nullptr;
	src2 = nullptr;
}

void addAndShift(node* &tail, node* &src) {
	tail->next = src;
	tail = tail->next;
	src = src->next;
}

