#include <iostream>
#include <fstream>
using namespace std;


int main(void) {
    srand(NULL); // not safe
    ofstream nums;
    int* T = new int[1000000];
    nums.open("numbers.txt");
    for (int f = 0; f < 100000 ;f++) {
        T[f] = (rand() % (1000 + 1 - 1)) + 1;
        nums << T[f] << endl;
    }
    nums << 10; //avoid newline and the end of the file
    nums.close();
    return 0;
}