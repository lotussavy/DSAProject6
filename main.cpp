/*
Name: Kamal Acharya
UID:U00997907
Project Name:  Hash Table Indexing
Description:
Task for this assignment is to implement a database of student records. 
Database consist of two parts: an unsorted vector of student records,and an index of student IDs implemented as a closed hash table
with pseudo-random probing.
It consists of the following files
Database.h => Contain the prototype of Database class
Database.cpp => Contain definition of all the member function of Database class
hashfunction.h => Contain definition of the hashfunction function which is used in this project
hashTable.h => Contain the prototype of the hashTable class
hashTable.cpp => Contain the definition of all the member fucntion of hashTable Class
Record.h => Contain the detail of the Record class
Slot.h => Contain the detail of the Slot class
main.cpp => Main file through which the program is run

Details of the functions and classes are provided in the individual files.
*/

#include <iostream>
#include <iomanip>
#include <string> 
#include <stdlib.h>


#include "hashTable.h"
#include "Database.h"
#include "Record.h"

using namespace std;

//Fuctions prototypes
void insertRecord(Database& db); //Function to insert the record 
void deleteRecord(Database& db); //Fucntion to delte the record 
void searchRecord(Database& db); //Function to search the record


int main()
{
	Database db;
	char action;
	cout<<"Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?"<<endl;
	cout<<"Enter action:  ";
	cin>>action;
	while (action !='Q' && action !='q')
	{
		if (action == 'I' || action =='i')
		{
			insertRecord(db);
		}
		else if(action == 'D' || action == 'd')
		{
			deleteRecord(db);
		}
		else if(action == 'S' || action == 's')
		{
			searchRecord(db);
		}
		else
		{
			cout<<"Wrong input. Please select again"<<endl;
		}
		
		cout<<"Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?"<<endl;
		cout<<"Enter action:  ";
		cin>>action;
	}

	cout<<"Exiting."<<endl;
	
	return(0);
}


//This function take database object reference as an argument. It asks user to insert the details 
// of the student to be inserted. And give the output accordingly if it succed or not.
void insertRecord(Database& db)
{
	Record newRecord;
	string lName,fName,year;
	int UID,collision;
	bool result;
	cout<<"Inserting a new record."<<endl;
	cout<<"Last name:  ";
	cin>>lName;
	newRecord.setLastName(lName);
	cout<<"First name:  ";
	cin>>fName;
	newRecord.setFirstName(fName);
	cout<<"UID: ";
	cin>>UID;
	newRecord.setUid(UID);
	cout<<"Year:  ";
	cin>>year;
	newRecord.setYear(year);
	result=db.insert(newRecord,collision);
	if (result)
	{
		cout<<"Record inserted."<<endl;
	}
	else
		cout<<"Sorry Record cannot be inserted"<<endl;
}




//This function take database object reference as an argument. It asks user to insert the UID
// of the student to be deleted. And give the output accordingly if it succed or not.
void deleteRecord(Database& db)
{
	int UID;
	bool result;
	cout<<"Enter UID to delete: ";
	cin>>UID;
	result=db.remove(UID);
	if (result)
	{
		cout<<"Removed Successfully"<<endl;
	}
	else
		cout<<"Sorry, Cannot remove the record."<<endl;
}




//This function take database object reference as an argument. It asks user to insert the UID 
// of the student to be searched. On success, it prints the details of the student along with it
// it also prints the number of collision during the search.
void searchRecord(Database& db)
{
	int UID,collision;
	Record foundRecord;
	bool result;
	cout<<"Enter UID to search for: ";
	cin>>UID;
	result= db.find(UID,foundRecord,collision);
	if (result)
	{
		cout<<"Searching... record found ("<<collision <<" collisions during search)"<<endl;
		cout<<"----------------------------"<<endl;
		cout<<"Last name:  "<<foundRecord.getLastName()<<endl;
		cout<<"First name:  "<<foundRecord.getFirstName()<<endl;
		cout<<"UID: "<<foundRecord.getUID()<<endl;
		cout<<"Year:  "<<foundRecord.getYear()<<endl;
		cout<<"----------------------------"<<endl;
	}
	else
		cout<<"Searching... record not found"<<endl;
}