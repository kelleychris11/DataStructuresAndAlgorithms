#include <iostream>
#include <string>
#include "map.h"
using namespace std;

/////////////////////////////
// Chris Kelley
// CSS 342
// Project 4
// 20 Hours
/////////////////////////////

/////////////////////////////
//Room Implementation
//////////////////////////////

char Room::getRoomType() const
{
	return roomType;
}

int Room::getRow() const
{
	return row;
}

int Room::getColumn() const
{
	return col;
}


void Room::setHasVisited(const bool thisHasVisited)
{
	hasVisited = thisHasVisited;
}

bool Room::getHasVisited() const
{
	return hasVisited;
}

/////////////////////////////////////////////////////
//Map implementation
/////////////////////////////////////////////////

//Check the rooms adjacent to curRoom(the current room)
//to see if one has a path that can be taken
Room& Map::getNextRoom(Room &curRoom)
{
	//check east for path
	if((roomList[curRoom.getRow()][curRoom.getColumn() + 1].getRoomType() 
                != '#'&& !roomList[curRoom.getRow()]
                [curRoom.getColumn() + 1].hasVisited) &&
		        curRoom.getColumn() + 1 < getColumns())
	{
		return roomList[curRoom.getRow() ][curRoom.getColumn() + 1];
	}
	//check west for path
	if((roomList[curRoom.getRow()][curRoom.getColumn() - 1].getRoomType() 
                != '#' && !roomList[curRoom.getRow()]
                [curRoom.getColumn() - 1].hasVisited) &&
		        curRoom.getColumn() - 1 >= 0)
	{
		return roomList[curRoom.getRow()][curRoom.getColumn() - 1];
	}
	//check north for path
	if((roomList[curRoom.getRow() - 1][curRoom.getColumn()].getRoomType() 
                != '#' && !roomList[curRoom.getRow() - 1]
                [curRoom.getColumn()].hasVisited) &&
		        curRoom.getRow() - 1 >= 0)
	{
		return roomList[curRoom.getRow() - 1][curRoom.getColumn()];
	}
	//check south for path
	if (roomList[curRoom.getRow() + 1][curRoom.getColumn()].getRoomType() 
                != '#' && !roomList[curRoom.getRow() + 1]
                [curRoom.getColumn()].hasVisited &&
		        curRoom.getColumn() + 1 < getColumns())
	{
		return roomList[curRoom.getRow() + 1][curRoom.getColumn()];
	}

		//if no path found, return generic room with 'x' type
		Room * noRoom = new Room(NO_ROOM, 0, 0);
		return *noRoom;
}

void Map::setNextRoom(Room & thisRoom, int row, int col)
{
	roomList[row][col] = thisRoom;
}

Room& Map::getRoom(int row, int col)
{
	return roomList[row][col];
}

//set next room on the exitPath stack
void Map::setNextExitRoom(Room& currentRoom)
{
	exitPath.push(roomList[currentRoom.getRow()][currentRoom.getColumn()]);
}

//get the room on the top of the exitPath stack
Room& Map::getNextExitRoom() const
{

	return exitPath.top();
}

//remove the top of the exitPath stack
void Map::removeExitRoom()
{
	exitPath.pop();
	pathSize--;
}

int Map::getPathSize() const
{
	return pathSize;
}

int Map::getRows() const
{
	return rows;
}
int Map::getColumns() const
{
	return columns;
}
void Map::setRows(const int thisRows)
{
	rows = thisRows;
}
void Map::setColumns(const int thisColumns)
{
	columns = thisColumns;
}

//recursively checks isPath for the path from the start
//to the exit (indicated by Room type '#')
bool Map::isPath(Room &currentRoom)
{
	roomList[currentRoom.getRow()][currentRoom.getColumn()].hasVisited = true;
	//thisTraveler.setCurrentRoom(currentRoom);

	//check if current room is exit room
	if (currentRoom.getRoomType() == 'o')
	{
		//exit found
		cout << "Exit found at: (" << currentRoom.getRow() << ", " 
		<< currentRoom.getColumn() << ")" << endl << endl;

		//put room on exitPath stack
		setNextExitRoom(currentRoom);
		pathSize++;
		return true;
	}

	Room nextRoom = getNextRoom(currentRoom);

	//for getNext room, if there are no rooms to go
	//return generic room with type 'x'
	while(nextRoom.getRoomType() != NO_ROOM)
	{
		//recursively check nextRoom for path
		if(isPath(nextRoom))
		{
			setNextExitRoom(currentRoom);
			pathSize++;
			return true;
		}
		else
		{
			//check other rooms adjacent to currentRoom
			//for a path to exit
			nextRoom = getNextRoom(currentRoom);
		}
	}
	return false;
}


