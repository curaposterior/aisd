#include <iostream>
using namespace std;

/*
Wiekszosc kodu zostala zredagowana na  podstawie strony
http://cslibrary.stanford.edu/110/BinaryTrees.html
*/

struct tree {
    int data;
    tree* left;
    tree* right;
};

//printing functions for testing
void printBT(const string &prefix, const tree *tree, bool isLeft);
void printBT(const tree *tree); 
void inorder(const tree* root);
void postorder(const tree* root);
void preorder(const tree* root);
void printPaths(tree* root);
void printPathsRecur(tree* root, int path[], int pathLen);
void printArray(int tab[], int n);

//all functions:
static int lookup(tree* root, int target);
tree* insert(tree* root, int x);
tree* build123();
int size(tree* root);
int maxDepth(tree* root);
int minValue(tree* root);
tree* minValueAddress(tree* root);
int maxValue(tree* root);
tree* maxValueAddress(tree* root);
int hasPathSum(tree* root, int sum);
tree* copy(tree* root);
tree* mirrorTree(tree* root);
void mirror(tree* root);
void doubleTree(tree* root);
int sameTree(tree* a, tree* b);
int isBST1(tree* root);

tree* predecessor(tree* root);
// int isBST2(tree* root);

int main(void) {
    tree* root = nullptr;
    
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 9);
    root = insert(root, 6);

    // root = build123();
    printBT(root);
    cout << "Wysokosc drzewska: " << maxDepth(root) << endl;
    cout << "Maksymalna wartosc drzewska: " << maxValue(root) << endl;
    //3 glowne metody przechodzenia drzewa:
    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
    postorder(root);
    cout << endl;
    cout << "has path sum (1 - exists, 2 - doesn't exist): " << hasPathSum(root, 4) << endl;
    printPaths(root);
    cout << endl;
    
    tree* rootCopy = copy(root);
    cout << "Czy drzewa sa takie same: " << sameTree(root, rootCopy) << endl;
    
    
    cout << "Czy drzewo jest BST: " << isBST1(rootCopy) << endl;

    tree* pop = predecessor(root);
    cout << "Poprzednik korzenia: " << pop->data << endl;


    return 0;
}


static int lookup(tree* root, int target) { 
    while (root && root->data != target) {
        if (root->data > target) root = root->left;
        else root = root->right;
    }
    if (root->data == target)
        return (true);
    else return (false);
}

tree* build123() { // proste drzewo 2, 1, 3
    tree* p = nullptr;
    p = insert(p, 2);
    p = insert(p, 1);
    p = insert(p, 3);

    return p;
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

tree* NewNode(int data) { // tworzenie wezla
    tree* p = new tree;    // "new" is like "malloc"
    p->data = data;
    p->left = NULL;
    p->right = NULL;

    return(p);
}

tree* insert(tree* root, int x) { // wstawianie wezla
    if (root == nullptr)
        return (NewNode(x));
    else {
        if (x <= root->data) root->left = insert(root->left, x);
        else root->right = insert(root->right, x);

        return (root);
    }
}


int size(tree* root) { // obliczanie rozmiaru drzewa
    if (root == nullptr)
        return (0);
    else 
        return size(root->left) + 1 + size(root->right);
}


int maxDepth(tree* root) { // obliczanie wysokosci drzewa
    if (root == nullptr)
        return (0);
    else {
        int lDepth = maxDepth(root->left);
        int rDepth = maxDepth(root->right);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else 
            return (rDepth + 1);
    }
}

int minValue(tree* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return (root->data);
}

tree* minValueAddress(tree* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return (root);
}

int maxValue(tree* root) {
    while (root && root->right) {
        root = root->right;
    }
    return (root->data);
}

tree* maxValueAddress(tree* root) {
    while (root && root->right) {
        root = root->right;
    }
    return (root);
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

/*
Funkcja zwracajaca prawde/falsz gdy suma wartosci węzłów, które 
kończą się liściem (root-to-leaf path) jest rowna podanej sumie
*/
int hasPathSum(tree* root, int sum) {
    if (root == nullptr)
        return (sum == 0);
    else {
        int pSum = sum - root->data;
        return (hasPathSum(root->left, pSum) ||
                hasPathSum(root->right, pSum));
    }
}


/*
Funkcja wypisujaca sciezki root-to-leaf korzystajaca
z funkcji printPathRecur().
Schodzimy kolejnymi wezlami od korzenia do
lisci.
*/
void printPaths(tree* root) {
    int tab[1000];
    printPathsRecur(root, tab, 0);
}

/*
Funkcja pomocnicza wypisująca scieżki root-to-leaf.
*/
void printPathsRecur(tree* root, int path[], int pathLen) {
    if (root == nullptr) return;

    path[pathLen] = root->data;
    pathLen++;

    //jesli root to lisc:
    if (!(root->left) && !(root->right))
        printArray(path, pathLen);
    else {
        printPathsRecur(root->left, path, pathLen);
        printPathsRecur(root->right, path, pathLen);
    }
}

/*
Wypisz zawartosc tablicy.
*/
void printArray(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;
}

/*
Tworzenie kopii drzewa
*/
tree* copy(tree* root) {
    if (root == nullptr)
        return nullptr;

    tree* p = new tree;
    p->data = root->data;

    p->left = copy(root->left);
    p->right = copy(root->right);

    return p;
}

/*
Stworzenie lustrzanego odbicia drzewa. Tworzony jest
nowy obiekt (kopia root) i na nim przeprowadzamy funkcje
mirror().
*/
tree* mirrorTree(tree* root) {
    tree* p = copy(root);
    mirror(p);
    return p;
}

/*
Tworzenie lustrzanego odbicia drzewa
*/
void mirror(tree* root) {
    // tree* newRoot = copy(root);
    if (root == nullptr)
        return;
    else {
        tree* temp = nullptr;
        mirror(root->left);
        mirror(root->right);

        temp = root->left;
        root->left = root->right;
        root->right = temp;
        // delete temp;
    }
}

/*
Skopiowanie kazdego elementu, tak aby wystepowal w drzewie x2 razy.
Obiekt przekazywany do funkcji jest zmieniany (nie tworzy kopii, jesli
nie chcesz utracic pierwotnego drzewa zrob kopie)
*/
void doubleTree(tree* root) {
    tree* oldNode = nullptr;
    if (root == nullptr)
        return;
    else {
        doubleTree(root->left);
        doubleTree(root->right);
        
        oldNode = root->left;
        root->left = NewNode(root->data);
        root->left->left = oldNode;
    }
}

/*
Funkcja zwracajaca prawde jezeli drzewa a i b
sa takie same i falsz jezeli sa rozne.
*/
int sameTree(tree* a, tree* b) {
    if (!a && !b) return (true);
    else if (a && b)
        return (a->data == b->data && 
                sameTree(a->left, b->left) &&
                sameTree(a->right, b->right)
                );
    else return (false);
}

int isBST1(tree* root) {
    if (root == nullptr) return (true);
    if (root->left && maxValue(root->left) > root->data)
        return (false);
    if (root->right && minValue(root->right) <= root->data)
        return (false);
    if (!isBST1(root->left) || !isBST1(root->right))
        return (false);
    return (true);
}

/*
Source:
https://eduinf.waw.pl/inf/utils/002_roz/mp001.php
*/
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
