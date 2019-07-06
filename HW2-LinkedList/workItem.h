#ifndef WORKITEM_H
#define WORKITEM_H
#include <string>

/////////////////////////
//  Chris Kelley
//  CSS 342 - Project 2
//  25 hours
//  Cygwin
/////////////////////////

////////////////////////////////
// WorkItem Class
//		Contains priority number
//		of WorkItem and a unique
//		string ID
////////////////////////////////

class WorkItem
{
	friend class WorkQueue;

private:
	int priority;
	std::string key;


public:

	////////////////////////
	//Default Constructor
	///////////////////////
	WorkItem();

	//////////////
	//Constructer
	//////////////
	WorkItem(int thisPriority, const std::string& thisKey) :
		priority(thisPriority), key(thisKey)
	{
	}

	////////////////
	//Destructor
	//////////////
	virtual ~WorkItem();

	///////////////////////
	//ShallowCopy Constructor
	//////////////////////
	WorkItem(const WorkItem&);

	////////////////////////
	//DeepCopy Constructor
	///////////////////////
	WorkItem& operator = (const WorkItem& rhs);

	///////////////////////
	//returns priority
	////////////////////
	int getPriority() const;

	/////////////////////
	//returns ID key
	////////////////////
	const std::string& getKey() const;
};

//////////////////////////////////////////////
// Node Class
//		For use in linked list.  Each node
//		contains a pointer to the next next
//		Node in the list and a WorkItem object
//////////////////////////////////////////////
class Node
{
private:
	WorkItem item;
	Node * next;;
	
public:
	///////////////
	//Constructor
	//////////////
	Node(const WorkItem& thisItem) : item(thisItem), next(nullptr)
	{
	}

	////////////////////////
	//Overloaded Constructor
	////////////////////////
	Node(const WorkItem& newItem, Node * nextNodePtr);

	//////////////
	//Destructor
	//////////////
	virtual ~Node();

	///////////////
	//Set next node
	///////////////
	void setNext(Node * nextNodePtr);

	////////////////
	//Get next node
	////////////////
	Node * getNext() const;

	//////////////////
	//Get item in node
	//////////////////
	WorkItem getItem() const;

	///////////////////
	//Set item in node
	//////////////////
	bool setItem(const WorkItem& newItem);


};

#endif
