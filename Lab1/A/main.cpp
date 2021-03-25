#include <fstream>

using namespace std;

int main() {
    int a, b;
    ifstream fin("aplusbI.txt");
    ofstream fout("aplusbO.txt");
    fin >> a >> b;
    fout << a + b << "\n";
    return 0;
}