#include <fstream>

using namespace std;

int main() {
    /*ifstream cin("stack.in");
    ofstream cout("stack.out");*/
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    int m;
    int head = 0;
    char znak;
    fin >> m;
    int *mas = new int[m];

    for (int i = 0; i < m; i++) {
        fin >> znak;

        if (znak == '+') {
            fin >> mas[head];
            head++;
        } else {
            head--;
            fout << mas[head] << endl;
        }
    }
}