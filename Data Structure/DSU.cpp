#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
class DisjointSetUnion {
   private:
    vector<int> parentVector, sizeVector;
    int numberOfSets, totalSize;

   public:
    DisjointSetUnion(int n) {
        parentVector = sizeVector = vector<int>(n, 1);
        iota(parentVector.begin(), parentVector.end(), 0);
        numberOfSets = totalSize = n;
    }
    int findSet(int x) {
        /* recursive way is more elegant and easier to understand but when the
        DSU is very large there's a potential Stack Overflow
        if (parent[x] == x) return x;
        return parent[x] = Find(parent[x]);*/

        // iterative method avoids the Stack Overflow problem and it handles
        // larger data sets and deeper trees better.

        while (x != parentVector[x])
            x = parentVector[x] = parentVector[parentVector[x]];
        return x;
    }
    void unionSets(int x, int y) {
        x = findSet(x);
        y = findSet(y);
        if (x == y) return;
        if (sizeVector[x] < sizeVector[y]) swap(x, y);
        parentVector[y] = x;
        sizeVector[x] += sizeVector[y];
        numberOfSets--;
    }
    int getNumberOfComponents() { return numberOfSets; }
    int getComponentSize(int x) { return sizeVector[findSet(x)]; }
    int getSize() { return totalSize; }
};

int main() {
    DisjointSetUnion dsu(5);
    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);
    cout << dsu.findSet(4) << "\n";
    dsu.unionSets(4, 1);
    cout << dsu.findSet(4) << " " << dsu.findSet(2) << "\n";
}
