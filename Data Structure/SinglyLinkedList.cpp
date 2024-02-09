#include <bits/stdc++.h>

template <typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next = nullptr;

    Node(T _data) : data(_data) {}

};

template <typename T>
class LinkedList {
   private:
    std::shared_ptr<Node<T>> head = nullptr;
    int sz = 0;

   public:
    void push_front(T x) {
        sz++;
        auto add = std::make_shared<Node<T>>(x);
        if (!empty()) add->next = head;
        head = add;
    }

    void push_back(T x) {
        sz++;
        auto add = std::make_shared<Node<T>>(x);
        if (empty()) {
            head = add;
            return;
        }
        auto temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = add;
    }

    void insert(T x, int idx) {
        if (idx >= sz)
            throw std::out_of_range("Index bigger than the Linked List!");
        auto add = std::make_shared<Node<T>>(x);
        sz++;
        if (empty()) {
            head = add;
            return;
        }
        auto temp = head;
        while (--idx) temp = temp->next;
        add->next = temp->next;
        temp->next = add;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("Linked List is Empty!");
        head = head->next;
        sz--;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("Linked List is empty!");
        if (sz == 1) {
            pop_front();
            return;
        }
        auto temp = head;
        while (temp->next->next != nullptr) temp = temp->next;
        temp->next = nullptr;
        sz--;
    }

    void erase(T x) {
        if (empty()) throw std::out_of_range("Linked List is empty!");
        if (head->data == x) {
            pop_front();
            return;
        }
        auto temp = head;
        while (temp->next != nullptr && temp->next->data != x) {
            temp = temp->next;
        }
        if (temp->next == nullptr) return;
        temp->next = temp->next->next;
        sz--;
    }

    void print() const {
        auto temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }

    bool empty() const { return head == nullptr; }
    int size() const { return sz; }
};

int main() {
    LinkedList<int> s;
    // 9 8 6 3 10 1 11 2 4 7
    s.push_back(1);
    s.push_back(2);
    s.push_front(3);
    s.push_back(4);
    s.push_front(6);
    s.insert(11, 3);
    s.push_back(7);
    s.push_front(8);
    s.push_front(9);
    s.insert(10, 4);
    s.print();
    s.erase(10);
    s.print();
    s.erase(7);
    s.print();
    s.erase(9);
    s.print();
    std::cout << s.size() << "\n";
}
