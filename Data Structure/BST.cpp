#include <iostream>
#include <memory>
#include <queue>

template <class T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> left = nullptr;
    std::shared_ptr<Node<T>> right = nullptr;

    // Added explicit keyword to the constructor of Node to prevent implicit conversions.
    explicit Node(T data) : data(data){};
};

template <class T>
class BST {
   private:
    std::shared_ptr<Node<T>> root = nullptr;

    std::shared_ptr<Node<T>> insertNode(std::shared_ptr<Node<T>> node, T data) {
        if (node == nullptr) {
            return std::make_shared<Node<T>>(data);
        }
        
        if (data >= node->data) {
            node->right = insertNode(node->right, data);
        } else {
            node->left = insertNode(node->left, data);
        }
        return node;
    }

    std::shared_ptr<Node<T>> removeNode(std::shared_ptr<Node<T>> node, T data) {
        if (node == nullptr) return nullptr;
        
        if (data > node->data) {
            node->right = removeNode(node->right, data);
        } else if (data < node->data) {
            node->left = removeNode(node->left, data);
        } else {
            if (node->right == nullptr) {
                return node->left;
            } else if (node->left == nullptr) {
                return node->right;
            } else {
                node->data = findMax(node->left)->data;
                node->left = removeNode(node->left, node->data);
            }
        }
        return node;
    }

    std::shared_ptr<Node<T>> searchNode(std::shared_ptr<Node<T>> node, T data) {
        if (node == nullptr || data == node->data) return node;
        if (data > node->data) {
            return searchNode(node->right, data);
        }
        return searchNode(node->left, data);
    }

   private:
    std::shared_ptr<Node<T>> findMax(std::shared_ptr<Node<T>> node) {
        if (node->right == nullptr) return node;
        return findMax(node->right);
    }

    std::shared_ptr<Node<T>> findMin(std::shared_ptr<Node<T>> node) {
        if (node->left == nullptr) return node;
        return findMin(node->left);
    }

    void printPreOrder(std::shared_ptr<Node<T>> node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    void printInOrder(std::shared_ptr<Node<T>> node) {
        if (node == nullptr) return;
        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }

    void printPostOrder(std::shared_ptr<Node<T>> node) {
        if (node == nullptr) return;
        printPostOrder(node->right);
        std::cout << node->data << " ";
        printPostOrder(node->left);
    }

   public:
    bool isEmpty() { return root == nullptr; }

    void insert(T data) { root = insertNode(root, data); }

    void remove(T data) { root = removeNode(root, data); }

    bool search(T data) { return searchNode(root, data) != nullptr; }

    T max() { return findMax(root)->data; }

    T min() { return findMin(root)->data; }

    void printInOrder() { printInOrder(root); }

    void printPreOrder() { printPreOrder(root); }

    void printPostOrder() { printPostOrder(root); }

    void BFS() {
        std::queue<std::shared_ptr<Node<T>>> q;
        q.push(root);
        while (!q.empty()) {
            int curSize = q.size();
            while(curSize--){
                auto node = q.front();
                std::cout << node->data << "\n";
                q.pop();
                if (node->right != nullptr) q.push(node->right);
                if (node->left != nullptr) q.push(node->left);
            }
        }
    }
};
int main() {
    BST<int> v;
    v.insert(6);
    v.insert(3);
    v.insert(7);
    v.insert(11);
    v.insert(-2);
    v.insert(9);
    v.insert(123);
    v.BFS();
}
