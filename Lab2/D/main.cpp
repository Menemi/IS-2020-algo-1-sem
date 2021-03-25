#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("antiqs.in");
    ofstream fout("antiqs.out");
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/

    int n;
    fin >> n;

    if (n == 1)
        fout << "1";
    else if (n == 2)
        fout << "2 1";


    int *mas = new int[n * 4];
    mas[0] = 1;
    mas[1] = 3;
    mas[2] = 2;

    for (int i = 3; i < n; i++) {
        mas[i] = i + 1;
        swap(mas[i / 2], mas[i]);
    }

    for (int i = 0; i < n; i++) {
        fout << mas[i] << " ";
    }

    fin.close();
    fout.close();
}