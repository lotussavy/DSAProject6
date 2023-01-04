
#include "hashTable.h"
#include "hashfunction.h"
#include <vector>
#include "Record.h"

// Function to inseert the key and index value to the table and calculate the number of collision during insertion
// Arguments: integer key, integer index and reference to integer collision
// Return: True on success and Fasle on failure
bool hashTable::insert(int key, int index, int& collisions)
{
    bool success= false;
    collisions=0;
    int slotIndex=jsHash(key)%MAXHASH;
    if (slot[slotIndex].isEmptyAfterRemoval() || slot[slotIndex].isEmptySinceStart())
    {
        slot[slotIndex].setSlot(key,index);
        success=true;
    }
    else
    {
        if(slot[slotIndex].getKey()!=key)
        {
            collisions=1;
            for (int i = 0; i < MAXHASH-1; i++)
            {
                slotIndex=(slotIndex+offsetArray[i]) % MAXHASH;
                if(slot[slotIndex].isEmptyAfterRemoval() || slot[slotIndex].isEmptySinceStart())
                {
                    slot[slotIndex].setSlot(key,index);
                    success=true;
                    break;
                }
                else
                {
                    if (slot[slotIndex].getKey()==key)
                    {
                        break;
                    }
                    
                }
                collisions=collisions+1;
            } 
        }
    }

    return success;
}



// Function to remove the slot with the given key in the hashTable
// Argument: integer key
// Return: True when removed successfully, false otherwise
bool hashTable::remove(int key)
{
    bool success=false;
    int slotIndex=jsHash(key)%MAXHASH;
    if (slot[slotIndex].isNormal() && slot[slotIndex].getKey()==key)
    {
        slot[slotIndex].kill();
        success=true;
    }
    else
    {
        for (int i = 0; i < MAXHASH-1; i++)
        {
            slotIndex=(slotIndex+offsetArray[i]) % MAXHASH;
            if(slot[slotIndex].isNormal() && slot[slotIndex].getKey()==key)
            {
                slot[slotIndex].kill();
                success=true;
                break;
            }
            if (slot[slotIndex].isEmptySinceStart())
            {
                break;
            }
            
        }
    }
    return success;
}



// Function to find the sloth with the particular key and give its index and collision during the search
// Arguments: integer key, reference to integer index and collision
// Returns: True on success and false on failure
bool hashTable::find(int key, int& index, int& collision)
{
    bool success=false;
    collision=0;
    int slotIndex=jsHash(key)%MAXHASH;
    if (slot[slotIndex].isNormal() && slot[slotIndex].getKey()==key)
    {
        index=slot[slotIndex].getIndex();
        success=true;
    }
    else
    {
        collision++;
        for (int i = 0; i < MAXHASH-1; i++)
        {
            slotIndex=(slotIndex+offsetArray[i]) % MAXHASH;
            if(slot[slotIndex].isNormal() && slot[slotIndex].getKey()==key)
            {
                index=slot[slotIndex].getIndex();
                success=true;
                break;
            }
            if (slot[slotIndex].isEmptySinceStart())
            {
                break;
            }
            collision++;
        }
    }
    return success;
}


// Function to calculate the load factor of the hashtable
// Arguments: None
// Return: float variable which is the load factor of the table
float hashTable::alpha()
{
    int count=0;
    for (int i = 0; i < MAXHASH-1; i++)
    {
        if (slot[i].isNormal())
        {
            count++;
        }
    }
    
    return (float)count / MAXHASH;
}



// Function to update the index value of the slot
// Arguments: integer key and index
// Return: void
void hashTable::updateSlotIndex(int key,int index)
{
    for (int i = 0; i < MAXHASH; i++)
    {
        if (slot[i].getKey()==key)
        {
            slot[i].setIndex(index);
        }
    }
}


// Friend fucntion to overloadd << operator for the hashtable
// Arguments: Reference to object of ostream and reference to object of hashtable
// Return : Reference to the object of ostream
ostream& operator<<( ostream& os, hashTable& ht )
{
    os<<"HashTable contents:"<<endl;
    for (int i = MAXHASH-1; i >= 0; i--)
    {
        if (ht.slot[i].isNormal())
        {
            os<<"HashTable Slot "<<i<<": Key = "<< ht.slot[i].getKey()<<", Index =" << ht.slot[i].getIndex()<<endl;
        }
        
    }
    return(os);
}



// Fuction to shuffle the offset array
// Arguments: reference to offset array, reference to unsigned integer size
// Return: void
void hashTable::shuffle_array(int *array, unsigned int size)
{
    srand(time(NULL));
    for (int i = 0; i<size; i++)
        for (int j=0; j<size-1; j++){
            if (rand()%2) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
}



// Function to print the detail of the hashTable entry to support friend function of Database class
// Argument: Reference to the vector of record objec
// Return : void
void hashTable::printMe(vector<Record> &recordStore)
{
    vector<Record>::iterator it;
    for (int i = MAXHASH-1; i >= 0; i--)
    {
        if (slot[i].isNormal())
        {
            it=recordStore.begin()+slot[i].getIndex();
            cout<<"HashTable Slot "<<i<<", recordStore slot "<<slot[i].getIndex()  <<" -- "<<it->getLastName()<<","
             <<it->getFirstName()<<"(U"<< setw(8) << setfill('0') << it->getUID()<<"): "<< it->getYear() <<endl;
        }
        
    }
}