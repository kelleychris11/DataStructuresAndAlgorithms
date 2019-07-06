#include <cassert>

/////////////////////////////////////////
//LLStack Implementation
///////////////////////////////////////

//Copy Constructor - Utilizes overriden operator = method
//to create copy.
template<class Type>
LLStack<Type>::LLStack(const LLStack<Type> & rhs)
{
	*this = rhs;

}

//Overriden operator = copies rhs to lhs. Traverse through rhs stack
//and copies item values in newly created nodes for the lhs stack
template<class Type>
LLStack<Type>& LLStack<Type>::operator = (const LLStack<Type>& rhs)
{
		this->itemCount = rhs.itemCount;

    //if rhs headPtr is null, there is nothing in list, so return
    //lhs list with nothing     
	if(rhs.headPtr == nullptr)
	{
		this->headPtr = nullptr;
        return *this;
	}    

	this->headPtr = new Node<Type>(rhs.headPtr->getItem());
	Node<Type> * rhsCurPtr = rhs.headPtr->getNext();
	Node<Type> * lhsPtr = this->headPtr;

    //while rhsCurPtr is not null, traverse through the stack and copy
    //each item in rhs stack into a newly created node linked to the
    //lhs stack
	while (rhsCurPtr)
	{
		Node<Type> * copyNodePtr = new Node<Type>(rhsCurPtr->getItem());
		lhsPtr->setNext(copyNodePtr);
		lhsPtr = lhsPtr->getNext();
		rhsCurPtr = rhsCurPtr->getNext();
	}
	lhsPtr->setNext(nullptr);

	return *this;
}

template<class Type>
LLStack<Type>::~LLStack()
{
}

//pushes new item on to the stack by creating a new
//head node and assigning the next field as as the old 
//head node
template<class Type>
void LLStack<Type>::push(const Type & newItem)
{
	Node<Type> * newNode = new Node<Type>(newItem);
	newNode->setNext(headPtr);
	headPtr = newNode;
	itemCount++;
}

//removes the top item from the stack by deleting the head node
template<class Type>
void LLStack<Type>::pop()
{
    //if the list is empty, return
	if (empty())
	{
		return;
	}

    //if the list only has one, delete the head node
	else if (itemCount == 1)
	{
		delete headPtr;
		headPtr = nullptr;
		itemCount--;
	}

    //for all other cases, delete the head node and assign
    //the new head node as the next node in the link
	else
	{
		Node<Type> * discardPtr = headPtr;
		headPtr = headPtr->getNext();
		delete discardPtr;
		discardPtr = nullptr;
		itemCount--;
	}
}

//return the value of the item held in the head node
template<class Type>
Type&  LLStack<Type>::top() const throw(std::logic_error)
{

	if (headPtr == nullptr)
	{
		throw (std::logic_error("No items in the stack"));
	}
	else
	{	
		return headPtr->item;	
	}
}

//if itemCount is empty, return true
template<class Type>
bool LLStack<Type>::empty() const
{
	if (itemCount == 0)
	{
		return true;
	}
	return false;
}


template<class Type>
int LLStack<Type>::size() const
{
	return itemCount;
}

///////////////////////////////////////////////////////////
// Node Implementation
//////////////////////////////////////////////////////////


template<class Type>
Node<Type>::Node(const Type thisItem)
{
	item = thisItem;
}

template<class Type>
void Node<Type>::setNext(Node * NextNode)
{
	nextPtr = NextNode;
}

template<class Type>
Node<Type>* Node<Type>::getNext() const
{
	return nextPtr;
}

template<class Type>
void Node<Type>::setItem(const Type anItem)
{
	item = anItem;
}

template<class Type>
Type Node<Type>::getItem() const
{
	return item;
}

