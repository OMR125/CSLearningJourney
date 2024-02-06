#include <bits./stdc++.h>

using namespace std;

const int MAXSIZE = 1e5;
// to get your parent index (i - 1) / 2
// to get your left child index 2 *  i+ 1
// to get your parent index 2 * i + 2 == left + 1

template <typename T, typename Compare = less<T>>
class PQ {
   private:
    int len = 0;
    vector<T> v;

   private:
    void go_up(int child) {
        int parent = (child - 1) / 2;
        while (Compare()(v[child], v[parent])) {
            swap(v[parent], v[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
    }
    void go_down(int parent) {
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        while (true) {
            int child;
            if (left >= len) break;
            if (!Compare()(v[parent], v[left]) || !Compare()(v[parent], v[right])) {
                child = !Compare()(v[right], v[left]) ? left : right;
                swap(v[parent], v[child]);
            } else
                break;
            parent = child;
            left = 2 * parent + 1;
            right = 2 * parent + 2;
        }
    }

   public:
    int size() { return len; }
    int empty() { return !len; }
    void push(T x) {
        if (len + 1 > MAXSIZE) {
            throw length_error("Size is too large");
        }
        v.push_back(x);
        go_up(len);
        len++;
    }
    void pop() {
        v[0] = v[len - 1];
        v.pop_back();
        len--;
        go_down(0);
    }
    T top() { return v[0]; }
    void remove(T x) { // useless function you won't need this in a priority queue goes to O(N)
        int i = find(v.begin(), v.end(), x) - v.begin();
        v[i] = v[len - 1];
        v.pop_back();
        go_down(i);
    }
    void clear() {
        while (!empty()) {
            pop();
        }
    }
};

int main() {
    PQ<int, greater<>> x;
    x.push(2);
    x.push(3);
    x.push(1);
    x.push(-4);
    x.push(9);
    x.push(9);
    x.push(-2);
    x.push(1);
    x.remove(9);
    while (!x.empty()) {
        cout << x.top() << " ";
        x.pop();
    }
}
