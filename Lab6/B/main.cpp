#include <fstream>

using namespace std;

ifstream fin("map.in");
ofstream fout("map.out");
//ifstream fin("in.txt");
//ofstream fout("out.txt");

struct Hash {
    string value;
    string key;
    Hash *previous;
    Hash *next = NULL;

    Hash(string key, string value, Hash *previous = NULL) : key(key), value(value), previous(previous) {}
};

struct map {
    Hash *table[1000000];
    int simple_numbers[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    int index(string key) {
        int result = 0;
        for (int i = 0; i < key.length(); i++) {
            result += simple_numbers[abs(key[i] - 'a') % 10] * simple_numbers[i % 10];
        }
        return result % 1000000;
    }

    void put(string key, string value) {
        int temp = index(key);

        if (table[temp] == NULL)
            table[temp] = new Hash(key, value);
        else {
            Hash *p = table[temp];
            while (p->next != NULL && p->key != key)
                p = p->next;
            if (p->key != key)
                p->next = new Hash(key, value, p);
            else
                p->value = value;
        }
    }

    string get(string key) {
        int temp = index(key);
        if (table[temp] == NULL) return "none";
        else {
            Hash *p = table[temp];
            while (p->next != NULL && p->key != key) p = p->next;
            if (p->key == key) return p->value;
            else return "none";
        }
    }

    void del(string key) {
        int temp = index(key);
        if (table[temp] == NULL)
            return;
        else {
            Hash *p = table[temp];

            while (p->next != NULL && p->key != key)
                p = p->next;

            if (p->key == key) {
                if (table[temp] == p)
                    table[temp] = p->next;

                if (p->previous != NULL)
                    p->previous->next = p->next;

                if (p->next != NULL)
                    p->next->previous = p->previous;

                p = NULL;
            }
        }
    }
};

int main() {
    map *myHash = new map();
    string command;

    while (fin >> command) {
        string key;
        fin >> key;

        if (command == "put") {
            string value;
            fin >> value;
            myHash->put(key, value);
        } else if (command == "delete")
            myHash->del(key);
        else
            fout << (myHash->get(key)) << "\n";
    }
}