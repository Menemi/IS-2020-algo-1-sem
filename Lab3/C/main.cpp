#include <iostream>

using namespace std;

int main() {
    int n, m, k; //количество, длина, число раз сортировки
    cin >> n >> m >> k;
    char **mas = new char *[n];

    for (int i = 0; i < n; i++) {
        mas[i] = new char[m];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mas[i][j];
        }
    }

    for (int i = k - 1; i >= 0; i--) // цифровая сортировка
    {
        for (int j = n - 1; j > 0; j--) // сортировка пузырьком
        {
            for (int f = n - j - 1; f > 0; f--) {
                if (mas[j][i] < mas[j - 1][i]) {
                    for (int l = 0; l < m; l++) // swap полной строки, а не одной буквы
                    {
                        swap(mas[j][l], mas[j - 1][l]);
                    }
                }
            }
        }
    }

    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mas[i][j];
        }
        cout << "\n";
    }
}