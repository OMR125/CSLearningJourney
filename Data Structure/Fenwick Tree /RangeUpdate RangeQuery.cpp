#include <bits/stdc++.h>

using namespace std;

class Fenwick {
   private:
    int n;
    vector<int> Tree1, Tree2;

   public:
    Fenwick(int n = 0) { init(n); }
    void init(int _n) {
        n = _n + 1;
        Tree1.assign(n, 0);
        Tree2.assign(n, 0);
    }
    void build(vector<int> &arr) {
        init(arr.size());
        for (int i = 0; i < n; i++) range_update(i, i, arr[i]);
    }
    void update(vector<int> &arr, int i, int value) {
        for (++i; i < n; i += i & -i) arr[i] += value;
    }
    void range_update(int l, int r, int value) {
        update(Tree1, l, value);
        update(Tree1, r + 1, -value);
        update(Tree2, l, value * (l - 1));
        update(Tree2, r + 1, -value * r);
    }
    int sum(vector<int> &arr, int i) {
        int ans = 0;
        for (++i; i > 0; i -= i & -i) ans += arr[i];
        return ans;
    }
    int prefix_sum(int i) { return sum(Tree1, i) * i - sum(Tree2, i); }
    int range_sum(int l, int r) { return prefix_sum(r) - prefix_sum(l - 1); }
    int Query(int i) { return prefix_sum(i) - prefix_sum(i - 1); }
};
int main() {
    Fenwick F;
    vector<int> arr(10);
    for (int i = 0; i < 10; i++) arr[i] = i + 1;
    F.build(arr);
    F.range_update(3, 5, 6);
    F.range_update(1, 7, 3);
    F.range_update(8, 9, -2);
    for (int i = 0; i < 10; i++) cout << F.Query(i) << " \n"[i == 9];
    for (int i = 0; i < 10; i++) cout << F.prefix_sum(i) << " \n"[i == 9];
    for (int i = 0; i < 10; i++) cout << F.range_sum(i, 9) << " \n"[i == 9];
}
