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
void deletion(node* &head, int); 
void del_first(node* &head);
void swap(node* &head);
void swapElems(node* &head);
void bubbleSort(node* &head);

int main(void) {
    node* head = nullptr;
    cout << head << endl;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1,100);
    for (int i = 0; i < 10; i++) {
        addToEnd(head, dist6(rng));
    }

    print(head);
    bubbleSort(head);
    print(head);
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

void deletion(node* &head, int dval) {
    if (head->next == nullptr) {
        node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    else {
        node* p = head;
        while (p && p->next->val != dval) {
            p = p->next;
        }
        node* toDelete = p->next;
        p->next = toDelete->next;
        delete toDelete;
    }
}

void del_first(node* &head) {
    if (head != NULL) {
        node* p = head;
        head = head->next;
        delete p;
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

void swapElems(node* &head) {
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


//not working
void bubbleSort(node* &head) {
    node* p = head;
    while (p->next && p->next->next) {
        if (p->next->val > p->next->next->val) {
            swapElems(p->next);
        }
        p = p->next;
    }
}