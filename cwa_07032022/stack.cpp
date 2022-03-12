#include <iostream>
using namespace std;

struct node {
    int val;
    node* next;
};


void push(node* &top, int val);

int pop(node* &top);

bool empty(node* top);

int size(node* top);

void print_debug(node* top);

int main(void) {

    node* top = nullptr;
    push(top, 1);
    push(top, 2);
    pop(top);
    return 0;
}


void push(node* &top, int val) {
    node* p = new node;
    p->val = val;
    p->next = top;
    top = p;
}


int pop(node* &top) {
    int val;
    if (top != nullptr) {
        node* p = top;
        top = top->next;
        val = p->val;
        delete p;
        return val;
    }
    return -1;
}


bool empty(node* top) {
    if (top == nullptr)
        return true;
    else
        return false;
}


void print_debug(node* head) {
	cout << "top->";
	node* p = head;
	while (p != NULL) {
		cout << p->val << "->";
		p = p->next;
	}
	cout << "NULL" << endl;
}
