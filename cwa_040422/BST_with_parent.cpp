#include <iostream>
using namespace std;

struct tree {
    int val;
    tree* R;
    tree* L;
    tree* Up;
};

//dzieki kuba
void insert(tree* &root, int x, tree* up);
void printBT(const string &prefix, const tree *node, bool isLeft);
void printBT(const tree *node);
tree* search(tree* root, int x);
void inorder(tree* root);
void rotateLeft(tree* &root);
void rotateRight(tree* &root);

int main(void) {
    tree* root = nullptr;
    
    insert(root,20, root);
    insert(root,19,root);
    insert(root,10,root);
    insert(root,9,root);
    printBT(root);

    return 0;    
}

void insert(tree* &root, int x, tree* up) {
    if (root == nullptr) {
        tree* p = new tree;
        p->L = p->R = nullptr;
        p->val = x;
        p->Up = up;
        root = p;
    }
    else {
        if (root->val <= x)
            insert(root->R, x, root);
        else
            insert(root->L, x, root);
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

void rotateRight(tree* &root) {
    tree* A = root;
    tree* B = nullptr;
    tree* BR = nullptr;
    if (root->L) {
        B = root->L;
        if (root->L->R) {
            BR = root->L->R;
            BR->Up = A;
        }
        BR->R = A;
        A->L = BR;
        A->Up = B;
        root = B;
        B->Up = B;
    }
}

void rotateLeft(tree* &root) {
    tree* A = root;
    tree* B = nullptr;
    tree* BL = nullptr;
    if (root->R) {
        B = root->R;
        if (root->R->L) {
            BL = root->R->L;
            BL->Up = A;
        }
        B->L = A;
        A->R = BL;
        root = B;
    }
}