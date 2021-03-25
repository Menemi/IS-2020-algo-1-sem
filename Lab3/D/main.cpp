#include <fstream>
#include <iostream>

using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("priorityqueue.in");
ofstream fout("priorityqueue.out");

void Min(int mas[], int i, int n) {
    int l = i * 2;
    int r = i * 2 + 1;
    int smallest;

    if (l <= n && mas[l] < mas[i]) smallest = l;
    else smallest = i;

    if (r <= n && mas[r] < mas[smallest]) smallest = r;

    if (smallest != i) {
        swap(mas[i], mas[smallest]);
        Min(mas, smallest, n);
    }
}

void extractMin(int mas[], int &n) {
    if (n < 1) {
        fout << "*\n";
        return;
    }

    int min = mas[1];
    mas[1] = mas[n];
    n--;
    Min(mas, 1, n);
    fout << min << "\n";
    return;
}

void decreaseKey(int mas[], int i, int key) {
    mas[i] = key;
    while (i > 1 && mas[i / 2] > mas[i]) {
        swap(mas[i], mas[i / 2]);
        i = i / 2;
    }
}

void push(int mas[], int key, int &n) {
    n++;
    mas[n] = INT_MAX;
    decreaseKey(mas, n, key);
}

int main() {
    int archive[100000], heap[100000];
    string command;
    int x, y, n = 0, count = 0;

    while (fin >> command) {
        if (command == "push") {
            fin >> x;
            push(heap, x, n);
        } else if (command == "extract-min") {
            x = -1;
            extractMin(heap, n);
        } else if (command == "decrease-key") {
            fin >> x >> y;
            int i;

            for (i = 1; i <= n; i++) {
                if (archive[x] == heap[i]) break;
            }

            decreaseKey(heap, i, y);
            archive[x] = y;
        }
        count++;
        archive[count] = x;
    }
}
