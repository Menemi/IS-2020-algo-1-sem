#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");

    int n;
    fin >> n;

    vector<vector<int>> tree(n, vector<int>(3));
    int l, r;

    for (int i = 0; i < n; ++i) {
        fin >> tree[i][0];
        fin >> tree[i][1];
        fin >> tree[i][2];
    }

    vector<int> h(n + 1);
    for (int i = n; i > 0; i--) {
        l = tree[i - 1][1];
        r = tree[i - 1][2];
        h[i] = 1 + max(h[l], h[r]);
    }

    for (int i = 0; i < n; i++)
        fout << h[tree[i][2]] - h[tree[i][1]] << "\n";
}