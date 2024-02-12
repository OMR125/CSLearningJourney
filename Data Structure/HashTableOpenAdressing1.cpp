#include <bits./stdc++.h>
using namespace std;

// to make Linear Probing stop cycle and effecient. GCD(a,N) = 1 . N is the size
// of the hash table. for Quadratic probing there's a lot of possible functions
// for P(x) but here i'll use P(x) = (x^2+x)/2 and N must be a power of two .
// there exists a max load factor as will which when multiplied by the size it
// produced a variable which is our key to resize the table when we cycle more
// than it. we resize the table to 2N when we cycle through the hash table more
// than or equal (max load factor * N) . max load factor is less than one.
// double hashing is another way that i will cover next
enum State { ALIVE, USED, DEAD };
class HashTable {
   private:
    const int LinearConstant = 1;
    float loadFactor;
    int elements = 0, size = 1;
    vector<pair<int, int>> v;
    vector<int> flag;

   private:
    void adjustSize() {
        elements = 0;
        size *= 2;
        while (__gcd(size, LinearConstant) != 1) size++;
        vector<pair<int, int>> oldTable(v.begin(), v.end());
        vector<int> oldflag(flag.begin(), flag.end());
        v.clear(), v.resize(size);
        flag.clear(), flag.resize(size);
        for (int i = 0; i < oldTable.size(); i++)
            if (oldflag[i] == USED)
                insert(oldTable[i].first, oldTable[i].second);
    }
    bool reSize() { return elements >= Threshold(); }
    int getTableSize() { return size; }
    int Threshold() { return loadFactor * size; }

   public:
    HashTable(float _x) : loadFactor(_x) {
        v.resize(size);
        flag.resize(size);
    };
    HashTable() : loadFactor(0.75) {
        v.resize(size);
        flag.resize(size);
    };
    int H(int key) { return key % size; }
    int P(int x) { return LinearConstant * x % size; }
    void insert(int key, int value) {
        if (reSize()) adjustSize();

        int hash = abs(H(key)) % size;
        bool found = 0;
        for (int x = 1, j = -1; !found; hash = (hash * P(x++)) % size) {
            if (flag[hash] == DEAD && j == -1)
                j = hash;
            else if (v[hash].first == key || flag[hash] == ALIVE) {
                if (v[hash].first == key) elements--;
                if (~j) {
                    flag[hash] = ALIVE;
                    hash = j;
                }
                flag[hash] = USED;
                v[hash] = {key, value}, found = 1;
            }
        }
        elements++;
    }
    void erase(int key) {
        int hash = abs(H(key)) % size;
        for (int x = 1;; hash = (hash * P(x++)) % size) {
            if (flag[hash] == DEAD) continue;
            if (flag[hash] == ALIVE) break;
            if (v[hash].first == key) {
                elements--;
                flag[hash] = DEAD;
                break;
            }
        }
    }
    int getvalue(int key) {
        int hash = abs(H(key)) % size;
        bool found = 0;
        for (int x = 1, j = -1;; hash = (hash * P(x++)) % size) {
            if (flag[hash] == DEAD && j == -1)
                j = hash;
            else if (flag[hash] == USED && v[hash].first == key) {
                if (~j) {
                    flag[hash] = ALIVE;
                    v[j] = v[hash];
                    hash = j;
                }
                flag[hash] = USED;
                return v[hash].second;
            } else if (flag[hash] == ALIVE) {
                return 0;
            }
        }
    }
    int operator[](int key) { return getvalue(key); }
    void print() {
        for (int i = 0; i < size; i++) {
            if (flag[i] == USED)
                cout << v[i].first << " " << v[i].second << "\n";
        }
    }
    int getSize() { return elements; }
};
int main() {
    HashTable x;
    x.insert(19, 11);
    x.insert(1, 2);
    x.insert(3, 7);
    x.insert(2, 4);
    x.insert(12, 9);
    x.insert(8, 3);
    x.insert(41, -2);
    x.insert(-821, -32);
    x.erase(-821);
    x.print();
}
