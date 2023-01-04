#pragma once
#include <vector>
#include "hashTable.h"
#include "Record.h"

/* This is the prototype of the Database class which consits of hashTable and vector of Record as the data member.
    It has following member functions:

        Database()
            Constructor for the Database class

        ~Database()
            Destructor for the Database class

        bool insert(const Record& newRecord, int& collisions)
            Function to insert the record into the recordStore and also gives the number of collision during 
            the insertion into the hashTable

        bool remove(int key)
            Function to remove the record for the given key in the recordstore as well as in the hashTable.

        bool find(int uid, Record& foundRecord, int& collision)
            Function to find the record with given UID in the recordStore. It also gives the number of collision
            during search in the hashTable.

        float alpha()
            Function to calculate the load factor of the hashTable in the databse.

        friend ostream& operator<<( ostream& os,Database& db )
            Friend function to overload the << operator so that it can print the Database object.
*/


class Database
{
    private:
        hashTable indexTable;
        vector<Record> recordStore;
    public:
        Database(){ }
        ~Database(){ }
        bool insert(const Record& newRecord, int& collisions);
        bool remove(int key);
        bool find(int uid, Record& foundRecord, int& collision);
        float alpha();
        friend ostream& operator<<( ostream& os,Database& db );
};