#include <bits./stdc++.h>

using namespace std;

template<typename T>
struct node {
    T data;
    node *left = nullptr;
    node *right = nullptr;

    node(T x) {
        data = x;
    }
};

template<typename T>
class BST {
private:
    node<T> *root;
    int len = 0;
private:
    node<T> *insert(node<T> *u, T x) {
        if (u == nullptr || empty())
            u = new node(x);
        else if (x >= u->data)
            u->right = insert(u->right, x);
        else
            u->left = insert(u->left, x);
        return u;
    }

    node<T> *max(node<T> *u) {
        if (u->right == nullptr)
            return u;
        max(u->right);
    }

    node<T> *search(node<T> *u, T x) {
        if (u == nullptr)
            return nullptr;
        if (x == u->data)
            return u;
        if (x > u->data)
            return search(u->right, x);
        return search(u->left, x);
    }

    node<T> *remove(node<T> *u, T x) {
        if (u == nullptr)
            return nullptr;
        if (x > u->data) {
            u->right = remove(u->right, x);
        } else if (x < u->data) {
            u->left = remove(u->left, x);
        } else {
            if (u->left == nullptr) {
                node<T> *temp = u->right;
                delete u;
                return temp;
            } else if (u->right == nullptr) {
                node<T> *temp = u->left;
                delete u;
                return temp;
            } else {
                node<T> *mx = max(u->left);
                u->data = mx->data;
                u->left = remove(u->left, mx->data);
            }
        }
        return u;
    }

    void print(node<T> *u) {
        if (u == nullptr)
            return;
        cout << u->data << " ";
        print(u->left);
        print(u->right);
    }

public:


    void insert(T x) {
        root = insert(root, x);
        len++;
    }


    bool search(T x) {
        return search(root, x);
    }


    void remove(T x) {
        if (empty())
            return;
        remove(root, x);
        len--;
    }

    void print() {
        print(root);
    }

    bool empty() {
        return !len;
    }

    int size() {
        return len;
    }
};

int main() {
    BST<int> v;
    for (int i = 0; i < 10; i++) {
        int x;
        cin >> x;
        v.insert(x);
    }
    v.print();
    cout << "\n";
    v.remove(9);
    v.print();
}
