#include <iostream>
#include <fstream>

using namespace std;

int main() {
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/
    ifstream fin("isheap.in");
    ofstream fout("isheap.out");

    int n;
    fin >> n;
    int *mas = new int[n + 1];
    bool temp = 1;

    for (int i = 1; i < n + 1; i++) {
        fin >> mas[i];
    }

    for (int i = 1; i < n / 2; i++) {
        if ((2 * i > n) || (mas[i] > mas[2 * i])) temp = 0;
        if (((2 * i) + 1 > n) || (mas[i] > mas[(2 * i) + 1])) temp = 0;
    }

    if (temp == 1) fout << "YES";
    else fout << "NO";
}