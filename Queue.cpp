#include <bits./stdc++.h>

using namespace std;

template<typename T>
struct node {
    T data;
    node<T> *next = nullptr;
    node<T> *prev = nullptr;

    node(T _data) {
        data = _data;
    }
};

template<typename T>
class Queue {
private:
    node<T> *head;
    node<T> *tail;
    int len = 0;
public:
    void push(T x) {
        node<T> *new_data = new node(x);
        if (empty()) {
            tail = new_data;
        } else {
            head->prev = new_data;
            new_data->next = head;
        }
        head = new_data;
        len++;
    }

    void pop() {
        if (empty())
            throw out_of_range("Queue is Empty");
        len--;
        node<T> *temp = tail;
        tail->next = nullptr;
        tail = tail->prev;
        delete temp;
    }

    bool empty() {
        return !len;
    }

    T top() {
        return !empty() ? tail->data : throw out_of_range("Queue is Empty");
    }

    bool find(int x) {
        node<T> *temp = tail;
        while (temp != nullptr) {
            if (temp->data == x) {
                return true;
            }
            temp = temp->prev;
        }
        return false;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }
};

int main() {
    Queue<float> x;
    x.push(1.5);
    x.push(2);
    x.push(4);
    x.push(88);
    x.clear();
    x.push(33.6969);
    x.push(23);
    cout << x.top() << "\n";
    x.pop();
    cout << x.top() << "\n";
    x.pop();
    x.pop();

}
