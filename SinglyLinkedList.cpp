#include <bits./stdc++.h>

using namespace std;
struct node {
    int data;
    node* next = nullptr;
    node(int _data) { data = _data; }
};

class LinkedList {
   private:
    node* head = nullptr;
    int sz = 0;

   public:
    void push_front(int x) {
        sz++;

        node* add = new node(x);
        if (!empty()) add->next = head;
        head = add;
    }
    void push_back(int x) {  // complexity fixed in Doubly Linked List
        sz++;
        node* add = new node(x);
        if (empty()) {
            head = add;
            return;
        }
        node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = add;
    }
    void insert(int x,
                int idx) {  // complexity slightly fixed in Doubly Linked List
        if (idx >= sz) throw out_of_range("Index bigger than the Linked List!");
        sz++;
        node* add = new node(x);
        if (empty()) {
            head = add;
            return;
        }
        node* temp = head;
        while (--idx) temp = temp->next;
        add->next = temp->next;
        temp->next = add;
    }
    void pop_front() {
        if (empty()) throw out_of_range("Linked List is Empty!");
        sz--;
        node* temp = head;
        head = head->next;
        delete temp;
    }
    void pop_back() {  // complexity fixed in Doubly Linked List
        if (empty()) throw out_of_range("Linked List is empty!");
        if (sz == 1) pop_front();
        node* temp = head;
        int idx = sz - 1;
        while (--idx) temp = temp->next;
        node* del = temp->next;
        temp->next = nullptr;
        delete del;
        sz--;
    }
    void erase(int x) {
        if (empty()) throw out_of_range("Linked List is empty!");
        if (head->data == x) {
            pop_front();
            return;
        }
        node* temp = head;
        while (temp != nullptr && temp->next->data != x) {
            temp = temp->next;
        }
        if (temp == nullptr) return;
        node* del = temp->next;
        temp->next = del->next;
        delete del;
        sz--;
    }

    void print() {
        node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    bool empty() { return head == nullptr; }
    bool size() { return sz; }
};
int main() {
    LinkedList s;
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
}
