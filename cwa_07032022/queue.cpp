#include <iostream>

using namespace std;

struct node
{
	int val;
	node* next;
};

void enqueue(node* &head);
void dequeue(node* &head);
bool isEmpty(node* head);
node* front(node* &head);

int main(void) {
	node* head = nullptr;
	node* tail = nullptr;
	
    

    return 0;
}

node *front(node *&head)
{
    if (front != NULL)
    {
        cout << "przod: " << head->next << endl;
        return head->next;
    }
}

bool isEmpty(node* head) {
	if (head == nullptr)
		return true;
	else
		return false; 
}

void enqueue() {

}