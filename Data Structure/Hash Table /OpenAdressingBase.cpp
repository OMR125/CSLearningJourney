#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

enum EntryState { ALIVE, USED, DEAD };

class HashTable {
   protected:
    float maxLoadFactor;
    int totalEntries = 0;
    int tableSize = 1;
    vector<pair<int, int>> hashTable;
    vector<int> entryState;

   protected:
    virtual int hashFunction(int key) const = 0;

    virtual int probingFunction(int x) const = 0;

    virtual int properSize(int x) const = 0;

    int loadThreshold() const { return maxLoadFactor * tableSize; }

    bool needsResizing() const { return totalEntries >= loadThreshold(); }

    void adjustTableSize();

   public:
    HashTable(float loadFactor);
    HashTable();
    void insert(int key, int value);
    void erase(int key);
    int getValue(int key);
    int operator[](int key);
    void print() const;
    int size() const;
};

HashTable::HashTable(float loadFactor)
    : maxLoadFactor(min((float)1, loadFactor)) {
    hashTable.resize(tableSize);
    entryState.resize(tableSize);
}

HashTable::HashTable() : maxLoadFactor(0.75) {
    hashTable.resize(tableSize);
    entryState.resize(tableSize);
}

void HashTable::adjustTableSize() {
    totalEntries = 0;
    tableSize *= 2;
    tableSize = properSize(tableSize);

    vector<pair<int, int>> oldTable(hashTable.begin(), hashTable.end());
    vector<int> oldEntryState(entryState.begin(), entryState.end());

    hashTable.clear();
    hashTable.resize(tableSize);
    entryState.clear();
    entryState.resize(tableSize);

    for (int i = 0; i < oldTable.size(); i++) {
        if (oldEntryState[i] == USED) {
            insert(oldTable[i].first, oldTable[i].second);
        }
    }
}

void HashTable::insert(int key, int value) {
    if (needsResizing()) {
        adjustTableSize();
    }

    int hashValue = abs(hashFunction(key)) % tableSize;
    bool isInserted = false;

    for (int x = 1, emptySlot = -1; !isInserted;
         hashValue = (hashValue * probingFunction(x++)) % tableSize) {
        if (entryState[hashValue] == DEAD && emptySlot == -1) {
            emptySlot = hashValue;
        } else if (hashTable[hashValue].first == key || entryState[hashValue] == ALIVE) {
            if (hashTable[hashValue].first == key) {
                totalEntries--;
            }
            if (~emptySlot) {
                entryState[hashValue] = ALIVE;
                hashValue = emptySlot;
            }
            entryState[hashValue] = USED;
            hashTable[hashValue] = {key, value};
            isInserted = true;
        }
    }
    totalEntries++;
}

void HashTable::erase(int key) {
    int hashValue = abs(hashFunction(key)) % tableSize;

    for (int x = 1;;
         hashValue = (hashValue * probingFunction(x++)) % tableSize) {
        if (entryState[hashValue] == DEAD) {
            continue;
        }
        if (entryState[hashValue] == ALIVE) {
            break;
        }
        if (hashTable[hashValue].first == key) {
            totalEntries--;
            entryState[hashValue] = DEAD;
            break;
        }
    }
}

int HashTable::getValue(int key) {
    int hashValue = abs(hashFunction(key)) % tableSize;
    bool isFound = false;

    for (int x = 1, emptySlot = -1;;
         hashValue = (hashValue * probingFunction(x++)) % tableSize) {
        if (entryState[hashValue] == DEAD && emptySlot == -1) {
            emptySlot = hashValue;
        } else if (entryState[hashValue] == USED && hashTable[hashValue].first == key) {
            if (~emptySlot) {
                entryState[hashValue] = ALIVE;
                hashTable[emptySlot] = hashTable[hashValue];
                hashValue = emptySlot;
            }
            entryState[hashValue] = USED;
            return hashTable[hashValue].second;
        } else if (entryState[hashValue] == ALIVE) {
            return 0;
        }
    }
}

int HashTable::operator[](int key) { return getValue(key); }

void HashTable::print() const {
    for (int i = 0; i < tableSize; i++) {
        if (entryState[i] == USED) {
            cout << hashTable[i].first << " " << hashTable[i].second << "\n";
        }
    }
}

int HashTable::size() const { return totalEntries; }
