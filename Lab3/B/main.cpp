#include <iostream>
#include <fstream>

using namespace std;

void heapify(int mas[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && mas[l] > mas[largest]) largest = l;
    if (r < n && mas[r] > mas[largest]) largest = r;
    if (largest != i) {
        swap(mas[i], mas[largest]);
        heapify(mas, n, largest);
    }
}

void heapSort(int mas[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(mas, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(mas[0], mas[i]);
        heapify(mas, i, 0);
    }
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    /*ifstream fin("sort.in");
    ofstream fout("sort.out");*/

    int n;
    fin >> n;
    int *mas = new int[n];

    for (int i = 0; i < n; i++) {
        fin >> mas[i];
    }

    heapSort(mas, n);
    for (int i = 0; i < n; i++) fout << mas[i] << " ";
}