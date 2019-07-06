#include "workQueue.h"
#include <iostream>
using namespace std;

/////////////////////////
//  Chris Kelley
//  CSS 342 - Project 2
//  25 hours
//  Cygwin
/////////////////////////

WorkQueue::WorkQueue()
{
	headPtr = nullptr;
	itemCount = 0;
}
///////////////////////////////////////
// Traverses through rhs WorkQueue and
// copies workitems to nodes into 
// this WorkQueue
////////////////////////////////////////
WorkQueue::WorkQueue(const WorkQueue& rhs)
{
	itemCount = rhs.itemCount;
	
	//if rhs headPtr is empty, so is copy
	if (rhs.headPtr == nullptr)
	{
		headPtr = nullptr;
	}
	
	headPtr = new Node(rhs.headPtr->getItem());
	Node * rhsCurPtr = rhs.headPtr->getNext();
	Node * thisNodePtr = headPtr;
	while (rhsCurPtr)
	{
		WorkItem copyItem = rhsCurPtr->getItem();
		Node * cpyNodePtr = new Node(copyItem);
		thisNodePtr->setNext(cpyNodePtr);
		thisNodePtr = thisNodePtr->getNext();
		rhsCurPtr = rhsCurPtr->getNext();
	}
	thisNodePtr->setNext(nullptr);
}

///////////////////////////////////////
// Traverses through rhs Workqueue and
// copies WorkItems to this WorkQueue
///////////////////////////////////////
WorkQueue& WorkQueue::operator = (const WorkQueue& rhs)
{
	itemCount = rhs.itemCount;

	//if rhs headPtr is empty, so is copy
	if (rhs.headPtr == nullptr)
	{
		headPtr = nullptr;
	}

	headPtr = new Node(rhs.headPtr->getItem());
	Node * rhsCurPtr = rhs.headPtr->getNext();
	Node * thisNodePtr = headPtr;
	while (rhsCurPtr)
	{
		WorkItem copyItem = rhsCurPtr->getItem();
		Node * cpyNodePtr = new Node(copyItem);
		thisNodePtr->setNext(cpyNodePtr);
		thisNodePtr = thisNodePtr->getNext();
		rhsCurPtr = rhsCurPtr->getNext();
	}
	thisNodePtr->setNext(nullptr);

	return *this;
}

WorkQueue::~WorkQueue()
{
}
////////////////////////////////////////////
// Traverses list and places the WorkItem
// in order in the list.
/////////////////////////////////////////////
void WorkQueue::addWorkItem(const WorkItem& newItem)
{
	Node * newNodePtr = new Node(newItem);
	Node * curPtr = nullptr;
	Node * prevPtr = nullptr;
	bool isAdded = false;

	//if item count is zero, add to front
	if (itemCount == 0)
	{
		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
		itemCount++;
		isAdded = true;
	}
	//if item count is one, see if the priority is greater
	//than the already existing item
	else if (itemCount == 1)
	{
		if (newItem.getPriority() > headPtr->getItem().getPriority())
		{
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
			itemCount++;
			isAdded = true;
		}
		else
		{
			headPtr->setNext(newNodePtr);
			itemCount++;
			isAdded = true;
		}
	}
	//if the priority of the new item is greater than the 
	//head WorkItem, place new item at front of list
	else if (newItem.priority > headPtr->getItem().getPriority())
	{
		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
		itemCount++;
		isAdded = true;
	}
	//for all other items, traverse list and place in 
	//order in list
	else
	{
		curPtr = headPtr->getNext();
		prevPtr = headPtr;
		while (curPtr->getNext())
		{
			if (newItem.priority <= curPtr->getItem().getPriority())
			{
				curPtr = curPtr->getNext();
				prevPtr = prevPtr->getNext();
			}
			else
			{
				prevPtr->setNext(newNodePtr);
				newNodePtr->setNext(curPtr);
				itemCount++;
				isAdded = true;
				break;
			}
		}
	}
	//if it hasn't already been added, add to end
	if (!isAdded)
	{
		if (newItem.getPriority() > curPtr->getItem().getPriority())
		{
			prevPtr->setNext(newNodePtr);
			newNodePtr->setNext(curPtr);
			itemCount++;
		}
		else 
		{
			curPtr->setNext(newNodePtr);
			itemCount++;
		}
	}
}

