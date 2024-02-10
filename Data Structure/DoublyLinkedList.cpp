#include <bits/stdc++.h>

using namespace std;

struct node {
    int data;
    shared_ptr<node> next = nullptr;
    shared_ptr<node> prev = nullptr;
    node(int _data) : data(_data){};
    node(int _data, shared_ptr<node>& _prev, shared_ptr<node>& _next) {
        data = _data;
        prev = _prev;
        next = _next;
    }
};

class LinkedList {
   private:
    shared_ptr<node> head = nullptr;
    shared_ptr<node> tail = nullptr;
    int sz = 0;

   private:
    void erasenode(shared_ptr<node>& del) {
        if (del->prev != nullptr)
            del->prev->next = del->next;
        else
            head = head->next;

        if (del->next != nullptr)
            del->next->prev = del->prev;
        else
            tail = tail->prev;
        sz--;
    }
    void insertbefore(int x, shared_ptr<node>& u) {
        auto add = make_shared<node>(x, u->prev, u);
        u->prev->next = add;
        u->prev = add;
        sz++;
    }

   public:
    void push_back(int x) {
        sz++;
        auto add = make_shared<node>(x);
        if (empty()) {
            head = add;
            tail = add;
        } else {
            tail->next = add;
            add->prev = tail;
        }
        tail = add;
    }
    void push_front(int x) {
        sz++;
        auto add = make_shared<node>(x);
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
        if (empty()) throw out_of_range("Linked List is Empty!");
        tail = tail->prev;
        tail->next = nullptr;
        sz--;
    }
    void pop_front() {
        if (empty()) throw out_of_range("Linked List is Empty!");
        head = head->next;
        head->prev = nullptr;
        sz--;
    }
    void eraseFirstOccurrence(int x) {
        auto temp = head;
        while (temp != nullptr) {
            if (temp->data == x) erasenode(temp);
            temp = temp->next;
        }
    }
    void eraseLastOccurrence(int x) {
        auto temp = tail;
        while (temp != nullptr) {
            if (temp->data == x) erasenode(temp);
            temp = temp->prev;
        }
    }

    void erase(int x) {
        auto l = head;
        auto r = tail;
        int cnt = (sz + 1) / 2;
        while (cnt--) {
            auto next_l = l->next;
            auto prev_r = r->prev;
            if (l->data == x) erasenode(l);
            if (r->data == x) erasenode(r);
            l = next_l;
            r = prev_r;
        }
    }

    void insert(int x, int idx) {
        if (idx > sz)
            throw out_of_range(
                "Index Bigger Than The Size of The Linked List!");
        if (idx == sz) push_back(x);
        if (idx == 0) push_front(x);
        shared_ptr<node> temp;
        if (idx < sz / 2) {
            temp = head;
            while (idx--) {
                temp = temp->next;
            }
        } else {
            idx = sz - idx - 1;
            temp = tail;
            while (idx--) {
                temp = temp->prev;
            }
        }
        insertbefore(x, temp);
    }
    bool empty() { return head == nullptr; }
    int size() { return sz; }
    void print() {
        if (empty()) {
            cout << "The Linked List is Empty :)";
            return;
        }
        auto temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

int main() {
    LinkedList s;
    s.push_front(4);
    s.push_front(4);
    s.push_front(4);
    s.push_front(4);
    s.push_back(4);
    s.push_back(4);
    s.erase(2);
    s.erase(4);
    s.print();
}
