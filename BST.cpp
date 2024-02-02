#include <bits./stdc++.h>

using namespace std;

struct node {
    int data;
    node *left = nullptr;
    node *right = nullptr;

    node(int x) {
        data = x;
    }
};

class BST {
private:
    node *root;
    int len = 0;
public:
    node *insert(node *u, int x) {
        if (u == nullptr || empty())
            u = new node(x);
        else if (x >= u->data)
            u->right = insert(u->right, x);
        else
            u->left = insert(u->left, x);
        return u;
    }

    void insert(int x) {
        root = insert(root, x);
        len++;
    }

    void Increasing(node *u) {
        if (u == nullptr)
            return;
        Increasing(u->left);
        cout << u->data << " ";
        Increasing(u->right);
    }

    void Decreasing(node *u){
        if(u== nullptr){
            return;
        }
        Decreasing(u->right);
        cout << u->data << " ";
        Decreasing(u->left);
    }
    void print(bool check) {
        check ? Increasing(root) : Decreasing(root) ;
    }

    bool empty() {
        return !len;
    }

    int size() {
        return len;
    }
};

int main() {
    BST v;
    v.insert(6);
    v.insert(3);
    v.insert(7);
    v.insert(1);
    v.print(0);
    cout << "\n";
    v.print(1);
}
