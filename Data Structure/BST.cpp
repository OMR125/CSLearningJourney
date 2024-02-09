#include <bits./stdc++.h>
using namespace std;
template <class T>
struct node {
    T data;
    node<T>* left = nullptr;
    node<T>* right = nullptr;
    node<T>(T _data) : data(_data){};
};
template <class T>
class BST {
   private:
    node<T>* root = nullptr;

   private:
    node<T>* insert(node<T>* u, T x) {
        if (u == nullptr || empty()) {
            u = new node<T>(x);
        } else if (x >= u->data) {
            u->right = insert(u->right, x);
        } else {
            u->left = insert(u->left, x);
        }
        return u;
    }
    node<T>* remove(node<T>* u, T x) {
        if (u == nullptr) return nullptr;
        if (x > u->data)
            u->right = remove(u->right, x);
        else if (x < u->data)
            u->left = remove(u->left, x);
        else {
            if (u->right == nullptr) {
                node<T>* temp = u->left;
                delete u;
                return temp;
            } else if (u->left == nullptr) {
                node<T>* temp = u->right;
                delete u;
                return temp;
            } else {
                u->data = max(u->left)->data;
                u->left = remove(u->left, u->data);
            }
        }
        return u;
    }
    node<T>* search(node<T>* u, T x) {
        if (x == u->data) return u;
        if (u == nullptr) return nullptr;
        if (x > u->data) return search(u->right, x);
        return search(u->left, x);
    }
    node<T>* max(node<T>* u) {
        if (u->right == nullptr) return u;
        return max(u->right);
    }
    void preOrder(node<T>* u) {
        if (u == nullptr) return;
        cout << u->data << " ";
        preOrder(u->left);
        preOrder(u->right);
    }
    void inOrder(node<T>* u) {
        if (u == nullptr) return;
        inOrder(u->left);
        cout << u->data << " ";
        inOrder(u->right);
    }
    void postOrder(node<T>* u) {
        if (u == nullptr) return;
        postOrder(u->right);
        cout << u->data << " ";
        postOrder(u->left);
    }

   public:
    bool empty() { return root == nullptr; }
    void insert(T x) { root = insert(root, x); }
    void remove(T x) { remove(root, x); }
    bool search(T x) { return search(root, x); }
    void preOrder() { preOrder(root); }
};
int main() {
  
}
