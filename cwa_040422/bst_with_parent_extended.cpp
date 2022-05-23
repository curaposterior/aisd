#include <iostream>
using namespace std;

struct tree {
    int data;
    tree *left, *right, *parent;
};

//printing functions
void printBT(const string &prefix, const tree *tree, bool isLeft);
void printBT(const tree *tree); 
tree* newNode(int x);
tree* insert(tree* root, int x);
void deleteLeaf();
void deleteNode();
tree* predecessor(tree* root);
tree* successor(tree* root);
void rotateRight(tree* &root);
void rotateLeft(tree* &left);
tree* minValueAddress(tree* root);
tree* maxValueAddress(tree* root);
void inorder(const tree* root);
void postorder(const tree* root);
void preorder(const tree* root);

int main(void) {
    tree* root = nullptr;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 9);
    root = insert(root, 6);

    printBT(root);

    return 0;
}

tree* newNode(int x) {
    tree* p = new tree;
    p->data = x;
    p->left = p->right = nullptr;
    p->parent = nullptr;
    return p;
}

tree* insert(tree* root, int x) {
    if (root == nullptr)
        return newNode(x);
    
    if (x < root->data) {
        tree* lchild = insert(root->left, x);
        root->left = lchild;
        lchild->parent = root;
    }
    else {
        tree* rchild = insert(root->right, x);
        root->right = rchild;
        rchild->parent = root;
    }
    return root;
}

void RotateLeftUp(tree *&root) {
    tree *A = root;
    tree *B = nullptr;
    tree *BL = nullptr;
    if (root->right)
    {
        B = root->right;
        if (root->right->left)
        {
            BL = root->right->left;
            BL->parent = A;
        }
        B->left = A;
        A->right = BL;
        root = B;
        B->parent = nullptr;
    }
}

void RotateRightUp(tree *&root) {
    tree *A = root;
    tree *B = nullptr;
    tree *BR = nullptr;
    if (root->left)
    {
        B = root->left;
        if (root->left->right)
        {
            BR = root->left->right;
            BR->parent = A;
        }
        B->right = A;
        A->left = BR;
        A->parent = B;
        root = B;
        B->parent = nullptr;
    }
}

tree* predecessor(tree* root) {
    if (root->left) return maxValueAddress(root->left);

    tree* p = nullptr;

    do {
        p = root;
        root = root->right;
    } while(root && (root->right != p));
    return root;
}

tree* successor(tree* root) {
    if (root->right) return minValueAddress(root->right);

    tree* p = nullptr;

    do {
        p = root;
        root = root->right;
    } while(root && (root->left != p));
    return root;
}

tree* minValueAddress(tree* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

tree* maxValueAddress(tree* root) {
    while (root && root->right)
        root = root->right;
    return root;
}

void inorder(const tree* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(const tree* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void preorder(const tree* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

////////////////////////////////////////////////////////////////////
void printBT(const string &prefix, const tree *tree, bool isLeft) {
    if (tree != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        cout << tree->data << endl;
        printBT(prefix + (isLeft ? "|   " : "    "), tree->right, true);
        printBT(prefix + (isLeft ? "|   " : "    "), tree->left, false);
    }
}


void printBT(const tree *tree) {
    printBT("", tree, false);
}
////////////////////////////////////////////////////////////////////