////////////////////////////////////////////////
// Traverses list and returns the highest
// priority item for the priority provided
// If no WorkItem exists for priority specified
// a logic error will be thrown
/////////////////////////////////////////////////
const WorkItem& WorkQueue::nextWorkItem(int priority) const
{
	//If headPtr is null, there are no items to return
	if (headPtr == nullptr)
	{
		throw (logic_error("Error: empty Queue"));
	}

	Node * curPtr = headPtr;
	bool isFound = false;
	bool getOldest = false;
	int abovePriority = 0;
	int lowestPriority = curPtr->getItem().getPriority();

	for (int i = 0; i < itemCount - 1; i++)
	{
		curPtr = curPtr->getNext();
		if (curPtr->getItem().getPriority() < lowestPriority)
		{
			lowestPriority = curPtr->getItem().getPriority();
		}
	}
	curPtr = headPtr;
	if (lowestPriority > priority)
	{
		for (int i = 0; i < itemCount; i++)
		{
			if (curPtr->getItem().getPriority() == lowestPriority)
			{
				isFound = true;
				break;
			}
			else
			{
				curPtr = curPtr->getNext();
			}
		}
	}
	if (!isFound)
	{
		curPtr = headPtr;
		while (curPtr->getNext())
		{
			if (curPtr->getItem().getPriority() == priority)
			{
				isFound = true;
				break;
			}
			else if (curPtr->getItem().getPriority() > priority && 
				curPtr->getNext()->getItem().getPriority() < priority)
			{
				abovePriority = curPtr->getItem().getPriority();
				isFound = true;
				bool getOldest = true;
				break;
			}
			else
			{
				curPtr = curPtr->getNext();
			}
		}
	}
	if (abovePriority)
	{
		curPtr = headPtr;
		while (curPtr->getNext())
		{
			if (curPtr->getItem().getPriority() == abovePriority)
			{
				isFound = true;
				break;
			}
			else
			{
				curPtr = curPtr->getNext();
			}
		}
	}
	if (!isFound)
	{
		throw (logic_error("error"));
	}

	WorkItem * returnItem = new WorkItem(curPtr->getItem());
	return *(returnItem);
}

//////////////////////////////////////
// Traverses list and identifies if
// a WorkItem exists in the queue for
// the specified priority
/////////////////////////////////////
bool WorkQueue::hasWorkItem(int priority)
{
	Node * curPtr = headPtr;
	bool isFound = false;
	for (int i = 0; i < itemCount - 1; i++)
	{
		if (curPtr->getItem().getPriority() >= priority)
		{
			isFound = true;
			break;
		}
		curPtr = curPtr->getNext();
	}
	return isFound;
}

//////////////////////////////////////////
// Traverses list and identifies if
// a WorkItem exists for the key specified
///////////////////////////////////////////
bool WorkQueue::containsKey(const string& thisKey)
{
	Node * curPtr = headPtr;
	bool isFound = false;
	for (int i = 0; i < itemCount; i++)
	{
		if (curPtr->getItem().getKey().compare(thisKey) == 0)
		{
			isFound = true;
		}
		curPtr = curPtr->getNext();
	}
	return isFound;
}

