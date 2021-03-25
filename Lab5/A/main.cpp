#include <fstream>

using namespace std;

int height(int root, int tree[][2]) {
    if (tree[root][0] == -1 && tree[root][1] == -1) return 1;

    int l = 0;
    int r = 0;

    if (tree[root][1] != -1) r = height(tree[root][1], tree);
    if (tree[root][0] != -1) l = height(tree[root][0], tree);

    return max(l + 1, r + 1);
}

int main() {
    ifstream fin("height.in");
    ofstream fout("height.out");

    int n;
    fin >> n;

    int tree[n][2];
    int k, l, r;

    for (int i = 0; i < n; ++i) {
        fin >> k >> l >> r;
        tree[i][0] = l - 1;
        tree[i][1] = r - 1;
    }

    if (n != 0) fout << height(0, tree);
    else fout << "0";
}