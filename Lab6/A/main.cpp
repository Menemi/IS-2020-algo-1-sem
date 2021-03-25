#include <fstream>

using namespace std;

ifstream fin("set.in");
ofstream fout("set.out");
//ifstream fin("in.txt");
//ofstream fout("out.txt");

struct hAsh {
    int value;
    struct hAsh *next;
};
hAsh **hashTable;

int myHash(int value) {
    return abs(value % 1000001);
}

bool exists(int value) {
    hAsh *temp;
    temp = hashTable[myHash(value)];

    while (temp && (temp->value != value)) {
        temp = temp->next;
    }

    if (temp == NULL) return false;
    else return true;
}

int insert(int value) {
    hAsh *temp, *temp2;
    int index = myHash(value);
    temp = new hAsh;
    if (exists(value)) return 0;

    temp2 = hashTable[index];
    hashTable[index] = temp;
    temp->next = temp2;
    temp->value = value;
    return 0;
}

void del(int value) {
    hAsh *temp, *temp2;
    int index;
    temp2 = 0;
    index = myHash(value);
    temp = hashTable[index];

    while (temp && (temp->value != value)) {
        temp2 = temp;
        temp = temp->next;
    }

    if (!temp) return;
    if (temp2) temp2->next = temp->next;
    else hashTable[index] = temp->next;
    temp = NULL;
}

int main() {
    hashTable = new hAsh *[1000000];
    for (int i = 0; i < 1000000; i++) {
        hashTable[i] = NULL;
    }
    string command;

    while (fin >> command) {
        int value;
        fin >> value;

        if (command == "insert") insert(value);
        else if (command == "delete") del(value);
        else {
            if (exists(value)) fout << "true" << "\n";
            else fout << "false" << "\n";
        }
    }
}