#include <fstream>

using namespace std;

double B(double h[], int n) {
    double left = 0;
    double right = h[0];

    while (right - left > 0.0000000001) {
        h[1] = (left + right) / 2;
        bool check = 1;

        for (int i = 2; i < n; i++) {
            h[i] = 2 * h[i - 1] - h[i - 2] + 2;

            if (h[i] < 0) {
                check = 0;
                break;
            }
        }

        if (check) right = h[1];
        else left = h[1];
    }
    return h[n - 1];
}

int main() {
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/
    ifstream fin("garland.in");
    ofstream fout("garland.out");

    int n;
    fin >> n;

    double *h = new double[n];
    fin >> h[0];

    double A = B(h, n);
    fout.precision(2);

    fout << fixed << A;
}