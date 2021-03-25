#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream fin("race.in");
    ofstream fout("race.out");
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/
    int n;
    fin >> n;

    string *country = new string[n];
    string *name = new string[n];

    for (int i = 0; i < n; i++) {
        fin >> country[i] >> name[i];
    }

    for (int i = 0; i < n - 1; i++) {
        string min = country[i];
        int index = i;

        for (int j = i + 1; j < n; j++) {
            if (country[j] < min) {
                min = country[j];
                index = j;
            }
        }

        if (i != index) {
            swap(name[i], name[index]);
            swap(country[i], country[index]);
        }
    }

    string temp = country[0];
    fout << "=== " << temp << " ===\n";
    fout << name[0] << "\n";

    for (int i = 1; i < n; i++) {
        if (temp == country[i]) {
            fout << name[i] << "\n";
        } else {
            temp = country[i];
            fout << "=== " << temp << " ===\n";
            fout << name[i] << "\n";
        }
    }
}