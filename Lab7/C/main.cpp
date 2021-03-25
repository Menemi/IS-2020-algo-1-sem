#include <fstream>
#include <vector>
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

struct BiggerTree {
    int key;
    int height;

    BiggerTree *left;
    BiggerTree *right;

    BiggerTree(int key) : key(key) {
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
private:
    BiggerTree *root = NULL;
    int size = 0;

    int showH(BiggerTree *myTree) {
        if (myTree == NULL)
            return 0;
        return myTree->height;
    }

    void editH(BiggerTree *myTree) {
        myTree->height = max(this->showH(myTree->left), this->showH(myTree->right)) + 1;
    }

    int balance(BiggerTree *myTree) {
        return this->showH(myTree->right) - this->showH(myTree->left);
    }

    BiggerTree *depthFirstSearch(vector<Tree> &tempVec, int top) {
        if (top < 0 || tempVec.size() == 0)
            return NULL;

        BiggerTree *temp = new BiggerTree(tempVec[top].key);
        this->size++;

        temp->left = depthFirstSearch(tempVec, tempVec[top].left);
        temp->right = depthFirstSearch(tempVec, tempVec[top].right);
        temp->height = max(this->showH(temp->left), this->showH(temp->right)) + 1;

        return temp;
    }

    BiggerTree *balancedTree(BiggerTree *myTree) {
        if (this->balance(myTree) > 1) {
            if (this->balance(myTree->right) < 0)
                myTree->right = this->Right(myTree->right);

            return this->Left(myTree);
        }

        if (this->balance(myTree) < -1) {
            if (this->balance(myTree->left) > 0)
                myTree->left = this->Left(myTree->left);

            return this->Right(myTree);
        }

        return myTree;
    }

    BiggerTree *rotation(BiggerTree *myTree, bool check) {
        BiggerTree *temp = check ? myTree->right : myTree->left;

        if (check) {
            myTree->right = temp->left;
            temp->left = myTree;
        } else {
            myTree->left = temp->right;
            temp->right = myTree;
        }

        this->editH(myTree);
        this->editH(temp);

        return temp;
    }

    BiggerTree *depthFirstSearch(int key, BiggerTree *now) {
        if (now == NULL)
            return new BiggerTree(key);

        if (key > now->key)
            now->right = depthFirstSearch(key, now->right);

        else
            now->left = depthFirstSearch(key, now->left);

        this->editH(now);
        return this->balancedTree(now);
    }

public:
    BiggerTree *Left(BiggerTree *myTree) {
        return this->rotation(myTree, true);
    }

    BiggerTree *Right(BiggerTree *myTree) {
        return this->rotation(myTree, false);
    }

    void showTree(vector<Tree> &tempVec) {
        this->root = this->depthFirstSearch(tempVec, 0);
    }

    void push(int key) {
        this->root = this->depthFirstSearch(key, this->root);
        this->size++;
    }

    void showT() {
        queue<BiggerTree *> breadthFirstSearch;
        breadthFirstSearch.push(this->root);
        int line = 1;
        fout << this->size << endl;

        while (!breadthFirstSearch.empty()) {
            BiggerTree *myTree = breadthFirstSearch.front();
            breadthFirstSearch.pop();
            int left = 0, right = 0;

            if (myTree->right != NULL) {
                breadthFirstSearch.push(myTree->right);
                right = ++line;
            }

            if (myTree->left != NULL) {
                breadthFirstSearch.push(myTree->left);
                left = ++line;
            }

            fout << myTree->key << " " << left << " " << right << endl;
        }
    }
};

int main() {
    int n;
    fin >> n;
    vector<Tree> mySecondTree(n);

    for (int i = 0; i < n; i++) {
        fin >> mySecondTree[i].key >> mySecondTree[i].left >> mySecondTree[i].right;
        mySecondTree[i].left--;
        mySecondTree[i].right--;
    }

    AVLTree *tempClass = new AVLTree();
    tempClass->showTree(mySecondTree);

    int pushElement;
    fin >> pushElement;

    tempClass->push(pushElement);
    tempClass->showT();
}