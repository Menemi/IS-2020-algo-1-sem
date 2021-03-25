#include <fstream>
#include <iostream>

using namespace std;

int main() {
    int n;
    ifstream fin("smallsortI.txt");
    ofstream fout("smallsortO.txt");
    fin >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        fout << arr[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}