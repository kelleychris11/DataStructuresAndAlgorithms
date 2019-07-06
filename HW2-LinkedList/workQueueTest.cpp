#include "workQueue.h"
#include <iostream>
#include <string>
using namespace std;

WorkQueue& initializeList();
void testCopyConstructor();
void testCopyOperator();
void testAddWorkItem();
void testNextWorkItem();
void testHasWorkItem();
void testContainsKey();
void testBumpWorkItem();
void testGetNumWorkItems();
void testGetNumWorkItemsPriority();
void testDeleteWorkItem();
void testDeleteAllWorkItems();
void testException();


int main()
{
	testCopyConstructor();
	testCopyConstructor();
	testAddWorkItem();
	testNextWorkItem();
	testHasWorkItem();
	testContainsKey();
	testBumpWorkItem();
	testGetNumWorkItems();
	testGetNumWorkItemsPriority();
	testDeleteWorkItem();
	testDeleteAllWorkItems();
	testException();
}

//Initial list with test data
WorkQueue& initializeList()
{
	WorkQueue * filledQueue = new WorkQueue();
	WorkItem item1(1, "A");
	WorkItem item2(3, "B");
	WorkItem item3(5, "C");
	WorkItem item4(2, "D");
	WorkItem item5(1, "E");
	WorkItem item6(3, "F");

	filledQueue->addWorkItem(item1);
	filledQueue->addWorkItem(item2);
	filledQueue->addWorkItem(item3);
	filledQueue->addWorkItem(item4);
	filledQueue->addWorkItem(item5);
	filledQueue->addWorkItem(item6);

	return *(filledQueue);
}
//Test copy constructor
void testCopyConstructor()
{
	WorkQueue queue1 = initializeList();
	WorkQueue * queue2 = new WorkQueue(queue1);
	if(queue2->containsKey("E"))
	{
		cout << "testCopyConstructor: Passed" << endl;
	}

	delete queue2;
	queue2 = nullptr;
}

//test copy operator
void testCopyOperator ()
{
	WorkQueue queue1 = initializeList();
	WorkQueue queue2 = queue1;
	if (queue2.containsKey("E"))
	{
		cout << "testCopyOperator: Passed" << endl;
	}
}

//Test Add Workitem
void testAddWorkItem()
{
	WorkQueue queue1;
	WorkItem item1(3, "G");
	WorkItem item2(4, "H");
	queue1.addWorkItem(item1);
	queue1.addWorkItem(item2);
	if(queue1.containsKey("G"))
	{
		cout << "testAddWorkItem: Passed" << endl;
	}
}

//test nextWorkItem
void testNextWorkItem()
{
	WorkQueue queue1 = initializeList();
	if(queue1.nextWorkItem(1).getKey().compare("A") == 0)
	{
		cout << "testNextWorkItem: Passed" << endl;
	}

}

//test contains key
void testContainsKey()
{
	WorkQueue queue1 = initializeList();
	if(queue1.containsKey("A"))
	{
		cout << "testContainsKey: Passed" << endl;
	}
}

//test hasWorkItem
void testHasWorkItem()
{
	WorkQueue queue1 = initializeList();
	if(queue1.hasWorkItem(2))
	{
		cout << "testHasWorkItem: Passed" << endl;
	}
}

//test bumpWorkItem
void testBumpWorkItem()
{
	WorkQueue queue1 = initializeList();
	queue1.bumpWorkItem("F");
	if(queue1.nextWorkItem(3).getKey().compare("F") == 0)
	{
		cout << "testBumpWorkItem: Passed" << endl;
	}
}

//Test getNumWorkItems
void testGetNumWorkItems()
{
	WorkQueue queue1 = initializeList();
	if(queue1.getNumWorkItems() == 6)
	{
		cout << "testGetNumWorkItems: Passed" << endl;
	}
}

//Test getNumWorkItems(int priority)
void testGetNumWorkItemsPriority()
{
	WorkQueue queue1 = initializeList();
	if(queue1.getNumWorkItems(3) == 2)
	{
		cout << "testGetNumWorkItems(priority): Passed" << endl;
	}
}

//Test deleteWorkItem
void testDeleteWorkItem()
{
	WorkQueue queue1 = initializeList();
	queue1.deleteWorkItem("B");
	if(queue1.getNumWorkItems(3) == 1)
	{
		cout << "testDeleteWorkItem: Passed" << endl;
	}
}

//test delete all work items
void testDeleteAllWorkItems()
{
	WorkQueue queue1 = initializeList();
	queue1.deleteAllWorkItems();
	if(queue1.getNumWorkItems() == 0)
	{
		cout << "testDeleteAllWorkItems: Passed" << endl;
	}
}

//test exception for nextworkitem
void testException()
{
	WorkQueue queue1;

	try
	{
		queue1.nextWorkItem(2);
	}
	catch (logic_error e)
	{
		cout << "testException: Passed";
	}
}










