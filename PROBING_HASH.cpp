#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define TABLE_SIZE 100
#define DELETED "-1"


class Node
{
public:
    string key;
    int value;
};

class HashTable
{
private:
    Node hashTable[100];
public:
    // Converts from string to int using base 128
    int convertToInt(string key) {
        int result = 0;
        for (int i = 0; i < key.size(); i++) {
            int j = key.size() - i - 1;
            result += key[i] * pow(128, j);
        }
        return result;
    }

    int hashFunction(string key) {
        int result = convertToInt(key);
        return result % TABLE_SIZE;
    }

    void insertKey(string key, int value) {
        int incre = 0;
        int index = hashFunction(key);
        while (incre != TABLE_SIZE) {
            if (hashTable[index].key == "" || hashTable[index].key == DELETED) {
                hashTable[index].key = key;
                hashTable[index].value = value;
                return;
            } else {
                incre++;
                index = (index + incre) % TABLE_SIZE;
            }
        }
        if (incre == TABLE_SIZE) {
            cout << "Error: Hash Table overflow" << endl;
        }
    }

    bool searchKey(string key) {
        int incre = 0;
        int index = hashFunction(key);
        while (hashTable[index].key != "") {
            if (hashTable[index].key == key) {
                return true;
            }
            incre++;
            index = (index + incre) % TABLE_SIZE;
        }
        return false;
    }

    void searchResult(string key) {
        if (searchKey(key)) {
            cout << key <<  " founded!" << endl;
        } else {
            cout << key << " not founded!" << endl;
        }
    }


    void deleteKey(string key) {
        int incre = 0;
        int index = hashFunction(key);
        if (searchKey(key)) {
            while (hashTable[index].key != "") {
                if (hashTable[index].key == key) {
                    hashTable[index].key = DELETED;
                    hashTable[index].value = -1;
                    cout << key << " deleted!" << endl;
                }
                incre++;
                index = (index + incre) % TABLE_SIZE;
            }
        } else {
            cout << key << " is invalid!" << endl;
        }
    }

    void printKey() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i].key != "" && hashTable[i].key != DELETED) {
                cout << "Pos: " << i + 1 << "\t" << "Key: " << hashTable[i].key << "\t" << "Value: " << hashTable[i].value << endl;
            }
        }
    }
};

int main()
{
    HashTable ht;

    cout << "Original:" << endl;
    ht.insertKey("IRON", 1);
    ht.insertKey("GOLD", 2);
    ht.insertKey("WOOD", 3);
    ht.insertKey("PLAS", 4);
    ht.insertKey("PLAT", 5);
    ht.printKey();
    cout << endl;

    cout << "Insert a key:" << endl;
    ht.insertKey("ALUM", 7);
    ht.printKey();
    cout << endl;

    cout << "Search for a key:" << endl;
    ht.searchResult("GOLD");
    ht.searchResult("DIAM");
    cout << endl;

    cout << "Delete a key:" << endl;
    ht.deleteKey("GOLD");
    ht.deleteKey("SILV");
    ht.printKey();
}