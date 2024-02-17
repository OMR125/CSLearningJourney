#include <iostream>
#include <memory>
#include <queue>

using namespace std;

struct node {
    int data;
    int bf = 0;
    int depth = 1;
    node* left = nullptr;
    node* right = nullptr;
    node(int _data) : data(_data){};
};

class AVL {
   private:
    node* root = nullptr;
    int len = 0;

   private:
    node* insert(node* u, int data) {
        if (u == nullptr) return new node(data);
        if (data > u->data)
            u->right = insert(u->right, data);
        else
            u->left = insert(u->left, data);
        update(u);
        return balance(u);
    };
    node* remove(node* u, int data) {
        if (u == nullptr) return u;
        if (data > u->data)
            u->right = remove(u->right, data);
        else if (data < u->data)
            u->left = remove(u->left, data);
        else {
            if (u->right == nullptr) {
                return u->left;
            } else if (u->left == nullptr) {
                return u->right;
            } else {
                u->data = FindMax(u->left)->data;
                u->left = remove(u->left, u->data);

                // also valid method
                // u->data = min(u->right)->data;
                // u->right = remove(u->right,u->data);
            }
        }
        update(u);
        return balance(u);
    };
    node* balance(node* u) {
        if (u->bf > 1) {  // left heavy
            if (u->left->bf >= 0) {
                return R(u);
            } else {
                u->left = L(u->left);
                return R(u);
            }
        } else if (u->bf < -1) {  // right heavy
            if (u->right->bf <= 0) {
                return L(u);
            } else {
                u->right = R(u->right);
                return L(u);
            }
        }
        return u;
    }
    node* search(node* u, int data) {
        if (u == nullptr || u->data == data) return u;
        if (data > u->data)
            return search(u->right, data);
        else
            return search(u->left, data);
    }
    node* FindMax(node* u) {
        if (u->right == nullptr) return u;
        return FindMax(u->right);
    }
    node* FindMin(node* u) {
        if (u->left == nullptr) return u;
        return FindMin(u->left);
    }
    node* L(node* u) {
        node* newparent = u->right;
        u->right = newparent->left;
        newparent->left = u;
        update(u);
        update(newparent);
        return newparent;
    }
    node* R(node* u) {
        node* newparent = u->left;
        u->left = newparent->right;
        newparent->right = u;
        update(u);
        update(newparent);
        return newparent;
    }
    void update(node* u) {
        int op1 = u->right != nullptr ? u->right->depth : 0;
        int op2 = u->left != nullptr ? u->left->depth : 0;
        u->depth = 1 + max(op1, op2);
        u->bf = op2 - op1;
    }
    void* inOrder(node* u) {
        inOrder(u->left);
        cout << u->data << "\n";
        inOrder(u->right);
    }
    void* preOrder(node* u) {
        cout << u->data << "\n";
        preOrder(u->left);
        preOrder(u->right);
    }
    void* postOrder(node* u) {
        postOrder(u->right);
        cout << u->data << "\n";
        postOrder(u->left);
    }

   public:
    bool insert(int data) {
        if (search(data)) return false;
        root = insert(root, data);
        len++;
        return true;
    };
    void remove(int data) { root = remove(root, data); };
    bool search(int data) { return search(root, data); };
    bool empty() { return root == nullptr; };
    int size() { return len; }
    int depth(int data) {
        node* distination = search(root, data);
        return distination != nullptr ? distination->depth - 1 : -1;
    }
    void BFS() {
        queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto node = q.front();
                cout << node->data << "\n";
                q.pop();
                if (node->right != nullptr) q.push(node->right);
                if (node->left != nullptr) q.push(node->left);
            }
            cout << "\n";
        }
    }
    int max_element() { return FindMax(root)->data; }
    int min_element() { return FindMin(root)->data; }
    void inOrder() { inOrder(root); }
    void preOrder() { preOrder(root); }
    void postOrder() { postOrder(root); }
};
int main() {
    AVL x;
    x.insert(1);
    x.insert(2);
    x.insert(3);
    x.insert(4);
    x.insert(5);
    x.remove(3);
    x.insert(99);
    x.insert(-5);
    x.insert(72);
    x.insert(52);
    x.insert(0);
    x.insert(-3);
    x.remove(4);
    x.remove(3);
    x.BFS();
}
