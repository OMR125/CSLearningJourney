#include <bits./stdc++.h>

using namespace std;

class HashMap {
   private:
    static const int MAXSIZE = 5;
    list<pair<int, int>> table[MAXSIZE];
    int size = 0;

   public:
    int hash(int key) { return key % MAXSIZE; }
    bool empty() { return !size; }
    bool getSize() { return size; }
    void insert(int key, int value) {
        int hashValue = hash(key);
        auto &cell = table[hashValue];
        bool found = 0;
        for (auto &e : cell) {
            if (e.first == key) {
                found = 1;
                e.second = value;
                break;
            }
        }
        if (!found) cell.push_back({key, value}), size++;
    }
    void erase(int key) {
        int hashValue = hash(key);
        auto &cell = table[hashValue];

        auto it = cell.begin();
        bool found = 0;
        for (const auto &e : cell) {
            if (e.first == key) {
                found = 1;
                it = cell.erase(it), size--;
                break;
            }
            it++;
        }
        if (!found) cout << "Key doesn't exist!\n";
    }
    int getValue(int key) {
        int hashValue = hash(key);
        for (const auto &e : table[hashValue]) {
            if (e.first == key) {
                return e.second;
            }
        }
        return 0;
    }
    void print() {
        for (int i = 0; i < MAXSIZE; i++)
            for (const auto &e : table[i])
                cout << e.first << " " << e.second << "\n";
    }
    int operator[](int key) { return getValue(key); }
};
int main() {
    HashMap mp;
    mp.insert(1, 2);
    mp.insert(2, 3);
    mp.insert(5, 3);
    mp.insert(7, 8);
    mp.insert(12, 9);
    mp.insert(7, 3);
    mp.erase(7);
    mp.print();
}

