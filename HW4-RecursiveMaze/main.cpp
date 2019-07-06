#include <iostream>
#include <string>
#include "map.h"
#include <fstream>
using namespace std;

void printExitPath(bool path, Map &newMap, char mapArray[][MAX_MAP_SIZE]);

/////////////////////////////
// Chris Kelley
// CSS 342
// Project 4
// 20 Hours
/////////////////////////////

//main method, inputs file data to Map array of Rooms
int main(int argc, char ** argv)
{
	string fileName;

	//if initialized with file, get filename
	if(argc > 1)
	{
		fileName = argv[1];
	}
	//get filename from console
	else
	{
		cout << "Enter a file name: " << endl;
		cin >> fileName;
	}
	ifstream inFile;
	inFile.open(fileName);
	if(!inFile)
	{
		cout << "ERROR: Failed to open File" << endl;
		cout << "Goodbye!" << endl;
		return 0;
	}
	cout << "Reading from: " << fileName << endl << endl;

	//read first line of file into variables
	int mapRows;
	int mapColumns;
	int startRow;
	int startColumn;
	inFile >> mapRows;
	inFile >> mapColumns;
	inFile >> startRow;
	inFile >> startColumn;

	char mapArray[MAX_MAP_SIZE][MAX_MAP_SIZE];
	string stream;
	string firstLine;
	inFile >> firstLine;
	int rows = 0;
	int columns = firstLine.length();

	//read file into mapArray
	while(getline(inFile, stream))
	{
		for(int i = 0; i < columns; i++)
		{
			if(rows == 0)
			{
				mapArray[rows][i] = firstLine[i];
			}
			else
			{
				mapArray[rows][i] = stream[i];
			}
			
		}
		rows++;
	}
	if(columns > mapColumns || rows > mapRows)
	{
		cout << "Sorry, that's a bad map." << endl;
		return 0;
	}

	mapRows = rows;
	mapColumns = columns;
	Map newMap(mapRows, mapColumns);
	
	//read mapArray(array of chars) to newMap
	//(array of Rooms)
	for(int i = 0; i < mapRows; i++)
	{
		for(int j = 0; j < mapColumns; j++)
		{
			Room newRoom(mapArray[i][j], i, j);
			newMap.setNextRoom(newRoom,i, j);
		}
	}

	//check starting point is valid
	if((newMap.getRoom(startRow, startColumn).getRoomType() != ' ')
		|| (startRow > mapRows) || startColumn > mapColumns)
	{
		cout << "Sorry, that's a bad map." << endl;
		return 0;
	}

	//recursive function to find path in maze
	bool path = newMap.isPath(newMap.getRoom(startRow, startColumn));
	printExitPath(path, newMap, mapArray);
}

void printExitPath(bool path, Map &newMap, char mapArray[][MAX_MAP_SIZE])
{
	int count = 0;
	//if path returned true, there is a path to print
	if (path)
	{
		while(newMap.getPathSize() != 0)
		{
			count = 0;
			//limits room coordinates printed to 8 per line
			while(count < 8 && newMap.getPathSize() != 0)
			{
				Room pathRoom = newMap.getNextExitRoom();
				mapArray[pathRoom.getRow()][pathRoom.getColumn()] = '+';
				newMap.removeExitRoom();
				if(newMap.getPathSize() == 0)
				{
					cout << "[" << pathRoom.getRow() << ", " 
                        << pathRoom.getColumn()
						<< "]";
				}
				else
				{
					cout << "[" << pathRoom.getRow() << ", " 
                        << pathRoom.getColumn()
						<< "]->";
				}
				count++;
			}
			cout << endl;
		}
		cout << endl;

		//prints new map with '+' on each room that is
		//on the path from start to exit
		for (int i = 0; i < newMap.getRows(); i++)
		{
			for (int j = 0; j < newMap.getColumns(); j++)
			{
				cout << mapArray[i][j];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No exit-Sarte was right" << endl;
	}
}


