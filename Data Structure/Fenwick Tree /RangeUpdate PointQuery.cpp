#include <bits/stdc++.h>

using namespace std;

class Fenwick {
   private:
    int n;
    vector<int> Tree;

   public:
    Fenwick(int n = 0) { init(n); }
    void init(int _n) {
        n = _n + 1;
        Tree.assign(n, 0);
    }
    void build(vector<int> &arr) {
        int n = arr.size();
        init(n);
        for (int i = 0; i < n; i++) range_update(i, i, arr[i]);
    }
    void add(int i, int value) {
        for (++i; i <= n; i += i & -i) Tree[i] += value;
    }
    void range_update(int l, int r, int value) {
        add(l, value);
        add(r + 1, -value);
    }
    int sum(int i) {
        int ans = 0;
        for (++i; i > 0; i -= i & -i) ans += Tree[i];
        return ans;
    }
    int Query(int i) { return sum(i); }
};
int main() {
    Fenwick F;
    vector<int> arr(10);
    for (int i = 0; i < 10; i++) arr[i] = i + 1;
    F.build(arr);
    F.range_update(3, 5, 6);
    F.range_update(1, 7, 3);
    F.range_update(8, 9, -2);
    for (int i = 0; i < 10; i++) cout << F.Query(i) << " ";
}
