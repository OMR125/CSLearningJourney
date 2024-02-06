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
    vector<T> heap;

   private:
    void BubbleUp(int child) {
        int parent = (child - 1) / 2;
        while (Compare()(heap[child], heap[parent])) {
            swap(heap[parent], heap[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
    }
    void BubbleDown(int parent) {
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        while (true) {
            int child;
            if (left >= len) break;
            if (!Compare()(heap[parent], heap[left]) || !Compare()(heap[parent], heap[right])) {
                child = !Compare()(heap[right], heap[left]) ? left : right;
                swap(heap[parent], heap[child]);
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
        heap.push_back(x);
        BubbleUp(len);
        len++;
    }
    void pop() {
        heap[0] = heap[len - 1];
        heap.pop_back();
        len--;
        BubbleDown(0);
    }
    T top() { return heap[0]; }
    void remove(T x) {  // useless function you won't need this in a priority
                        // queue goes to O(N)
        int i = find(heap.begin(), heap.end(), x) - heap.begin();
        heap[i] = heap[len - 1];
        heap.pop_back();
        BubbleDown(i);
    }
    void clear() {
        while (!empty()) {
            pop();
        }
    }
};

int main() {
    PQ<int, less<>> x;
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
