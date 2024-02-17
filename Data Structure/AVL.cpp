#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int value;
    int balanceFactor = 0;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int _value) : value(_value){};
};

class AVLTree {
   private:
    Node* rootNode = nullptr;
    int treeSize = 0;

   private:
    void updateNode(Node* curNode) {
        int rightHeight = curNode->right != nullptr ? curNode->right->height : 0;
        int leftHeight = curNode->left != nullptr ? curNode->left->height : 0;
        curNode->height = 1 + max(rightHeight, leftHeight);
        curNode->balanceFactor = leftHeight - rightHeight;
    }

    Node* balanceNode(Node* curNode) {
        if (curNode->balanceFactor > 1) {  // Left Heavy
            if (curNode->left->balanceFactor >= 0) {
                return rotateRight(curNode);
            } else {
                curNode->left = rotateLeft(curNode->left);
                return rotateRight(curNode);
            }
        } else if (curNode->balanceFactor < -1) {  // Right Heavy
            if (curNode->right->balanceFactor <= 0) {
                return rotateLeft(curNode);
            } else {
                curNode->right = rotateRight(curNode->right);
                return rotateLeft(curNode);
            }
        }
        return curNode;
    }

    Node* insertNode(Node* curNode, int value) {
        if (curNode == nullptr) return new Node(value);
        if (value > curNode->value)
            curNode->right = insertNode(curNode->right, value);
        else
            curNode->left = insertNode(curNode->left, value);
        updateNode(curNode);
        return balanceNode(curNode);
    };

    Node* removeNode(Node* curNode, int value) {
        if (curNode == nullptr) return curNode;
        if (value > curNode->value)
            curNode->right = removeNode(curNode->right, value);
        else if (value < curNode->value)
            curNode->left = removeNode(curNode->left, value);
        else {
            if (curNode->right == nullptr) {
                Node* tempNode = curNode->left;
                delete curNode;
                return curNode->left;
            } else if (curNode->left == nullptr) {
                Node* tempNode = curNode->right;
                delete curNode;
                return curNode->right;
            } else {
                curNode->value = findMaxNode(curNode->left)->value;
                curNode->left = removeNode(curNode->left, curNode->value);
            }
        }
        updateNode(curNode);
        return balanceNode(curNode);
    };

    Node* searchNode(Node* curNode, int value) {
        if (curNode == nullptr || curNode->value == value) return curNode;
        if (value > curNode->value)
            return searchNode(curNode->right, value);
        else
            return searchNode(curNode->left, value);
    }

    Node* findMaxNode(Node* curNode) {
        if (curNode->right == nullptr) return curNode;
        return findMaxNode(curNode->right);
    }

    Node* findMinNode(Node* curNode) {
        if (curNode->left == nullptr) return curNode;
        return findMinNode(curNode->left);
    }

    Node* rotateLeft(Node* curNode) {
        Node* newParent = curNode->right;
        curNode->right = newParent->left;
        newParent->left = curNode;
        updateNode(curNode);
        updateNode(newParent);
        return newParent;
    }

    Node* rotateRight(Node* curNode) {
        Node* newParent = curNode->left;
        curNode->left = newParent->right;
        newParent->right = curNode;
        updateNode(curNode);
        updateNode(newParent);
        return newParent;
    }

    void inOrderTraversal(Node* curNode) {
        inOrderTraversal(curNode->left);
        cout << curNode->value << "\n";
        inOrderTraversal(curNode->right);
    }

    void preOrderTraversal(Node* curNode) {
        cout << curNode->value << "\n";
        preOrderTraversal(curNode->left);
        preOrderTraversal(curNode->right);
    }

    void postOrderTraversal(Node* curNode) {
        postOrderTraversal(curNode->right);
        cout << curNode->value << "\n";
        postOrderTraversal(curNode->left);
    }

   public:
    // operations on the tree
    bool insertNode(int value) {
        if (searchNode(value)) return false;
        rootNode = insertNode(rootNode, value);
        ++treeSize;
        return true;
    };

    bool removeNode(int value) {
        if (!searchNode(value)) return false;
        rootNode = removeNode(rootNode, value);
        --treeSize;
        return true;
    };

    bool searchNode(int value) { return searchNode(rootNode, value); };

    // size related stuff
    bool isEmpty() { return rootNode == nullptr; };

    int getSize() { return treeSize; }

    int getNodeDepth(int value) {
        Node* destinationNode = searchNode(rootNode, value);
        return destinationNode != nullptr ? destinationNode->height - 1 : -1;
    }

    // Queries
    int getMaxElement() { return findMaxNode(rootNode)->value; }
    int getMinElement() { return findMinNode(rootNode)->value; }

    // Traversals
    void BFS() {
        queue<Node*> q;
        q.push(rootNode);
        while (!q.empty()) {
            int curSize = q.size();
            while (curSize--) {
                auto node = q.front();
                cout << node->value << "\n";
                q.pop();
                if (node->right != nullptr) q.push(node->right);
                if (node->left != nullptr) q.push(node->left);
            }
            cout << "\n";
        }
    }
    void inOrderTraversal() { inOrderTraversal(rootNode); }

    void preOrderTraversal() { preOrderTraversal(rootNode); }

    void postOrderTraversal() { postOrderTraversal(rootNode); }
};
int main() {
    AVLTree x;
    x.insertNode(1);
    x.insertNode(2);
    x.insertNode(3);
    x.insertNode(4);
    x.insertNode(5);
    x.removeNode(3);
    x.insertNode(99);
    x.insertNode(-5);
    x.insertNode(72);
    x.insertNode(52);
    x.insertNode(0);
    x.insertNode(-3);
    x.removeNode(4);
    x.removeNode(3);
    x.BFS();
    cout << x.getSize() << "\n";
}
