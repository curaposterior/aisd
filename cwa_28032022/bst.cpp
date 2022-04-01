#include <iostream>

using namespace std;

struct tree {
    int val;
    tree* L;
    tree* R;
};

void insert();
void inorder();
tree* search(tree*, int);

//printing functions 
//(more on https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way?msclkid=0c64912cae8111ecb1e338860958d0d7)
void printRow(const tree* p, const int, int);


int main(void) {


    return 0;
}
