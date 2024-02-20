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
        for (int i = 0; i < n; i++) update(i, arr[i]);
    }
    void update(int i, T x) {
        for (++i; i <= n; i += i & -i) v[i] += x;
    }
    T sum(int i) {
        T ans{};
        for (++i; i > 0; i -= i & -i) ans += v[i];
        return ans;
    }
    T range_sum(int l, int r) { return sum(r) - sum(l - 1); }
};
int main() {
    Fenwick<int> F;
    vector<int> arr(10);
    for (int i = 0; i < 10; i++) arr[i] = i + 1;
    F.build(arr);
    // 1 2 3 4 5 6 7 8 9 10
    cout << F.range_sum(4, 7) << "\n";
}
