#ifndef QUADPROBING_H_INCLUDED
#define QUADPROBING_H_INCLUDED

#include <iostream>
class QuadProbing
{
    int *hashTable;
    int size_t;

public:
    // constructor to initialize the hashTable array with a particular size
    QuadProbing(int tableSize)
    {
        this->size_t = tableSize;
        this->hashTable = new int[tableSize];

        // initializing all the keys of the hashTable with INT_MIN:
        for (int i = 0; i < tableSize; i++)
        {
          this->hashTable[i] = INT_MIN;
        }
    }

    void insert(int key);
    int search(int key);
    void deletion(int key);
    void displayTable();

    // destructor to delete the hashTable's allocation:
    ~QuadProbing()
    {
        delete[] hashTable;
    }
};

#endif // QUADPROBING_H_INCLUDED
