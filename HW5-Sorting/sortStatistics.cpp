#include "arrayList.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/////////////////////////////////////
// Author: Chris Kelley
// CSS 342 - Project 5
// Time: 20 hours
////////////////////////////////////

//method prototyping----------------------------------------------
void selectionSort(ArrayList<int>& arrayList);
int getLargestIndex(ArrayList<int>& arrayList, int unsortedSize);
void merge(ArrayList<int>& arrayList, int first, int mid, int last);
void mergeSort(ArrayList<int>& arrayList, int first, int last);
void quickSort(ArrayList<int>& arrayList, int first, int last);
int partition(ArrayList<int>& arrayList, int first, int last);
void getStatistics(ArrayList<int>& arrayList, ArrayStats& stats);
void printStats(ArrayStats& selectionStats, ArrayStats& mergeStats,
	ArrayStats& quickStats);
//-----------------------------------------------------------------

//Main method, receives array input from file and calls
//selection, merge, and quick sorting methods.
//Registers statistics about each sorting method and
//prints to the console
int main(int argc, char* argv[])
{
	string fileName;
	fstream inFile;
	bool printArrayNums = false;
	cout << "Welcome to Chris Kelley's wonderful world of sorting."
		 << endl << endl;
	if(argc > 1)
	{
		fileName = argv[1];

		//check to see if -d was entered on the command line
		//if so print out the numbers in each number set after
		//sorting with each sorting method(quick, merge, selection)
		if(argc == 3)
		{
			const string printCmd = "-d";
			string cmd1 = argv[1];
			string cmd2 = argv[2];
			if(cmd1.compare(printCmd) == 0)
			{
				printArrayNums = true;
				fileName = argv[2];
			}
			if(cmd2.compare(printCmd) == 0)
			{
				printArrayNums = true;
			}
		}
	}
	//get filename from the command line
	else
	{
		cout << "Enter a file name to enter the  magical "
			<< "realm of sorting algorithms: " << endl;
		cin >> fileName;
	}

	inFile.open(fileName);

	//check if filestream is valid
	if(!inFile)
	{
		cout << "Sorry, that's not a valid file name" << endl;
		return 0;
	}
	ArrayList<int> theArray(100);
	int num;
	while(inFile >> num)
	{
		theArray.append(num);
	}
	ArrayStats mergeStats;
	ArrayStats selectionStats;
	ArrayStats quickStats;
	
	
	//create copies of the array so that each sort method
	//gets an unsorted array
	ArrayList<int> selectionArray(theArray.getSize());
	selectionArray = theArray;
	ArrayList<int> mergeArray(theArray.getSize());
	mergeArray = theArray;
	ArrayList<int> quickArray(theArray.getSize());
	quickArray = theArray;

	//clear stats before sorting
	theArray.clearStatistics();

	cout << "Filename: " << fileName << endl;
	cout << "Number of Items: " << theArray.getSize() << endl;

	//sort array using selection sort. If -d was entered on the
	//command line, print numbers in array after the sort
	selectionSort(selectionArray);
	if(printArrayNums)
	{
		cout << "Selection Sort Results: " << endl;
		selectionArray.printArray();
		cout << endl;
	}

	getStatistics(selectionArray, selectionStats);
	selectionArray.clearStatistics();


	//sort array using merge sort. If -d was entered on the
	//command line, print numbers in array after the sort
	mergeSort(mergeArray, 0, mergeArray.getSize() - 1);
	if(printArrayNums)
	{
		cout << "Merge Sort Results: " << endl;
		mergeArray.printArray();
		cout << endl;
	}
	getStatistics(mergeArray, mergeStats);
	mergeArray.clearStatistics();

	//sort array using quick sort. If -d was entered on the
	//command line, print numbers in array after the sort
	quickSort(quickArray, 0, quickArray.getSize() - 1);
	if(printArrayNums)
	{
		cout << "Quick Sort Results: " << endl;
		quickArray.printArray();
		cout << endl;
	}
	getStatistics(quickArray, quickStats);
	printStats(selectionStats, mergeStats, quickStats);
}

//return statistics for the particular sort method
void getStatistics(ArrayList<int>& arrayList, ArrayStats& stats)
{
	stats.countAppend = arrayList.getNumAppends();
	stats.countAccess = arrayList.getNumAccess();
	stats.countInsert = arrayList.getNumInsertAt();
	stats.countRemove = arrayList.getNumRemove();
	stats.countSwap = arrayList.getNumSwap();
}

