#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Fenwick {
   private:
    int n;
    vector<T> Tree;

   public:
    Fenwick(int n = 0) { init(n); }
    void init(int _n) {
        n = _n + 1;
        Tree.assign(n, T{});
    }
    void build(vector<T> &arr) {
        init(arr.size());
        for (int i = 0; i < n; i++) range_update(i, i, arr[i]);
    }
    void update(int i, T value) {
        for (++i; i < n; i += i & -i) Tree[i] += value;
    }
    void range_update(int l, int r, T value) {
        update(l, value);
        update(r + 1, -value);
    }
    T sum(int i) {
        T ans{};
        for (++i; i > 0; i -= i & -i) ans += Tree[i];
        return ans;
    }
    T Query(int i) { return sum(i); }
};
int main() {
    Fenwick<int> F;
    vector<int> arr(10);
    for (int i = 0; i < 10; i++) arr[i] = i + 1;
    F.build(arr);
    F.range_update(3, 5, 6);
    F.range_update(1, 7, 3);
    F.range_update(8, 9, -2);
    for (int i = 0; i < 10; i++) cout << F.Query(i) << " ";
}
