#include <iostream>

#include <iostream>
using namespace std;

struct tree {
    int data;
    tree* left;
    tree* right;
    tree* parent;
};

//printing functions (found on stackoverflow)
void printBT(const string &prefix, const tree *tree, bool isLeft);
void printBT(const tree *tree);

tree* newNode(int data);
tree* insert(tree* root, int data);
void inorder(tree* root);
tree* search(tree* root, int x);

//zadanie 1
void findAndRemoveSons(tree* root, int x);
void deleteNode(tree* root);

//zadanie 2
int binarySearch(int* T, int x, int lewy, int prawy);


int main() {
    tree* root = nullptr;
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 12);
    root = insert(root, 11);
    
    
    int* T = new int[10] {1,2,3,4,5,6,7,8,9,10};
    cout << binarySearch(T,1,0,9) << endl;
    return 0;
}


tree* newNode(int data) {
    tree* p = new tree;
    p->data = data;
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
    else if (x > root->data) {
        tree* rchild = insert(root->right, x);
        root->right = rchild;
        rchild->parent = root;
    }
    return root;
}


void inorder(tree* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}


tree* search(tree* root, int x) {
    if (root == nullptr) return nullptr;
    else {
        if (root->data == x) return root;
        if (x < root->data) return search(root->left, x);
        else return search(root->right, x);
    }
}


void findAndRemoveSons(tree* root, int x) {
    if (root == nullptr) return;
    
    tree* found = search(root, x);
    
    if (found->left) {
        deleteNode(found->left);
        found->left = nullptr;
    }
    if (found->right) {
        deleteNode(found->right);
        found->right = nullptr;
    }
}


void deleteNode(tree* root) {
    if (root != NULL) {
        if (root->right != NULL) deleteNode(root->right);
        if (root->left != NULL) deleteNode(root->left);
        delete root; 
    }
    else cout << "lista jest juz pusta"<<endl;
}


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

//zadanie 2 - algorytm przeszukiwania binarnego w tablicy
int binarySearch(int* T, int x, int lewy, int prawy) {
    if (lewy < prawy) {
        int srodekIndeks = (lewy + prawy+1)/2;
        if (T[srodekIndeks] == x) return srodekIndeks; 

        if (x > T[srodekIndeks]) {
            //lezy po prawej stronie tablicy (jesli jest posortowana rosnaco)
            return binarySearch(T, x, srodekIndeks+1, prawy);
        }
        else if (x < T[srodekIndeks]) {
            //lezy po lewej stronie tablicy (jesli jest posortowana rosnaco)
            return binarySearch(T, x, lewy, srodekIndeks);
        }
    }
    return -1;
}