#include <fstream>
#include <iostream>

using namespace std;

int max(int a, int b) {
    if (b > a) return b;
    else return a;
}

int main() {
    ifstream fin("turtleI.txt");
    ofstream fout("turtleO.txt");
    int h, w, result;
    fin >> h >> w;

    int **ArrDistance = new int *[h];
    int **ArrGiven = new int *[h];

    for (int i = 0; i < h; i++) {
        ArrDistance[i] = new int[w];
        ArrGiven[i] = new int[w];
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fin >> ArrGiven[i][j];
            ArrDistance[i][j] = ArrGiven[i][j];
        }
    }

    ArrDistance[h - 1][0] = ArrGiven[h - 1][0];
    for (int i = h - 2; i >= 0; i--) //filling cells in bottom line
    {
        ArrDistance[i][0] = ArrDistance[i + 1][0] + ArrGiven[i][0];
    }

    for (int i = 1; i < w; i++) //filling cells in first column
    {
        ArrDistance[h - 1][i] = ArrDistance[h - 1][i - 1] + ArrGiven[h - 1][i];
    }

    for (int i = h - 2; i >= 0; i--) //filling all the other cells until the last one
    {
        for (int j = 1; j < w; j++) {
            ArrDistance[i][j] = max(ArrDistance[i + 1][j], ArrDistance[i][j - 1]) + ArrGiven[i][j];
        }
    }

    fout << ArrDistance[0][w - 1];
}
