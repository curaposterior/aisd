#include <iostream>
using namespace std;

struct tree {
	int val;
	tree* R;
	tree* L;
};

void insert(tree* &root, int x);

void inorder(tree* root);

tree* search(tree* root, int x);

void printTree(tree* curr, int depth);


int main(void) {
	tree* root = NULL;
	insert(root, 3);
	insert(root, 9);
	insert(root, -6);
	insert(root, 4);
	//printTree(root, 3);
	inorder(root);
	tree* szukana = search(root, 5);
	cout << "Znalezniono: " << szukana->val << endl;

	system("PAUSE");
	return 0;
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


void insert(tree* &root, int x) {
	if (root == NULL) {
		tree* p = new tree;
		p->L = p->R = nullptr;
		p->val = x;
		root = p;
	}
	else {
		if (root->val <= x) {
			insert(root->R, x);
		}
		else
			insert(root->L, x);
	}
}


tree* search(tree* root, int x) {
	while (root && root->val != x) {
		if (root->val > x) root = root->L;
		else root = root->R;
	}
	return root;
}
