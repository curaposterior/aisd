#include <iostream>
using namespace std;


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
        p  = p->next;
    }
    cout << "NULL" << endl;
}


int main() {
    node* head = NULL;
    cout << head << endl;

    add(head, 5);
    print(head);
    add(head, 10);
    print(head);
    del_structure(head);
    print(head);
    addToEnd(head, 11);
    print(head);
    system("PAUSE");

    return 0;
}