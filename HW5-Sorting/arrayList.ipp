#include <iostream>

/////////////////////////////////////
// Author: Chris Kelley
// CSS 342 - Project 5
// Time: 20 hours
////////////////////////////////////

//------------------------------------------------------
// Static Field Initialization:
//------------------------------------------------------
template<class TYPE>
int ArrayList<TYPE>::numAccess = 0;
template<class TYPE>
int ArrayList<TYPE>::numSwap = 0;
template<class TYPE>
int ArrayList<TYPE>::numRemove = 0;
template<class TYPE>
int ArrayList<TYPE>::numInsertAt = 0;
template<class TYPE>
int ArrayList<TYPE>::numAppends = 0;
//-------------------------------------------------------

///////////////////////////////////////////////
//Initialization of ArrayList Class
//////////////////////////////////////////////

template <class TYPE>
ArrayList<TYPE>::ArrayList()
{
	arrayList = new TYPE[INITIAL_SIZE];
	capacity = INITIAL_SIZE;
}

//creates a deep copy of the provided arrayList
template <class TYPE>
ArrayList<TYPE>& ArrayList<TYPE>::operator=(const ArrayList<TYPE>& rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	//increase arrayList capacity if it is too
	//small to hold rhs items
	while(capacity < rhs.itemCount)
	{
		doubleArraySize();
	}

	itemCount = rhs.itemCount;
	for(int i = 0; i < rhs.itemCount; i++)
	{
		arrayList[i] = rhs.arrayList[i];
	}
	return *this;
}

template<class TYPE>
ArrayList<TYPE>::ArrayList(const ArrayList<TYPE> & rhs)
{
	TYPE * newArray = new TYPE(rhs.itemCount);
	arrayList = newArray;
	itemCount = rhs.itemCount;
	for (int i = 0; i < rhs.itemCount; i++)
	{

		arrayList[i] = rhs.arrayList[i];
	}
}

template <class TYPE>
ArrayList<TYPE>::ArrayList(int arraySize)
{
	arrayList = new TYPE[arraySize];
	capacity = arraySize;
}

///////////////////////////////////////////////////////////////
// Returns the item stored in the specified index of the array
template <class TYPE>
TYPE& ArrayList<TYPE>::operator[](int index) const throw(std::out_of_range)
{
	if(index < 0 || index > itemCount - 1)
	{
		throw(std::out_of_range("Index out of range"));
		
	}
	numAccess++;
	return arrayList[index];
}

//////////////////////////////////////////////////////
// Returns true if array size is 0.
template <class TYPE>
bool ArrayList<TYPE>::isEmpty() const
{
	if(itemCount == 0)
	{
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////
// Returns the number of items in the array
template<class TYPE>
int ArrayList<TYPE>::getSize() const
{
	return itemCount;
}

//////////////////////////////////////////////////////////////
// Inserts the specified item at the specified index.
// Shift items after index up 1 in the array.
template<class TYPE>
void ArrayList<TYPE>::insertAt(int index, const TYPE& newEntry)
	throw(std::out_of_range)
{
	if(itemCount == capacity - 1)
	{
		doubleArraySize();
	}

	if(index < 0 || index > itemCount)
	{
		throw(std::out_of_range("Index out of range"));
	}
	for(int i = itemCount - 1; i >= index; i--)
	{
		arrayList[i + 1] = arrayList[i];
	}
	arrayList[index] = newEntry;
	numInsertAt++;
	itemCount++;
}

///////////////////////////////////////////////////////////
// Removes item at specified index from the array. Shifts
// all other items after removed item down 1 in the array
template <class TYPE>
void ArrayList<TYPE>::removeAt(int index) throw(std::out_of_range)
{
	///////////////////////////////////////
	//add array size guard
	if(index < 0 || index > itemCount)
	{
		throw(std::out_of_range("Index out of range"));
	}
	if(index == 0 && itemCount == 1)
	{
		itemCount--;
		return;
	}
	for(int i = index + 1; i < itemCount; i++)
	{
		arrayList[i - 1] = arrayList[i];
	}
	numRemove++;
	itemCount--;
}

//////////////////////////////////////////////////
// Adds specified item to the end of the array
template <class TYPE>
void ArrayList<TYPE>::append(const TYPE& newItem)
{
	if(itemCount == capacity - 1)
	{
		doubleArraySize();
	}

	TYPE item = newItem;
	arrayList[itemCount] = item;
	numAppends++;
	itemCount++;
}

/////////////////////////////////////////////////////////////
// Swaps the values of the 'from' and 'to' specified indices
template <class TYPE>
void ArrayList<TYPE>::swap(int from, int to) throw(std::out_of_range)
{
	if ((from < 0 || from > itemCount - 1) ||
		(to < 0 || to > itemCount - 1))
	{
		throw(std::out_of_range("Index out of range"));
	}
	TYPE temp = arrayList[from];
	arrayList[from] = arrayList[to];
	arrayList[to] = temp;
	numSwap++;
}
////////////////////////////////////////////////////////////
// Returns the item stored the specified index of the array
template <class TYPE>
TYPE& ArrayList<TYPE>::getAt(int index) const throw(std::out_of_range)
{
	if(index < 0 || index > itemCount - 1)
	{
		throw(std::out_of_range("Index out of range"));
	}
	numAccess++;
	return arrayList[index];
}

//////////////////////////////////////////////////////////
// Sets itemcount to 0, restricting access to the items
// in the array. Acts as a clearing function.
template <class TYPE>
void ArrayList<TYPE>::clearAll()
{
	itemCount = 0;
}

//////////////////////////////////////////////////////////
//Sets static variables to 0: numAccess, numSwap, numRemove,
// numInsertAt, and numAppends.
template <class TYPE>
void ArrayList<TYPE>::clearStatistics()
{
	numAccess = 0;
	numSwap = 0;
	numRemove = 0;
	numInsertAt = 0;
	numAppends = 0;
}

//////////////////////////////////////////////
// returns numAccess
template<class TYPE>
int ArrayList<TYPE>::getNumAccess() const
{
	return numAccess;
}
/////////////////////////////////////////////////
// returns numSwap
template<class TYPE>
int ArrayList<TYPE>::getNumSwap() const
{
	return numSwap;
}

////////////////////////////////////////////////////
// returns numRemove
template <class TYPE>
int ArrayList<TYPE>::getNumRemove() const
{
	return numRemove;
}

/////////////////////////////////////////////////////
// returns numInsertAt
template <class TYPE>
int ArrayList<TYPE>::getNumInsertAt() const
{
	return numInsertAt;
}

/////////////////////////////////////////////////////
// return numAppends
template <class TYPE>
int ArrayList<TYPE>::getNumAppends() const
{
	return numAppends;
}

////////////////////////////////////////////////
// Doubles the maximum capacity of the array
template<class TYPE>
void ArrayList<TYPE>::doubleArraySize()
{
	capacity *= 2;
	TYPE * tempArray = new TYPE[capacity];
	for(int i = 0; i < itemCount; i++)
	{
		tempArray[i] = arrayList[i];
	}
	delete arrayList;
	arrayList = tempArray;
}

///////////////////////////////////////////////////
// Iterates through array and prints each element
// to the console
template <class TYPE>
void ArrayList<TYPE>::printArray()
{
	if(isEmpty())
	{
		std::cout << "List is empty" << std::endl;
		return;
	}
	for(int i = 0; i < itemCount; i++)
	{
		std::cout << arrayList[i] << "|";
		//std::cout << "index " << i << ": " << arrayList[i] << std::endl;
	}
}










