#ifndef LLSTACK_H
#define LLSTACK_H 
#include <stdexcept>

template<class Type>
class Node;


///////////////////////////
// Chris Kelley
// CSS 342
// 20 Hours
/////////////////////////


/////////////////////////
// Class LLStack
//		Stack ADT with Linked
//		List structure
/////////////////////////////
template <class Type>
class LLStack

{
private: 
	Node<Type> * headPtr = nullptr;
	int itemCount = 0;

public:
    //Default Constructor
	LLStack() {}

    //Copy Constructor
	LLStack(const LLStack<Type>&);

    //Override operator = for class
	LLStack& operator = (const LLStack<Type>& rhs);

    //Destructor
	virtual ~LLStack();

    //Pushes parameter on to the top of the stack
	void push(const Type& newItem);

    //Removes the item on the top of the stack
	void pop();

    //Allows client to look at the top item of 
    //the stack
	Type & top() const throw(std::logic_error);

    //Checks to see if the stack is empty
	bool empty()const;

    //returns the number of items in the stack
	int size() const;

};

//////////////////////////
// Node Class
//		Building block of
//		Linked List
/////////////////////////


template<class Type>
class Node
{
	friend class LLStack<Type>;
public:
    //Default constructor
	Node() {}

    //Constructor with item parameter
	Node(const Type thisItem);

    //Sets the next pointer contained in the node
    //to the next node in the linked list
	void setNext(Node * NextNode);

    //returns the address of the next node in the
    //linked list
	Node * getNext()const;

    //sets the item contained in the node
	void setItem(const Type anItem);

    //returns the item contained in the node
	Type getItem() const;

private:

	Node<Type> * nextPtr = nullptr;
	Type item;
};
#endif
#include "llStack.ipp"
