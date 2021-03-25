#include <fstream>
#include <string>

using namespace std;

ifstream fin("brackets.in");
ofstream fout("brackets.out");
//ifstream fin("in.txt");
//ofstream fout("out.txt");

int main() {
    string str;

    while (fin >> str) {
        string stack;
        int head = -1;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(' || str[i] == '[' || stack.length() == 0) {
                stack += str[i];
                head++;
            } else if (str[i] == ']' && stack[head] == '[') {
                stack.erase(stack.begin() + head);
                head--;
            } else if (str[i] == ')' && stack[head] == '(') {
                stack.erase(stack.begin() + head);
                head--;
            } else {
                stack += str[i];
            }
        }

        if (stack.length() == 0) fout << "YES\n";
        else fout << "NO\n";
    }
}