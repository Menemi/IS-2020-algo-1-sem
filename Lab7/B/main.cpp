#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("addition.in");
ofstream fout("addition.out");
//ifstream fin("in.txt");
//ofstream fout("out.txt");

struct Tree {
    int key;
    int left;
    int right;
};

class AVLTree {
private:
    vector <Tree> myTree;
    vector<int> height;

    int depthFirstSearch(int top, int height) {
        if (top < 0)
            return 0;

        this->height[top] =
                max(depthFirstSearch(this->myTree[top].left, height),
                    depthFirstSearch(this->myTree[top].right, height)) + 1;

        return this->height[top];
    }

    void editH(int top) {
        this->height[top] =
                max(this->showH(this->myTree[top].left), this->showH(this->myTree[top].right)) + 1;
    }

public:
    void push(Tree *node) {
        this->myTree.push_back(*node);
        this->height.push_back(0);
    }

    int showH(int top) {
        if (top < 0)
            return 0;

        return this->height[top];
    }

    void calculatingH() {
        depthFirstSearch(0, 0);
    }

    int Left(int top) {
        int b = this->myTree[top].right;

        this->myTree[top].right = this->myTree[b].left;
        this->myTree[b].left = top;
        this->editH(top);
        this->editH(b);

        return b;
    }

    int Right(int top) {
        int b = this->myTree[top].left;

        this->myTree[top].left = this->myTree[b].right;
        this->myTree[b].right = top;
        this->editH(top);
        this->editH(b);

        return b;
    }

    int bigLeft(int top) {
        this->myTree[top].right = this->Right(this->myTree[top].right);

        return this->Left(top);
    }

    int defineOfRotation(int top) {
        int right = this->myTree[top].right;

        int leftChild = this->showH(this->myTree[right].left);
        int rightChild = this->showH(this->myTree[right].right);

        if (rightChild - leftChild < 0)
            return this->bigLeft(top);

        return this->Left(top);
    }

    void printT(int root) {
        fout << this->myTree.size() << "\n";
        queue<int> que;
        que.push(root);
        int line = 1;

        while (!que.empty()) {
            int top = que.front();
            que.pop();
            int left, right;

            left = 0;
            right = 0;

            if (this->myTree[top].left >= 0) {
                que.push(this->myTree[top].left);
                left = ++line;
            }

            if (this->myTree[top].right >= 0) {
                que.push(this->myTree[top].right);
                right = ++line;
            }

            fout << this->myTree[top].key << " " << (left) << " " << (right) << "\n";
        }
    }
};

int main() {
    int n;
    fin >> n;
    Tree mySecondTree;
    AVLTree *tempClass = new AVLTree();

    for (int i = 0; i < n; i++) {
        fin >> mySecondTree.key >> mySecondTree.left >> mySecondTree.right;
        mySecondTree.left--;
        mySecondTree.right--;
        tempClass->push(&mySecondTree);
    }

    tempClass->calculatingH();
    int newRoot = tempClass->defineOfRotation(0);
    tempClass->printT(newRoot);
}