#ifndef MAP_H
#define MAP_H
#include "llStack.h"
const int MAX_MAP_SIZE = 50;
const char NO_ROOM = 'x';

/////////////////////////////
// Chris Kelley
// CSS 342
// Project 4
// 20 Hours
/////////////////////////////

///////////////////////////////////
// Room class
//		A class used to represent
//		a room in a Maze class.
//		Each room contains its
//		location in the maze
//		and whether it has already
//		been visited.
//////////////////////////////////////
class Room
{
	friend class Map;
private:
	bool hasVisited;
	char roomType;
	int col;
	int row;

public:
	//Default constructor
	Room() {}
	
	//Complete constructor
	Room(const char &thisRoomType, const int thisRow, const int thisCol) : 
		roomType(thisRoomType),  row(thisRow), col(thisCol), 
        hasVisited(false) {}
	
	//get the type of the room(wall, exit, open)
	char getRoomType() const;

	//get the row of a Map that room is
	int getRow() const;

	//get the column of a Map that room is
	int getColumn() const;

	//set if a room has been visited
	void setHasVisited(const bool thisHasVisited);

	//return true if room has already been visited
	bool getHasVisited() const;
};

////////////////////////////////////////////
// Map class
//		Contains an array of Rooms that
//		make up a maze. The maze has a 
//		start and an exit and the Map class
//		finds the exit from the start point
/////////////////////////////////////////////

class Map
{
private:
	int rows;
	int columns;
	Room roomList[MAX_MAP_SIZE][MAX_MAP_SIZE];
	LLStack<Room> exitPath;
	int pathSize = 0;

public:
	//default constructor
	Map() {}

	//complete constructor
	Map(const int thisRows, const int thisColumns) : 
		rows(thisRows), columns(thisColumns){}

	//get the next room to check for a path
	//to the exit of the maze
	Room& getNextRoom(Room& currentRoom);

	//sets the next room on the map
	void setNextRoom(Room& thisRoom, int row, int col);

	//checks for a path from the start point of the map
	//to the exit of the map. If found, returns true.
	bool isPath(Room& currentRoom);

	//get room at indicated row and column
	Room& getRoom(int row, int col);

	//When a path to the exit is found, sets the 
	//room on the path on the LLStack (exitPath)
	void setNextExitRoom(Room& currentRoom);

	//gets the room that is on the top of the 
	//exitPath LLStack. 
	Room& getNextExitRoom() const;

	//Removes the top room from the exitPath
	//LLStack.
	void removeExitRoom();

	//get the size of exitPath LLStack
	int getPathSize() const;

	//get the number of rows of the Map
	int getRows() const;

	//get the number of columns of the Map
	int getColumns() const;

	//set the number of rows of the Map
	void setRows(const int thisRows);

	//set the number of columns of the Map
	void setColumns(const int thisColumns);
};

#endif

