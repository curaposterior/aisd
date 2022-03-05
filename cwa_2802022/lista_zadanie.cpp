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
        p  = p->next;
    }
    cout << "NULL" << endl;
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

void copy_elems2(node* head) {
    //H->1->3->8->NULL
    //H->1->3->3->3->8->8->8->8->8->8->8->8->NULL
    node* p = head;
    while (p != NULL) {
        for (int i = 0; i < p->val-1; i++) {
            addBehind(p, p->val);
            p = p->next;
        }
        p = p->next;
    }
}

int main() {
    node* head = NULL;
    cout << head << endl;
    add(head, 1);
    addToEnd(head, 3);
    addToEnd(head, 8);
    print(head);
    copy_elems1(head);
    print(head);
    return 0;
}