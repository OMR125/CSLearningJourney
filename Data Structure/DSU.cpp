#include <bits./stdc++.h>

using namespace std;
class DSU {
   private:
    vector<int> parent, sz;
    int sets, _size;

   public:
    DSU(int n) {
        parent = sz = vector<int>(n, 1);
        iota(parent.begin(), parent.end(), 0);
        sets = _size = n;
    }
    int Find(int x) {
        /* recursive way is more elegant and easier to understand but when the
        DSU is very large there's a potential Stack Overflow
        if (parent[x] == x) return x;
        return parent[x] = Find(parent[x]); */

        // iterative method avoids the Stack Overflow problem and it handles
        // larger data sets and deeper trees better.
        while (x != parent[x]) x = parent[x] = parent[parent[x]];
        return x;
    }
    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        if (sz[x] < sz[y])
            swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
        sets--;
    }
    int NumOfComponents() { return sets; }
    int ComponentSize(int x) { return sz[Find(x)]; }
    int size() { return _size; }
};

int main() {
    DSU dsu(5);
    dsu.Union(0, 1);
    dsu.Union(1, 2);
    dsu.Union(3, 4);
    cout << dsu.Find(4) << "\n";
    dsu.Union(4, 1);
    cout << dsu.Find(4) << " " << dsu.Find(2) << "\n";
}
