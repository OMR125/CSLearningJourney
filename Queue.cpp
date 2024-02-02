#include <bits./stdc++.h>

using namespace std;

struct node {
    int data = 0;
    node *next = nullptr;
    node *prev = nullptr;
    node(int _data, node *_next, node* _prev) {
        data = _data;
        next = _next;
        prev = _prev;
    }
};

class Queue {
private:
    node *head;
    node *tail;
    int len = 0;
public:
    void push(int x){
        node* new_data = new node(x, nullptr, nullptr);
        if(empty()){
            tail = new_data;
        }else {
            head->prev = new_data;
            new_data->next = head;
        }
        head = new_data;
        len++;
    }
    bool pop(){
        if(empty())
            return false;
        len--;
        node* temp = tail;
        tail->next= nullptr;
        tail = tail->prev;
        delete temp;
        return true;
    }
    bool empty(){
        return !len;
    }
    int top(){
        return !empty() ? tail->data : throw out_of_range("NIGGER");
    }
    bool find(int x){
        node*temp = tail;
        while(temp!= nullptr){
            if(temp->data==x){
                return true;
            }
            temp=temp->prev;
        }
        return false;
    }
    void clear(){
        while(!empty()){
            pop();
        }
    }
};

int main() {
    Queue x;
    x.push(1);
    x.push(2);
    x.push(4);
    x.push(88);
    x.clear();
    x.push(33);
    x.push(23);
    cout << x.top() << "\n";
    x.pop();
    cout << x.top() << "\n";
    x.pop();
    x.pop();

}
