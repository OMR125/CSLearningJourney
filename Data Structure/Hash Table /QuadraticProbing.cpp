#include <algorithm>
#include "HashTable.cpp"

class QuadraticProbing : public HashTable {
   private:
    int hashFunction(int key) const;
    int probingFunction(int x) const;
    int properSize(int x) const;

   public:
    QuadraticProbing() : HashTable(){};
    QuadraticProbing(float LoadFactor) : HashTable(LoadFactor){};
};
int QuadraticProbing::hashFunction(int key) const { return key % tableSize; }
int QuadraticProbing::probingFunction(int x) const {
    return (((x * x) + x) >> 1) % tableSize;
}
int QuadraticProbing::properSize(int x) const {
    if (__builtin_popcount(x) == 1) return x;
    for (int i = 30; ~i; i--) {
        if (x & (1 << i)) {
            if (i == 30)
                throw runtime_error("Max Size Reached");  // it will crash way before that but idk how to handle that
            return 1 << (i + 1);
        }
    }
}
int main() {
    QuadraticProbing x(0.75);
    x.insert(1, 2);
    x.insert(3, 5);
    x.insert(-23, 12);
    x.insert(122, 422);
    x.insert(42, -23);
    x.insert(12, -2342);
    x.insert(119, -2);
    x.erase(12);
    x.erase(3);
    x.print();
}
