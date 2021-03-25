#include <fstream>
#include <vector>

using namespace std;

struct tree {
    long long k;
    int l;
    int r;
};

bool GLOBAL_CHECK = true;
vector<tree> myTree;

void check(int value, long long min, long long max) {
    if (myTree[value].k <= min || myTree[value].k >= max) GLOBAL_CHECK = 0;

    if (myTree[value].l != 0) check(myTree[value].l, min, myTree[value].k);

    if (myTree[value].r != 0) check(myTree[value].r, myTree[value].k, max);
}

int main() {
    ifstream fin("check.in");
    ofstream fout("check.out");
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/

    int n;
    fin >> n;

    if (n == 0) fout << "YES";
    else {
        myTree.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            fin >> myTree[i].k >> myTree[i].l >> myTree[i].r;
        }

        check(1, -1000000000, 1000000000);

        if (GLOBAL_CHECK == false) fout << "NO";
        else fout << "YES";
    }
}