#include <iostream>
using namespace std;

struct node {
    int val;
    node* next;
};

void print(node* head); //wypisywanie liczby

void add(node* &head, int new_val); // dodawanie struktury na poczatek

void addToEnd(node* &head, int new_val); //dodawanie struktury na koniec listy

void deletion(node* &head, int); //usuwanie wskazanego elementu (klucz = wartosc)

void deleteFirst(node* &head); //usuwanie elementu

node* reverse(node* &head); //odwracanie listy

void delete_evens(node *&head); //usuwanie parzystych wartosci

void deleteEvenSum(node* &head); //usuniece gdy suma dwoch nast. elem. jest parzysta

void addReverselistRight(node* &head); //np. 1->2->3 na  1->2->3->3->2->1

void addReverselistLeft(node* &head); //np. 1->2->3 na 3->2->1->1->2->3

node* copy(node* &head); //kopiowanie listy

void split(node* &head, node* &head1, node* &head2); //dzielenie listy na head1 i head2

void swap(node* &head); //zamiana pierwszego elementu z drugim

void addSwapElems(node* &head); //zamiana elementow miedzy soba (np. H->1->2->2->4->4->NULL na H->2->1->4->2->4->NULL)

void swapFirstLast(node* &head); //zamiana ostatniego elementu z pierwszym

//pseudo sortowanie
void insertAccordingly(node *&H, int val);
void kinda_sort(node* &head);


int main(void) {
    node* head = nullptr;
    cout << head << endl;

    addToEnd(head, 1);
    addToEnd(head, 2);
    addToEnd(head, 2);
    addToEnd(head, 4);
    addToEnd(head, 4);

    print(head);
    swap(head);
    // addSwapElems(head);
    print(head);
    kinda_sort(head);
    print(head);

    return 0;
}

void add(node* &head, int new_val) {
    node* p = new node;
    p->val = new_val;
    p->next = head;
    head = p;
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

void deleteFirst(node* &head) {
    if (head != NULL) {
        node* p = head;
        head = head->next;
        delete p;
    }
} 

node* reverse(node* &head) {
    node* prevp = nullptr;
    node* currp =  head;
    node* nextp;

    while (currp != nullptr) {
        nextp = currp->next;
        currp->next = prevp;

        prevp = currp; 
        currp = nextp;
    }
    return prevp;
}

void delete_evens(struct node *&head) { 
    node *temp;
    node *step;
    node *prev;

    if (head == NULL)
        return; // nie ma co usuwac

    //kiedy pierwszy element glowy jest parzysty
    while (head != NULL && head->val % 2 == 0) {
        temp = head; 
        head = head->next; 
        delete temp;  
    }

    step=head;
   
    while (step != NULL) {
        if (step->val %2==0) { 
            temp = step ; 
            step = step -> next ; 
            prev->next=step;
            delete temp ; 
        }       
        else {
            prev=step;
            step = step -> next ; 
            }
    }
    step=NULL;
}

void deleteEvenSum(node* &head) {
    add(head, 0); //dodanie guarda
    if (head->next && head->next->next) {
        node* p = head;
        while (p->next && p->next->next) {
            if ((p->next->val + p->next->next->val) % 2 == 0) {
                deleteFirst(p->next);
                deleteFirst(p->next);
            }
            else
                p = p->next;
        }
        deleteFirst(head); //usuniecie guarda
    }
}

void addReverselistRight(node* &head) {
    if (head == NULL)
        return;

    node* p = head;
    node* c_head = copy(head);
    node* r_head = reverse(c_head);


    while (p->next != NULL) {
        p = p->next;
    }
    p->next = r_head;
}

void addReverselistLeft(node* &head) {
    if (head == NULL)
        return;

    node* c_head = copy(head);
    node* r_head = reverse(c_head);

    node* p = r_head;
    while (p->next != NULL)
        p = p->next;
    p->next = head;
    head = r_head;
}

node* copy(node* &head) {
    node* p = head;
    if (head == NULL) {
        node* copied_head = NULL;
        return copied_head;
    }

    node* copied_head = NULL;
    node* previous = new node;
    previous->val = p->val;
    previous->next = NULL;
    copied_head = previous;
    p = p->next;

    while (p != NULL) {
        node* cp = new node;
        cp->val = p->val;
        cp->next = NULL;
        previous->next = cp;

        p = p->next;
        previous = previous->next;
    }
    return copied_head;
}

void split(node* &head, node* &head1, node* &head2) {
    if (head == NULL) {
        return;
    }
    else if (head != NULL && head->next == NULL) {
        head1 = head;
        head = nullptr;
    }
    else {
        int n;
        node* p = head;
        while (p != NULL) {
            n++;
            p = p->next;
        }

        node* pom = head;
        int iter = 1;
        while (iter < n/2) {
            pom = pom->next;
            iter++;
        }

        head2 = pom->next;
        pom->next = NULL;
        head1 = head;
        head = nullptr;
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

void addSwapElems(node* &head) {
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

//pseudo sortowanie
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
// end