///////////////////////////////////////////
// Traverses list and identifies where the 
// workItem of the specified key exists.
// The workItem is then moved to before
// other items of the same priority
//////////////////////////////////////////
void WorkQueue::bumpWorkItem(const string& key)
{
	if (!WorkQueue::containsKey(key))
	{
		return;
	}

	//if 0 or 1 items in queue, do nothing
	if (itemCount <= 1)
	{
		return;
	}

	//key is already head pointer, nothing to change
	if (headPtr->getItem().getKey().compare(key) == 0)
	{
		return;
	}

	Node * curPtr = headPtr->getNext();
	Node * prevPtr = headPtr;
	Node * keyPtr = nullptr;
	//find the pointer to the key
	for (int i = 0; i < itemCount; i++)
	{
		if (curPtr->getItem().getKey() == key)
		{
			keyPtr = curPtr;
			break;
		}
		else
		{
			prevPtr = prevPtr->getNext();
			curPtr = curPtr->getNext();
		}
	}
	int keyPriority = keyPtr->getItem().getPriority();
	//if there are no duplicates of the priority
	//the position does not need to be changed
	if (WorkQueue::getNumWorkItems(keyPriority) <= 1)
	{
		return;
	}
	prevPtr->setNext(curPtr->getNext());
	curPtr = headPtr->getNext();
	prevPtr = headPtr;

	//if the key should be moved to the head
	if (prevPtr->getItem().getPriority() == keyPriority)
	{
		keyPtr->setNext(headPtr);
		headPtr = keyPtr;
	}
	for (int i = 0; i < itemCount - 2; i++)
	{
		if (curPtr->getItem().getPriority() == keyPriority)
		{
			prevPtr->setNext(keyPtr);
			keyPtr->setNext(curPtr);
			break;
		}
		curPtr = curPtr->getNext();
		prevPtr = prevPtr->getNext();
	}
}

int WorkQueue::getNumWorkItems() const
{
	return itemCount;
}

///////////////////////////////////////////////
// Traverses the list and whenever a workItem
// found with the same priority as the priority
// count is increased.  Count is then returned.
///////////////////////////////////////////////
int WorkQueue::getNumWorkItems(int priority) const
{
	int count = 0;
	Node * curPtr = headPtr;
	while (curPtr->getNext())
	{
		if (priority == curPtr->getItem().getPriority())
		{
			count++;
		}
		curPtr = curPtr->getNext();
	}

	if (curPtr->getItem().getPriority() == priority)
	{
		count++;
	}
	return count;
}

////////////////////////////////////////////////
// Traverses list and finds WorkItem with the 
// same key as the key specified. Deletes item.
////////////////////////////////////////////////
void WorkQueue::deleteWorkItem(string key)
{
	if (!WorkQueue::containsKey(key))
	{
		return;
	}
	Node * prevPtr = headPtr;
	Node * crtPtr = headPtr->getNext();
	Node * discardPtr;

	if (headPtr->getItem().getKey() == key)
	{
		discardPtr = headPtr;
		headPtr = headPtr->getNext();
		delete discardPtr;
		discardPtr = nullptr;
	}
	else
	{
		while (crtPtr)
		{
			if (key == crtPtr->getItem().getKey())
			{
				discardPtr = crtPtr;
				crtPtr = crtPtr->getNext();
				prevPtr->setNext(crtPtr);
				discardPtr->setNext(nullptr);
				delete discardPtr;
				discardPtr = nullptr;
				itemCount--;
				break;
			}
			crtPtr = crtPtr->getNext();
			prevPtr = prevPtr->getNext();
		}
	}
}

///////////////////////////////////////
// Traverses list and deletes all items
// in the list.
///////////////////////////////////////
void WorkQueue::deleteAllWorkItems()
{
	Node * prevPtr = headPtr;
	Node * discardPtr;

	for (int i = 0; i < itemCount; i++)
	{
		discardPtr = prevPtr;
		prevPtr = prevPtr->getNext();
		discardPtr->setNext(nullptr);
		delete discardPtr;
	}
	headPtr = nullptr;
	prevPtr = nullptr;
	discardPtr = nullptr;
	itemCount = 0;
}




