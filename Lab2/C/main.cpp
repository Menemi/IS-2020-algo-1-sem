#include <fstream>

using namespace std;

unsigned long long RESULT = 0;

int *Merge(int *start, int first, int *final, int last) {
    int *new_mas = new int[(first + last) * 4];
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < first || j < last) {
        if (i < first && j < last) {
            if (start[i] > final[j]) {
                RESULT += first - i;
                new_mas[k] = final[j];
                j++;
            } else {
                new_mas[k] = start[i];
                i++;
            }
        } else if (i == first || (j < last && start[i] > final[j])) {
            new_mas[k] = final[j];
            j++;
        } else {
            new_mas[k] = start[i];
            i++;
        }
        k++;
    }

    return new_mas;
}

int *Merge_sort(int *a, int length) {
    if (length == 1) {
        return a;
    }

    int *start = a;
    int first = length / 2;

    int *final = a + first;
    int last = length - length / 2;

    start = Merge_sort(start, first);
    final = Merge_sort(final, last);

    int *new_a = Merge(start, first, final, last);

    return new_a;
}

int main() {
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/

    int n;
    fin >> n;

    int *mas = new int[n * 4];

    for (int i = 0; i < n; i++) {
        fin >> mas[i];
    }

    mas = Merge_sort(mas, n);

    fout << RESULT;

    fin.close();
    fout.close();
}