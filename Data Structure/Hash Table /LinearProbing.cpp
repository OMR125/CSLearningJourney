#include <algorithm>
#include "HashTable.cpp"

class LinearProbing : public HashTable {
   private:
    const int LinearProbingConstant = 83;
    int hashFunction(int key) const;
    int probingFunction(int x) const;
    int properSize(int x) const;

   public:
    int x() { return tableSize; }
    LinearProbing() : HashTable(){};
    LinearProbing(float LoadFactor) : HashTable(LoadFactor){};
};
int LinearProbing::hashFunction(int key) const { return key % tableSize; }
int LinearProbing::probingFunction(int x) const {
    return (LinearProbingConstant * x) % tableSize;
}
int LinearProbing::properSize(int x) const {
    while (__gcd(tableSize, LinearProbingConstant) != 1) {
        x++;
    }
    return x;
}
int main() {
    LinearProbing x(0.44);
    x.insert(1, 2);
    x.insert(2, 3);
    x.insert(5, 4);
    x.insert(821, 9);
    x.insert(24, 9);
    x.insert(24241, 3);
    x.insert(-1324, 2);
    x.insert(7654, 11);
    x.erase(5);
    x.print();
}
