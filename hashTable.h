#pragma once
#define MAXHASH 20

#include "Slot.h"
#include "Record.h"
#include <vector>

using namespace std;

/* This is the prototype of the hashTable class which consits array of the objects of Slot class and an array of 
    integers as the data members. It has number of member function which are listed below:

    hashTable()
        Constructor for the class

    ~hashTable()
         Destructor for the class

    void shuffle_array(int *array, unsigned int size)
        Function to shuffle the offset array to randomize it.

    bool insert(int key, int index, int& collisions)
        Function to insert the key and index pair into the slot of the table. It also gives the number of collision
        during the insertion.


    bool remove(int key)
        Function to rmove the record from the hashTable.

    bool find(int key, int& index, int & collision)
        Function to find the key in the hashTable and it gives index of the key as well as the number of collisions
        during the search.

    float alpha()
        Function to calculate the load factor of the table.

    void updateSlotIndex(int key,int index)
        Function to update the Index of the slot in the table.

    friend ostream& operator<<( ostream& os,hashTable& ht )
        Friend function to overload << operator so that it can print the hashTable.

    void printMe(vector<Record> &recordStore)
        Function to print the detail of the hashTable to support the operator overloading function of the
        Database class

*/
class hashTable
{
private:
    Slot slot[MAXHASH];
    int offsetArray[MAXHASH-1];
public:
    hashTable()
    {
        for (int i = 0; i < MAXHASH; i++)
        {
            offsetArray[i]=i+1;
        }
        shuffle_array(offsetArray, MAXHASH-1);
    }
    ~hashTable(){}
    void shuffle_array(int *array, unsigned int size);
    bool insert(int key, int index, int& collisions);
    bool remove(int key);
    bool find(int key, int& index, int & collision);
    float alpha();
    void updateSlotIndex(int key,int index);
    friend ostream& operator<<( ostream& os,hashTable& ht );
    void printMe(vector<Record> &recordStore);
};
