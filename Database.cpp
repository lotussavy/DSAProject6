#include "Database.h"
#include "hashTable.h"
#include "Record.h"

// Function to insert the record into the database and gives the number of collision during insertion
// Arguments: Reference to object of record class and reference to int for counting collision
// Return: True when successful and false when fails
 bool Database::insert(const Record& newRecord, int& collisions)
 {
     int vectorIndex= recordStore.size();
     collisions=0;
     int index=0;
     int findCollision;
     bool success=false;
     if (!indexTable.find(newRecord.getUID(),index,findCollision))
     {
         if (indexTable.insert(newRecord.getUID(),vectorIndex,collisions))
         {        
            recordStore.insert(recordStore.begin()+vectorIndex,newRecord);
            success=true;
         }
     }
     return success;
 }


// Function to remove the record with the given key
// Arguments: integer varaiable key
// Returns: True on success and false on failure
 bool Database::remove(int key)
 {
     int index;
     int collision;
     bool success=false;
     if (indexTable.find(key,index,collision))
     {
         if (indexTable.remove(key))
         {
             Record &student = recordStore.at( recordStore.size()-1 ); // push the data from the front not good
             recordStore.insert(recordStore.begin()+index,student);
             recordStore.erase(recordStore.begin()+index+1);
             recordStore.pop_back();
             int uidOfLastEntry = student.getUID();
             indexTable.updateSlotIndex(uidOfLastEntry,index);
             success=true;
         }
     }
     return success;
 }


// Function to find the record with the given uid and gives the reference to the record and number of collision during search
//Arguments: Integer UID, reference to the record object and reference to the integer
// Returns: True on success and False on failure
bool Database::find(int uid, Record& foundRecord, int& collision)
{
    bool success=false;
    collision=0;
    int index;
    if (indexTable.find(uid,index,collision))
    {
        foundRecord = recordStore.at( index );
        success=true;
    }
    return success;
}



// Function to give the load factor of the table in the database
// Arguments: none
// Returns: load factor of the table which is float value
float Database::alpha()
{
    return indexTable.alpha();
}


//Friend function of the database class to overload the << operator
// Arguments: Reference to ostream object, reference to database object
// Return: Reference ot ostream object
ostream& operator<<( ostream& os,Database& db )
{
    os<<"Database contents:"<<endl;
    db.indexTable.printMe(db.recordStore);
    return os;
}


