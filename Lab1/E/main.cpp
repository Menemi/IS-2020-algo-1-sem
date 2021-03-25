#include <fstream>
#include <iostream>

using namespace std;

int main() {
    int n;
    ifstream fin("sortlandI.txt");
    ofstream fout("sortlandO.txt");
    fin >> n;

    float *ArrPrices = new float[n]; //array with prices
    float *ArrIndex = new float[n]; //array with indexes
    for (int i = 0; i < n; i++) {
        fin >> ArrPrices[i];
        ArrIndex[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ArrPrices[j] > ArrPrices[j + 1]) {
                swap(ArrIndex[j], ArrIndex[j + 1]);
                swap(ArrPrices[j], ArrPrices[j + 1]);
            }
        }
    }
    // +1 везде, тк индексы начинаются с нуля, а порядковые номера в задании с 1
    // n-1 - последнее выводимое число по тому же принципу,
    // что и с индексами, и порядковыми номерами
    fout << "\n"
         << ArrIndex[0] + 1 << " "
         << ArrIndex[n / 2] + 1 << " "
         << ArrIndex[n - 1] + 1;

    fin.close();
    fout.close();
    return 0;
}