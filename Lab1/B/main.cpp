#include <fstream>

using namespace std;

int main()
{
    long long a, b;
    ifstream fin("aplusbbI.txt");
    ofstream fout("aplusbbO.txt");
    fin >> a >> b;
    fout << a + b * b << "\n";
    fin.close();
    fout.close();
    return 0;
}