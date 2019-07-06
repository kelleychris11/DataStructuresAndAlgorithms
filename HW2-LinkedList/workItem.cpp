#include "workItem.h"
using namespace std;

/////////////////////////
//  Chris Kelley
//  CSS 342 - Project 2
//  25 hours
//  Cygwin
/////////////////////////


////////////////////////////
//WorkItem implementation
///////////////////////////

WorkItem::WorkItem()
{
}


WorkItem::~WorkItem()
{
}

WorkItem::WorkItem(const WorkItem& rhs)
{
	priority = rhs.priority;
	key = rhs.key;
}

WorkItem& WorkItem::operator = (const WorkItem& rhs)
{
	string * rhsString = new string(rhs.key);
	this->key = *rhsString;
	this->priority = rhs.priority;
	return *this;
}

int WorkItem::getPriority()const
{
	return priority;
}

const string& WorkItem::getKey() const
{
	return key;
}


///////////////////////
//Node implementation
///////////////////////

Node::Node(const WorkItem& thisItem, Node * nextNodePtr)
{
	item = thisItem;
	next = nextNodePtr;
}

Node::~Node()
{
}

void Node::setNext(Node * nextNodePtr)
{
	next = nextNodePtr;
}

Node * Node::getNext() const
{
	return next;
}

WorkItem Node::getItem() const
{
	return item;
}

bool Node::setItem(const WorkItem& newItem)
{
	item = newItem;
	if (item.getKey() == newItem.getKey())
	{
		return true;
	}
	else
	{
		return false;
	}
}



