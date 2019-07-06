#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <stdexcept>
#include "listInterface.h"
const int INITIAL_SIZE = 100;

/////////////////////////////////////
// Author: Chris Kelley
// CSS 342 - Project 5
// Time: 20 hours
////////////////////////////////////

///////////////////////////////////////////////////////
// ArrayList class
//		Inherits from ListInterface<TYPE>
//		Dynamic sizing array with methods for access,
//		insert, swap, etc.
///////////////////////////////////////////////////////

template<class TYPE>
class ArrayList: public ListInterface<TYPE>
{
private:
	TYPE * arrayList = nullptr;
	int itemCount = 0;
	int capacity = 0;
	static int numAccess;
	static int numSwap;
	static int numRemove;
	static int numInsertAt;
	static int numAppends;

	//doubles the capacity of the array
	void doubleArraySize();

public:

	ArrayList();

	//Default constructor
	ArrayList(int arraySize);

	//copy constructor
	ArrayList(const ArrayList<TYPE> & rhs);

	//destructor
	virtual ~ArrayList(){}

	//return current capacity of the arrayList, used
	//to determine if the array size needs to be 
	//increased.
	int getCapacity() const
	{
		return capacity;
	}

	//operator = override
	ArrayList& operator =(const ArrayList<TYPE>& rhs);

	// Allows access to the item stored at the specified index.
	TYPE& operator[](int index) const throw(std::out_of_range);

	//Returns true if ArrayList is empty (no items).
	bool isEmpty() const;

	//Returns the size of the ArrayList (number of items).
	int getSize() const;

	//Inserts specified item at the specified index in the array
	void insertAt(int index, const TYPE& newEntry) 
        throw(std::out_of_range);

	//Removes item from array at the specified index
	void removeAt(int index) throw(std::out_of_range);

	//Add specified item to the end the array
	void append(const TYPE&);

	// Move item stored at 'from' position to 'to' position
	// Move item stored at 'to' position to 'from' position
	void swap(int from, int to) throw(std::out_of_range);

	//Returns item stored at the specified index
	TYPE& getAt(int index) const throw(std::out_of_range);

	//Removes items from ArrayList
	void clearAll();

	///////////////////////////////////////
	//Static methods
	///////////////////////////////////////

	// Resets static counting variables to 0
	// Applies to: numAccess, numSwap, numRemove, numInsertAt
	// and numAppends
	void clearStatistics();

	// Returns the number of times the access []
	// operator has been called
	int getNumAccess() const;

	// Returns the number of times that the function
	// swap() has been called.
	int getNumSwap() const;

	// Returns the number of times the function remove()
	// has been called.
	int getNumRemove() const;

	// Returns the number of times the function insert()
	// has been called.
	int getNumInsertAt() const;

	// Returns the number of times the function append()
	// has been called.
	int getNumAppends() const;

	//prints the items in the array to the console
	void printArray();

};

//struct to hold stats for each sort method
struct ArrayStats
{
	int countAccess;
	int countRemove;
	int countInsert;
	int countSwap;
	int countAppend;
};
#include "arrayList.ipp"
#endif

