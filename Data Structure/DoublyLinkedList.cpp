#include <iostream>
#include <memory>

template <typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next = nullptr;
    std::shared_ptr<Node<T>> prev = nullptr;
    Node(T _data) : data(_data){};
    Node(T _data, std::shared_ptr<Node<T>>& _prev,
         std::shared_ptr<Node<T>>& _next) {
        data = _data;
        prev = _prev;
        next = _next;
    }
};

template <typename T>
class LinkedList {
   private:
    std::shared_ptr<Node<T>> head = nullptr;
    std::shared_ptr<Node<T>> tail = nullptr;
    int size = 0;

   private:
    std::shared_ptr<Node<T>> createNode(T nodeValue) {
        size++;
        return std::make_shared<Node<T>>(nodeValue);
    }

    void eraseNode(std::shared_ptr<Node<T>>& deleteNode) {
        if (deleteNode->prev != nullptr)
            deleteNode->prev->next = deleteNode->next;
        else
            head = head->next;

        if (deleteNode->next != nullptr)
            deleteNode->next->prev = deleteNode->prev;
        else
            tail = tail->prev;
        size--;
    }

    void insertBefore(T nodeValue, std::shared_ptr<Node<T>>& u) {
        auto add = std::make_shared<Node<T>>(nodeValue, u->prev, u);
        u->prev->next = add;
        u->prev = add;
        size++;
    }

   public:
    void push_back(T nodeValue) {
        auto add = createNode(nodeValue);
        if (empty()) {
            head = add;
            tail = add;
        } else {
            tail->next = add;
            add->prev = tail;
        }
        tail = add;
    }

    void push_front(T nodeValue) {
        auto add = createNode(nodeValue);
        if (empty()) {
            head = add;
            tail = add;
        } else {
            head->prev = add;
            add->next = head;
        }
        head = add;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("Linked List is Empty!");
        tail = tail->prev;
        tail->next = nullptr;
        size--;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("Linked List is Empty!");
        head = head->next;
        head->prev = nullptr;
        size--;
    }

    void eraseFirstOccurrence(T nodeValue) {
        auto iterNode = head;
        while (iterNode != nullptr) {
            if (iterNode->data == nodeValue) {
                eraseNode(iterNode);
                break;
            }
            iterNode = iterNode->next;
        }
    }

    void eraseLastOccurrence(T nodeValue) {
        auto iterNode = tail;
        while (iterNode != nullptr) {
            if (iterNode->data == nodeValue) {
                eraseNode(iterNode);
                break;
            }
            iterNode = iterNode->prev;
        }
    }

    void erase(T nodeValue) {
        auto left = head;
        auto right = tail;
        int cnt = (size + 1) / 2;
        while (cnt--) {
            auto next_l = left->next;
            auto prev_r = right->prev;
            if (left->data == nodeValue) {
                eraseNode(left);
            }
            if (right != left && right->data == nodeValue) {
                eraseNode(right);
            }
            left = next_l;
            right = prev_r;
        }
    }

    void insert(T nodeValue, int index) {
        if (index > size || index < 0)
            throw std::out_of_range("Index isn't Valid");
        if (index == size) push_back(nodeValue);
        if (index == 0) push_front(nodeValue);
        std::shared_ptr<Node<T>> iterNode;
        if (index < size / 2) {
            iterNode = head;
            while (index--) iterNode = iterNode->next;
        } else {
            index = size - index - 1;
            iterNode = tail;
            while (index--) iterNode = iterNode->prev;
        }
        insertBefore(nodeValue, iterNode);
    }

    bool empty() const { return head == nullptr; }

    int getSize() const { return size; }

    void print() const {
        if (empty()) {
            std::cout << "The Linked List is Empty :)";
            return;
        }
        auto iterNode = head;
        while (iterNode != nullptr) {
            std::cout << iterNode->data << " ";
            iterNode = iterNode->next;
        }
        std::cout << "\n";
    }
};

int main() {
    LinkedList<int> s;

    s.push_front(4);
    s.push_front(4);
    s.push_front(4);
    s.push_front(4);
    s.push_front(4);
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);

    s.print();
    s.erase(4);
    s.print();
}
