#include <iostream>
#include <random>
using namespace std;

struct node {
    int val;
    node* next;
};

void sort(node*&);
void addToEnd(node* &head, int);
void print(node*);
void add(node* &head, int new_val);

int main(void) {
    node* head = nullptr;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1,100);
    for (int i = 0; i < 10; i++) {
        addToEnd(head, dist6(rng));
    }
    print(head);
    sort(head);
    print(head);

    return 0;
}


void sort (node* &head)
{
  int count = 0, i;
  node *start = head;
  node *curr = NULL;
  node *trail = NULL;
  node *temp = NULL;

  while(start != NULL) { //grab count
    count++;
    start = start->next;
  }

  for(i = 0; i<count; ++i) { //for every element in the list

    curr = trail = head; //set curr and trail at the start node

    while (curr->next != NULL) { //for the rest of the elements in the list
      if (curr->val > curr->next->val) { //compare curr and curr->next

        temp = curr->next; //swap pointers for curr and curr->next
        curr->next = curr->next->next;
        temp->next = curr;

        //now we need to setup pointers for trail and possibly head
        if(curr == head) //this is the case of the first element swapping to preserve the head pointer
          head = trail = temp;
        else //setup trail correctly
          trail->next = temp;
        curr = temp; //update curr to be temp since the positions changed
      }
      //advance pointers
      trail = curr;
      curr = curr->next;
    }
  }
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