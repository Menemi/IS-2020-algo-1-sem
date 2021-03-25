#include <fstream>

using namespace std;

int *Merge(int *start, int first, int *final, int last) {
    int *c = new int[(first + last) * 4];
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < first || j < last) {
        if (i == first || (j < last && start[i] >= final[j])) {
            c[k] = final[j];
            j++;
        } else {
            c[k] = start[i];
            i++;
        }
        k++;
    }

    return c;
}

int *Merge_sort(int *mas, int len) {
    if (len == 1) {
        return mas;
    }

    int *start = mas;
    int first = len / 2;

    int *final = mas + first;
    int last = len - len / 2;

    start = Merge_sort(start, first);
    final = Merge_sort(final, last);

    int *new_mas = Merge(start, first, final, last);

    return new_mas;
}

int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");

    int n;
    fin >> n;

    int *mas = new int[n * 4];

    for (int i = 0; i < n; i++) {
        fin >> mas[i];
    }

    mas = Merge_sort(mas, n);

    for (int i = 0; i < n; i++) {
        fout << mas[i] << " ";
    }

    fin.close();
    fout.close();

    return 0;
}