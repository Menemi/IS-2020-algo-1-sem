#include <fstream>

using namespace std;

ifstream fin("linkedmap.in");
ofstream fout("linkedmap.out");
//ifstream fin("in.txt");
//ofstream fout("out.txt");

struct Hash {
    string key;
    string value;
    Hash *previous;
    Hash *next = NULL;
    Hash *first;
    Hash *last = NULL;
};

struct map {
    Hash *table[1000000];
    Hash *Last = NULL;
    int simple_numbers[10]
            = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    int index(string key) {
        int result = 0;
        for (int i = 0; i < key.length(); i++) {
            result += simple_numbers[abs(key[i] - 'a') % 10] * simple_numbers[i % 10];
        }

        return result % 1000000;
    }

    void put(string key, string value) {
        int temp = index(key);

        if (table[temp] == NULL) {
            Hash *temp2 = new Hash(key, value, Last);
            table[temp] = temp2;
            if (Last != NULL)
                Last->last = temp2;
            Last = temp2;
        } else {
            Hash *p = table[temp];
            while (p->next != NULL && p->key != key)
                p = p->next;

            if (p->key != key) {
                Hash *temp2 = new Hash(key, value, Last, p);
                p->next = temp2;
                if (Last != NULL) Last->last = temp2;
                Last = temp2;
            } else
                p->value = value;
        }
    }

    Hash *searchOfPtr(string key) {
        int temp = index(key);

        if (table[temp] == NULL)
            return NULL;
        else {
            Hash *p = table[temp];

            while (p->next != NULL && p->key != key)
                p = p->next;
            if (p->key == key)
                return p;
            else
                return NULL;
        }
    }

    string get(string key) {
        Hash *temp2 = searchOfPtr(key);

        if (temp2 == NULL)
            return "none";
        else
            return temp2->value;
    }

    string prev(string key) {
        Hash *temp2 = searchOfPtr(key);

        if (temp2 == NULL || temp2->first == NULL)
            return "none";
        return
                temp2->first->value;
    }

    string next(string key) {
        Hash *temp2 = searchOfPtr(key);

        if (temp2 == NULL || temp2->last == NULL)
            return "none";
        return
                temp2->last->value;
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

                if (p->first != NULL)
                    p->first->last = p->last;

                if (p->last != NULL)
                    p->last->first = p->first;

                if (Last == p)
                    Last = p->first;

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
        else if (command == "get")
            fout << (myHash->get(key)) << "\n";
        else if (command == "prev")
            fout << (myHash->prev(key)) << "\n";
        else
            fout << (myHash->next(key)) << "\n";
    }
}