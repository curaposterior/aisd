#include <iostream>
using namespace std;

struct node {
    int val;
    node* next;
};


void push(node* &top, int val);
void pop(node* &top);
bool empty(node* top);
int size(node* top);
void print_debug(node* top);

int main(void) {
    node* top = nullptr;



    cout << empty(top) << endl;
    return 0;
}


void push(node* &top, int val) {
    node* p = new node;
    p->val = val;
    p->next = top;
    top = p;
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
