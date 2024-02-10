#include <iostream>
#include <list>

template <typename K, typename V>
class HashMap {
   private:
    static const int MAXSIZE = 20;
    std::list<std::pair<K, V>> table[MAXSIZE];
    int size = 0;

   public:
    int hashFunction(K key) const {  // can be better of course
        return key % MAXSIZE;
    }
    bool empty() const { return !size; }
    int getSize() const { return size; }
    void insert(K key, V value) {
        int hashValue = hashFunction(key);
        auto &cell = table[hashValue];
        for (auto &entry : cell) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        cell.emplace_back(key, value);
        size++;
    }
    void erase(K key) {
        int hashValue = hashFunction(key);
        auto &cell = table[hashValue];
        for (auto it = cell.begin(); it != cell.end(); ++it)
            if (it->first == key) {
                cell.erase(it);
                size--;
                return;
            }

        std::cout << "Key doesn't exist!\n";
    }
    V getValue(K key) const {
        int hashValue = hashFunction(key);
        for (const auto &e : table[hashValue])
            if (e.first == key) return e.second;

        throw std::runtime_error("Key not found");
    }
    void print() const {
        for (int i = 0; i < MAXSIZE; i++)
            for (const auto &e : table[i])
                std::cout << e.first << " " << e.second << "\n";
    }
    V operator[](K key) const { return getValue(key); }
};

int main() {
    HashMap<int, int> mp;
    mp.insert(1, 2);
    mp.insert(2, 3);
    mp.insert(5, 3);
    mp.insert(7, 8);
    mp.insert(12, 9);
    mp.insert(7, 3);
    std::cout << mp.getSize() << "\n";
    mp.print();
    mp.erase(7);
    std::cout << mp.getSize() << "\n";
    mp.print();
}
