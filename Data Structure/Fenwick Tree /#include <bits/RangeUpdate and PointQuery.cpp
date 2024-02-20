#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Fenwick {
   private:
    int n;
    vector<int> v;

   public:
    Fenwick(int n = 0) { init(n); }
    void init(int _n) {
        n = _n + 1;
        v.assign(n, T{});
    }
    void build(vector<int> &arr) {
        int n = arr.size();
        init(n);
        for (int i = 0; i < n; i++) range_update(i, i, arr[i]);
    }
    void add(int i, T x) {
        for (++i; i <= n; i += i & -i) v[i] += x;
    }
    void range_update(int l, int r, int x) {
        add(l, x);
        add(r + 1, -x);
    }
    T sum(int i) {
        T ans{};
        for (++i; i > 0; i -= i & -i) ans += v[i];
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
