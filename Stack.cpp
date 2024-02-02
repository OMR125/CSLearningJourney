#include <bits./stdc++.h>

using namespace std;

template<typename T>
struct node {
    T data;
    node *next = nullptr;

    node(T x) {
        data = x;
    }
};

template<typename T>
class Stack {
private:
    node<T> *head;
    int len = 0;
public:
    void push(T x) {
        len++;
        node<T> *new_data = new node(x);
        if (!empty())
            new_data->next = head;
        head = new_data;
    }

    bool pop() {
        if (empty()) {
            throw out_of_range("Stack is Empty!");
        }
        len--;
        node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    T top() {
        return !empty() ? head->data : throw out_of_range("Stack is Empty!");
    }

    bool empty() {
        return !len;
    }

    int size() {
        return len;
    }
};

int main() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (!s.empty()) {
        cout << s.top() << "\n";
        s.pop();
    }
    Stack<float> x;
    x.push((float) 1.5);
    x.push(2.5);
    cout << "\n";
    while (!x.empty()) {
        cout << x.top() << "\n";
        x.pop();
    }
}
