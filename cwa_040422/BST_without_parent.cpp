#include <iostream>
using namespace std;

struct tree {
    int val;
    tree* R;
    tree* L;
};

void insert(tree* &, int);
void printBT(const string &prefix, const tree *node, bool isLeft);
void printBT(const tree *node);
tree* search(tree*, int);
void rotateRight(tree* &root); //dzieki kuba
void rotateLeft(tree* &root);
void inorder(tree* root);

int main(void) {
    tree* root = nullptr;
    insert(root,20);
    insert(root,19);
    insert(root,10);
    insert(root,9);
    printBT(root);
    // rotateRight(root);
    // rotateLeft(root);
    // cout << endl;
    // printBT(root);
    return 0;
}

void rotateRight(tree* & root) {
    tree* A = root;
    tree* B = nullptr;
    tree* BR = nullptr;

    if (root->L) {
        B = root->L;
        if(root->L->R)
            BR = root->L->R;
        B->R = A;
        A->L = BR;
        root = B;
    }
}

void rotateLeft(tree* &root) {
    tree* A = root;
    tree* B = nullptr;
    tree* BL = nullptr;

    if (root->R) {
        B = root->R;
        if (root->R->L)
            BL = root->R->L;
        B->L = A;
        A->R = BL;
        root = B;
    }
}

void insert(tree* &root, int x) {
    if (root == nullptr) {
        tree* p = new tree;
        p->val = x;
        p->L = p->R = nullptr;
        root = p;
    }
    else {
        if (root->val < x)
            insert(root->R, x);
        else
            insert(root->L, x); 
    }
}

void printBT(const string &prefix, const tree *node, bool isLeft)
{
    if (node != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        cout << node->val << endl;
        printBT(prefix + (isLeft ? "|   " : "    "), node->R, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->L, false);
    }
}

void printBT(const tree *node)
{
    printBT("", node, false);
}

tree* search(tree* root, int x) {
	while (root && root->val != x) {
		if (root->val > x) root = root->L;
		else root = root->R;
	}
	return root;
}

void inorder(tree* root) {
	if (root != nullptr) {
		if (root->L != NULL)
			inorder(root->L);
		cout << root->val << endl;
		if (root->R != NULL)
			inorder(root->R);
	}
}