//print the statistics of each sort method
void printStats(ArrayStats& selectionStats, ArrayStats& mergeStats,
	ArrayStats& quickStats)
{

	printf("NumAccess:\tSelection = %-10d Merge = %-10d Quick = %-10d\n",
		selectionStats.countAccess, mergeStats.countAccess,
		quickStats.countAccess);

	printf("NumSwap:\tSelection = %-10d Merge = %-10d Quick = %-10d\n",
		selectionStats.countSwap, mergeStats.countSwap, 
		quickStats.countSwap);

	printf("NumRemove:\tSelection = %-10d Merge = %-10d Quick = %-10d\n",
		selectionStats.countRemove, mergeStats.countRemove, 
		quickStats.countRemove);

	printf("NumInsertAt:\tSelection = %-10d Merge = %-10d Quick = %-10d\n",
		selectionStats.countInsert, mergeStats.countInsert,
		quickStats.countInsert);

	printf("NumAppend:\tSelection = %-10d Merge = %-10d Quick = %-10d\n",
		selectionStats.countAppend, mergeStats.countAppend,
		quickStats.countAppend);
}

//sort an array using selection sort
void selectionSort(ArrayList<int>& arrayList)
{
	for(int i = arrayList.getSize() - 1; i > 0; i--)
	{
		arrayList.swap(getLargestIndex(arrayList, i), i);
	}
}

//helper method for selection sort
//returns the index of the largest value
int getLargestIndex(ArrayList<int>& arrayList, int unsortedSize)
{
	int indexOfMax = 0;
	for(int i = 0; i <= unsortedSize; i++)
	{
		if(arrayList[i] > arrayList[indexOfMax])
		{
			indexOfMax = i;
		}
	}
	return indexOfMax;
}

//sorts an array with merge sort
void mergeSort(ArrayList<int>& arrayList, int first, int last)
{
	if(first < last)
	{
		int mid = first + (last - first) / 2;
		mergeSort(arrayList, first, mid);
		mergeSort(arrayList, mid + 1, last);
		merge(arrayList, first, mid, last);
	}
}

//helper method for mergeSort
//merges two sorted arrays
void merge(ArrayList<int>& arrayList, int first, int mid, int last)
{
	ArrayList<int> tempArray(arrayList.getSize());
	tempArray = arrayList;


	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;

	//sort the array for the first n elements of the array
	//(where n = the lesser of last1 or last2)
	while(first1 <= last1 && first2 <= last2)
	{
		if(arrayList[first1] <= arrayList[first2])
		{
			tempArray[index] = arrayList[first1];
			first1++;
		}
		else
		{
			tempArray[index] = arrayList[first2];
			first2++;
		}
		index++;
	}
	//if there are items remaining in the array from first1 to last1
	//add the remaining items to the end of tempArray
	while (first1 <= last1)
	{
		tempArray[index] = arrayList[first1];
		first1++;
		index++;
	}

	//if there are items remaining in the array from first1 to last1
	//add the remaining items to the end of tempArray
	while(first2 <= last2)
	{
		tempArray[index] = arrayList[first2];
		first2++;
		index++;
	}

	//copy the temporary array into the original array
	for(int i = first; i <= last; i++)
	{
		arrayList[i] = tempArray[i];
	}
}

//sort an array using quickSort
void quickSort(ArrayList<int>& arrayList, int first, int last)
{
	if(first < last)
	{
		int partition1 = partition(arrayList, first, last);
		quickSort(arrayList, first, partition1 - 1);
		quickSort(arrayList, partition1 + 1, last);
	}
}

//helper method for quick sort
//creates a partition to be sorted
int partition(ArrayList<int>& arrayList, int first, int last)
{
	int pivot = arrayList[last];
	int pivotIndex = last;
	int index = first;
	int indexFromLeft = first;
	int indexFromRight = last - 1;
	bool finished = false;
	while(!finished)
	{
		while(arrayList[indexFromLeft] < pivot && indexFromLeft < arrayList.getSize())
		{
			indexFromLeft++;
		}
		while(arrayList[indexFromRight] > pivot && indexFromRight > 0)
		{
			indexFromRight--;
		}

		if(indexFromLeft < indexFromRight)
		{
			arrayList.swap(indexFromLeft, indexFromRight);
			indexFromLeft++;
			indexFromRight--;
		}
		else
		{
			finished = true;
		}
	}
	arrayList.swap(pivotIndex, indexFromLeft);
	pivotIndex = indexFromLeft;
	return pivotIndex;
}





