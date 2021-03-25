#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("deletion.in");
ofstream fout("deletion.out");
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
        if (myTree == NULL) return 0;
        return myTree->height;
    }

    void editH(BiggerTree *myTree) {
        myTree->height = max(
                this->showH(myTree->left),
                this->showH(myTree->right)) + 1;
    }

    int balance(BiggerTree *myTree) {
        return this->showH(myTree->right) - this->showH(myTree->left);
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

    BiggerTree *depthFirstSearch(vector<Tree> &tempVec, int vertex) {
        if (vertex < 0 || tempVec.size() == 0)
            return NULL;

        BiggerTree *temp = new BiggerTree(tempVec[vertex].key);
        temp->left = depthFirstSearch(tempVec, tempVec[vertex].left);
        temp->right = depthFirstSearch(tempVec, tempVec[vertex].right);
        temp->height = max(this->showH(temp->left), this->showH(temp->right)) + 1;

        return temp;
    }

    BiggerTree *pushDFS(int key, BiggerTree *now) {
        if (now == NULL)
            return new BiggerTree(key);

        if (key > now->key)
            now->right = pushDFS(key, now->right);
        else
            now->left = pushDFS(key, now->left);

        return this->balancedTree(now);
    }

    BiggerTree *deleteDFS(int key, BiggerTree *now) {
        if (now == NULL)
            return NULL;

        if (key > now->key)
            now->right = deleteDFS(key, now->right);
        else if (key < now->key)
            now->left = deleteDFS(key, now->left);
        else {
            if (now->left == NULL && now->right == NULL)
                return NULL;
            else if (now->left == NULL) {
                now = now->right;
                return this->balancedTree(now);
            } else {
                BiggerTree *finded = lastRight(now->left);
                now->key = finded->key;
                now->left = deleteDFS(finded->key, now->left);
            }
        }

        return this->balancedTree(now);
    }

    BiggerTree *balancedTree(BiggerTree *myTree) {
        this->editH(myTree);
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

    BiggerTree *lastRight(BiggerTree *now) {
        if (now->right == NULL)
            return now;
        return lastRight(now->right);
    }

public:
    BiggerTree *Right(BiggerTree *myTree) {
        return this->rotation(myTree, false);
    }

    BiggerTree *Left(BiggerTree *myTree) {
        return this->rotation(myTree, true);
    }

    void buildTree(vector<Tree> &tempVec) {
        this->size = tempVec.size();
        this->root = this->depthFirstSearch(tempVec, 0);
    }

    void push(int key) {
        this->root = this->pushDFS(key, this->root);
        this->size++;
    }

    void remove(int key) {
        this->root = this->deleteDFS(key, this->root);
    }

    void showT() {
        queue<BiggerTree *> breadthFirstSearch;
        breadthFirstSearch.push(this->root);
        int line = 1;
        fout << (this->size - 1) << endl;

        while (!breadthFirstSearch.empty()) {
            BiggerTree *myTree = breadthFirstSearch.front();
            breadthFirstSearch.pop();

            if (myTree == NULL)
                break;
            int left = 0, right = 0;

            if (myTree->left != NULL) {
                breadthFirstSearch.push(myTree->left);
                left = ++line;
            }

            if (myTree->right != NULL) {
                breadthFirstSearch.push(myTree->right);
                right = ++line;
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

    AVLTree *AVL = new AVLTree();
    AVL->buildTree(mySecondTree);
    int tempClass;
    fin >> tempClass;

    AVL->remove(tempClass);
    AVL->showT();
}