#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

void qSort(int *a, int l, int r, int k) {
    if (l >= r)
        return;
    
    int f = 0;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] != a[i - 1]) {
            f = 1;
            break;
        }
    }

    if (f == 0)
        return;

    int pivot = a[r];

    int j = l;
    for (int i = l; i < r; i++) {
        if (a[i] < pivot) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            j++;
        }
    }

    a[r] = a[j];
    a[j] = pivot;

    //now element [j-1] == pivot is on the correct place
    int pivotIndex = j;
    j++;

    while (j <= r && a[j] == a[j - 1])
        j++;
    //now element [j] is the first elem which is more than pivot

    //[(L) <pivot (pivot_index-1)][(pivotIndex) == pivot (j-1)][(j) > pivot (R)]
    if (k >= pivotIndex && k <= j - 1)
        return;

    if (k < pivotIndex)
        qSort(a, l, pivotIndex - 1, k);
    else
        qSort(a, j, r, k);


}

int main() {
    FILE *in = fopen("kth.in", "r");
    FILE *out = fopen("kth.out", "w");
    //FILE* in = fopen("input.txt", "r");
    //FILE* out = fopen("output.txt", "w");

    int n, k, A, B, C, a1, a2;
    fscanf(in, "%d %d", &n, &k);
    fscanf(in, "%d %d %d %d %d", &A, &B, &C, &a1, &a2);

    if (n == 1) {
        fprintf(out, "%d", a1);
        return 0;
    }
    if (n == 2) {
        fprintf(out, "%d", a2);
        return 0;
    }

    int *a = (int *) malloc(n * sizeof(int));
    a[0] = a1;
    a[1] = a2;

    for (int i = 2; i < n; i++) {
        a[i] = a[i - 2] * A + a[i - 1] * B + C;
    }

    qSort(a, 0, n - 1, k - 1);

    fprintf(out, "%d", a[k - 1]);
    fclose(in);
    fclose(in);
}