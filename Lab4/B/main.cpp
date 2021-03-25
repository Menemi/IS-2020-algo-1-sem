#include <fstream>

using namespace std;

const int QMAX = 1000000;

struct queue {
    int qu[QMAX];
    int back, front;
};

void init(struct queue *q) {
    q->front = 1;
    q->back = 0;
    return;
}

void insert(struct queue *q, int x) {
    if (q->back < QMAX - 1) {
        q->back++;
        q->qu[q->back] = x;
    }
    return;
}

int remove(struct queue *q) {
    int temp;
    temp = q->qu[q->front];
    q->front++;
    return temp;
}

int main() {
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/
    ifstream fin("queue.in");
    ofstream fout("queue.out");

    struct queue *q = new struct queue[sizeof(queue *)];
    init(q);
    int m;
    fin >> m;

    int *mas = new int[m];

    for (int i = 0; i < m; i++) {
        char command;
        fin >> command;
        int number;

        if (command == '+') {
            fin >> number;
            insert(q, number);
        } else {
            fout << remove(q) << "\n";
        }
    }
}