#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int value;
    int balanceFactor = 0;
    int height = 1;
    Node* leftChild = nullptr;
    Node* rightChild = nullptr;
    Node(int _value) : value(_value){};
};

class AVLTree {
   private:
    Node* rootNode = nullptr;
    int treeSize = 0;

   private:
    void updateNode(Node* currentNode) {
        int rightChildHeight = currentNode->rightChild != nullptr ? currentNode->rightChild->height : 0;
        int leftChildHeight = currentNode->leftChild != nullptr ? currentNode->leftChild->height : 0;
        currentNode->height = 1 + max(rightChildHeight, leftChildHeight);
        currentNode->balanceFactor = leftChildHeight - rightChildHeight;
    }

    Node* balanceNode(Node* currentNode) {
        if (currentNode->balanceFactor > 1) { // Left Heavy
            if (currentNode->leftChild->balanceFactor >= 0) {
                return rotateRight(currentNode); 
            } else {
                currentNode->leftChild = rotateLeft(currentNode->leftChild);
                return rotateRight(currentNode);
            }
        } else if (currentNode->balanceFactor < -1) { // Right Heavy
            if (currentNode->rightChild->balanceFactor <= 0) {
                return rotateLeft(currentNode);
            } else {
                currentNode->rightChild = rotateRight(currentNode->rightChild);
                return rotateLeft(currentNode);
            }
        }
        return currentNode;
    }

    Node* insertNode(Node* currentNode, int value) {
        if (currentNode == nullptr) return new Node(value);
        if (value > currentNode->value)
            currentNode->rightChild =
                insertNode(currentNode->rightChild, value);
        else
            currentNode->leftChild = insertNode(currentNode->leftChild, value);
        updateNode(currentNode);
        return balanceNode(currentNode);
    };

    Node* removeNode(Node* currentNode, int value) {
        if (currentNode == nullptr) return currentNode;
        if (value > currentNode->value)
            currentNode->rightChild =
                removeNode(currentNode->rightChild, value);
        else if (value < currentNode->value)
            currentNode->leftChild = removeNode(currentNode->leftChild, value);
        else {
            if (currentNode->rightChild == nullptr) {
                tempNode = currentNode->leftChild;
                delete currentNode;
                return currentNode->leftChild;
            } else if (currentNode->leftChild == nullptr) {
                tempNode = currentNode->rightChild;
                delete currentNode;
                return currentNode->rightChild;
            } else {
                currentNode->value = findMaxNode(currentNode->leftChild)->value;
                currentNode->leftChild =
                    removeNode(currentNode->leftChild, currentNode->value);
            }
        }
        updateNode(currentNode);
        return balanceNode(currentNode);
    };

    Node* searchNode(Node* currentNode, int value) {
        if (currentNode == nullptr || currentNode->value == value)
            return currentNode;
        if (value > currentNode->value)
            return searchNode(currentNode->rightChild, value);
        else
            return searchNode(currentNode->leftChild, value);
    }

    Node* findMaxNode(Node* currentNode) {
        if (currentNode->rightChild == nullptr) return currentNode;
        return findMaxNode(currentNode->rightChild);
    }

    Node* findMinNode(Node* currentNode) {
        if (currentNode->leftChild == nullptr) return currentNode;
        return findMinNode(currentNode->leftChild);
    }

    Node* rotateLeft(Node* currentNode) {
        Node* newParentNode = currentNode->rightChild;
        currentNode->rightChild = newParentNode->leftChild;
        newParentNode->leftChild = currentNode;
        updateNode(currentNode);
        updateNode(newParentNode);
        return newParentNode;
    }

    Node* rotateRight(Node* currentNode) {
        Node* newParentNode = currentNode->leftChild;
        currentNode->leftChild = newParentNode->rightChild;
        newParentNode->rightChild = currentNode;
        updateNode(currentNode);
        updateNode(newParentNode);
        return newParentNode;
    }

    void inOrderTraversal(Node* currentNode) {
        inOrderTraversal(currentNode->leftChild);
        cout << currentNode->value << "\n";
        inOrderTraversal(currentNode->rightChild);
    }

    void preOrderTraversal(Node* currentNode) {
        cout << currentNode->value << "\n";
        preOrderTraversal(currentNode->leftChild);
        preOrderTraversal(currentNode->rightChild);
    }

    void postOrderTraversal(Node* currentNode) {
        postOrderTraversal(currentNode->rightChild);
        cout << currentNode->value << "\n";
        postOrderTraversal(currentNode->leftChild);
    }

   public:
    // operations on the tree
    bool insertNode(int value) {
        if (searchNode(value)) return false;
        rootNode = insertNode(rootNode, value);
        treeSize++;
        return true;
    };

    void removeNode(int value) { rootNode = removeNode(rootNode, value); };

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
                if (node->rightChild != nullptr) q.push(node->rightChild);
                if (node->leftChild != nullptr) q.push(node->leftChild);
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
}
