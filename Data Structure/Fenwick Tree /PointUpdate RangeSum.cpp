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
        int n = arr.size();
        init(n);
        for (int i = 0; i < n; i++) update(i, arr[i]);
    }
    void update(int i, T value) {
        for (++i; i <= n; i += i & -i) Tree[i] += value;
    }
    T sum(int i) {
        T ans{};
        for (++i; i > 0; i -= i & -i) ans += Tree[i];
        return ans;
    }
    T range_sum(int l, int r) { return sum(r) - sum(l - 1); }
};
int main() {
    Fenwick<double> F;
    vector<double> arr(10);
    for (int i = 0; i < 10; i++) arr[i] = i;
    F.build(arr);
    // 1 2 3 4 5 6 7 8 9 10
    cout << F.range_sum(4, 7) << "\n";
}
