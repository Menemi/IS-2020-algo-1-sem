#include <fstream>
#include <string>

using namespace std;

struct tree {
    int value;
    tree *l;
    tree *r;
};

bool Search(tree *root, int temp) {
    if (root == NULL) return false;
    if (root->value == temp) return true;
    if (temp < root->value) return Search(root->l, temp);
    else return Search(root->r, temp);
}

tree *Insert(tree *&root, int temp) {
    if (root == NULL) {
        root = new tree;
        root->value = temp;
        root->l = root->r = NULL;
    } else if (root->value > temp) Insert(root->l, temp);
    else if (root->value < temp) Insert(root->r, temp);
    return root;
}

tree *Next(tree *&root, int temp) {
    tree *current = root;
    tree *successor = NULL;

    while (current != NULL) {
        if (current->value > temp) {
            successor = current;
            current = current->l;
        } else current = current->r;
    }
    return successor;
}

tree *Previous(tree *&root, int temp) {
    tree *current = root;
    tree *successor = NULL;

    while (current != NULL) {
        if (current->value < temp) {
            successor = current;
            current = current->r;
        } else current = current->l;
    }
    return successor;
}

tree *tMin(tree *&temp) {
    if (temp->l == NULL) return temp;
    return tMin(temp->l);
}

tree *tMax(tree *&temp) {
    if (temp->r == NULL) return temp;
    return tMax(temp->l);
}

tree *Delete(tree *&root, int temp) {
    if (root == NULL) return root;

    if (temp < root->value) root->l = Delete(root->l, temp);
    else if (temp > root->value) root->r = Delete(root->r, temp);
    else if (root->l != NULL && root->r != NULL) {
        root->value = tMin(root->r)->value;
        root->r = Delete(root->r, root->value);
    } else {
        if (root->l != NULL) root = root->l;
        else root = root->r;
    }

    return root;
}

int main() {
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");
    /*ifstream fin("in.txt");
    ofstream fout("out.txt");*/

    tree *myTree = NULL;
    tree *temp;
    string command;
    int value;

    while (fin >> command) {
        fin >> value;

        if (command == "insert") Insert(myTree, value);
        else if (command == "exists") {
            if (Search(myTree, value)) fout << "true\n";
            else fout << "false\n";
        } else if (command == "next") {
            temp = Next(myTree, value);
            if (temp == NULL) fout << "none\n";
            else fout << temp->value << "\n";
        } else if (command == "prev") {
            temp = Previous(myTree, value);
            if (temp == NULL) fout << "none\n";
            else fout << temp->value << "\n";
        } else if (command == "delete") Delete(myTree, value);
    }
}