#include <bits./stdc++.h>

using namespace std;

struct node {
    int data;
    node *next = nullptr;

    node(int x) {
        data = x;
    }
};

class Stack {
private:
    node *head;
    int len = 0;
public:
    void push(int x) {
        len++;
        node *new_data = new node(x);
        if (!empty())
            new_data->next = head;
        head = new_data;
    }

    bool pop() {
        if (empty()) {
            throw out_of_range("Stack is Empty!");
        }
        len--;
        node *temp = head;
        head = head->next;
        delete temp;
    }

    int top() {
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
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (!s.empty()) {
        cout << s.top() << "\n";
        s.pop();
    }
    s.push(2);
    s.push(3);
    s.pop();
    cout << s.top();
    cout << s.pop();
    s.pop();
}
