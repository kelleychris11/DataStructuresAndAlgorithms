#include "map.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/////////////////////////////////////
//Author: Chris Kelley
//CSS 342
//Project #6
//Time: 15 hours
//////////////////////////////////////

//////////////////////////////////////////
// Implement Room
///////////////////////////////////////////

Room::Room(const int thisRoomNum)
{
	x = thisRoomNum / ARRAY_SIZE;
	y = thisRoomNum % ARRAY_SIZE;
	roomNum = thisRoomNum;
}

void Room::setRoomNum(const int newRoomNum)
{
	roomNum = newRoomNum;
}

int Room::getRoomNum() const
{
	return roomNum;
}

void Room::setHasWumpus(const bool newVal)
{
	hasWumpus = newVal;
}

void Room::setHasBat(const bool newVal)
{
	hasBat = newVal;
}

void Room::setHasPit(const bool newVal)
{
	hasPit = newVal;
}

bool Room::getHasWumpus() const
{
	return hasWumpus;
}

bool Room::getHasBat() const
{
	return hasBat;
}
bool Room::getHasPit() const
{
	return hasPit;
}

bool Room::getHasCharacter() const
{
	return hasCharacter;
}
void Room::setHasCharacter(const bool newVal)
{
	hasCharacter = newVal;
}

void Room::setHasFootsteps(bool newVal)
{
	hasFootsteps = newVal;
}

bool Room::getHasFootsteps() const
{
	return hasFootsteps;
}

//Identifies what is contained in the specified room
//and prints information to the console based on those
//contents.
void Map::doEvent(Room& curRoom)
{
	//check for wumpus
	if (curRoom.getHasWumpus())
	{
		cout << "Wumpus!!!!" << endl;
		cout << "You die a slow, horrifying death" << endl;
		isDead = true;
	}
	//check for a pit
	else if (curRoom.getHasPit())
	{
		cout << "You fell in a pit!!" << endl;
		cout << "You are still alive, but your limbs are broken" << endl;
		cout << "You cannot get out of the pit!!" << endl;
		cout << "You slowly starve to death." << endl;
		isDead = true;
	}
	//check for a bat
	else if (curRoom.getHasBat())
	{
		cout << "A bat picks you up!" << endl;
		cout << "You feel stressed out as it carries you through the dungeon";
		cout << endl;
		batTeleport(curRoom);
		mapArray[curRoom.getX()][curRoom.getY()].setHasFootsteps(true);

	}
	//if room does not have a bat, pit or Wumpus
	else
	{
		cout << "You see a number on the floor." << endl;
		cout << "It is " << curRoom.getRoomNum() << "." << endl;

		if (curRoom.getHasFootsteps())
		{
			cout << endl << "You see footsteps on the floor...";
			cout << "you've been here before." << endl;
		}
		mapArray[curRoom.getX()][curRoom.getY()].setHasFootsteps(true);
	}
}

int Room::getX() const
{
	return roomNum / ARRAY_SIZE;
}

int Room::getY() const
{
	return roomNum % ARRAY_SIZE;
}



/////////////////////////////////////////
// Map Implementation
////////////////////////////////////////

//create randomly generated map
Map::Map()
{
	//create 2D array of Rooms
	int count = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			Room newRoom(count);
			mapArray[i][j] = newRoom;
			count++;
		}
	}

	//add 4 pits at random locations
	srand(unsigned(time(0)));
	int randNum;
	int randX;
	int randY;
	for (int i = 0; i < 4; i++)
	{
		randNum = rand() % 63;
		randX = randNum / ARRAY_SIZE;
		randY = randNum % ARRAY_SIZE;
		//make sure a pit is not added to a room that
		//already has a pit
		if (!mapArray[randX][randY].getHasPit())
		{
			mapArray[randX][randY].setHasPit(true);
		}
		else
		{
			i--;
		}
	}

	//put bats in 4 random rooms
	for (int i = 0; i < 4; i++)
	{
		randNum = rand() % 63;
		randX = randNum / ARRAY_SIZE;
		randY = randNum % ARRAY_SIZE;
		//make sure the room does not already have 
		//a bat
		if (!mapArray[randX][randY].getHasBat())
		{
			mapArray[randX][randY].setHasBat(true);
		}
		else
		{
			i--;
		}
	}

	//set wumpus in random location
	randNum = rand() % 63;
	randX = randNum / ARRAY_SIZE;
	randY = randNum % ARRAY_SIZE;
	mapArray[randX][randY].setHasWumpus(true);
	wumpusRoom = mapArray[randX][randY];

	//set the character at a random location in the pit. 
	//Since it is the starting point, the character will be 
	//placed in a safe room without pit, bat, or Wumpus.
	bool charSet = false;
	while (!charSet)
	{
		randNum = rand() % 63;
		randX = randNum / ARRAY_SIZE;
		randY = randNum % ARRAY_SIZE;
		if (!mapArray[randX][randY].getHasBat() &&
			!mapArray[randX][randY].getHasPit() &&
			!mapArray[randX][randY].getHasWumpus())
		{
			mapArray[randX][randY].setHasCharacter(true);
			curRoom = mapArray[randX][randY];
			charSet = true;
		}
	}
	//set character position
	curRoom = mapArray[randX][randY];
	mapArray[randX][randY].setHasFootsteps(true);
}

//Checks in each room adjacent to where the character is currently
//located and prints information as clues to the player as to the 
//contents of adjacent rooms.
void Map::viewAdjacent()
{
	bool closeBat = false;
	bool closeWumpus = false;
	bool closePit = false;
	//check north
	if (curRoom.getX() > 0)
	{
		if (mapArray[curRoom.getX() - 1][curRoom.getY()].getHasBat())
		{
			closeBat = true;
		}

		if (mapArray[curRoom.getX() - 1][curRoom.getY()].getHasPit())
		{
			closePit = true;
		}

		if (mapArray[curRoom.getX() - 1][curRoom.getY()].getHasWumpus())
		{
			closeWumpus = true;
		}
	}
	//check south
	if (curRoom.getX() < ARRAY_SIZE - 1)
	{
		if (mapArray[curRoom.getX() + 1][curRoom.getY()].getHasBat())
		{
			closeBat = true;
		}

		if (mapArray[curRoom.getX() + 1][curRoom.getY()].getHasPit())
		{
			closePit = true;
		}

		if (mapArray[curRoom.getX() + 1][curRoom.getY()].getHasWumpus())
		{
			closeWumpus = true;
		}
	}

	//check east
	if (curRoom.getY() < ARRAY_SIZE - 1)
	{
		if (mapArray[curRoom.getX()][curRoom.getY() + 1].getHasBat())
		{
			closeBat = true;
		}

		if (mapArray[curRoom.getX()][curRoom.getY() + 1].getHasPit())
		{
			closePit = true;
		}

		if (mapArray[curRoom.getX()][curRoom.getY() + 1].getHasWumpus())
		{
			closeWumpus = true;
		}
	}
	//check west
	if (curRoom.getX() > 0)
	{
		if (mapArray[curRoom.getX()][curRoom.getY() - 1].getHasBat())
		{
			closeBat = true;
		}

		if (mapArray[curRoom.getX()][curRoom.getY() - 1].getHasPit())
		{
			closePit = true;
		}

		if (mapArray[curRoom.getX()][curRoom.getY() - 1].getHasWumpus())
		{
			closeWumpus = true;
		}
	}
	//if a bat is in an adjacent room, print a message
	if (closeBat)
	{
		cout << "You hear the flapping of leathery wings..." << endl;
		cout << "There must be bats nearby." << endl << endl;
	}
	//if a pit is nearby, print a message
	if (closePit)
	{
		cout << "Something feels drafty..." << endl;
		cout << "There must be a pit nearby." << endl;
	}
	//if wumpus is nearby, print a message
	if (closeWumpus)
	{
		cout << "Something smells disgusting and rank like garbage...";
		cout << "Wumpus must be close." << endl;
	}

}

Room Map::getRoom(int roomNum) const
{
	int x = roomNum / ARRAY_SIZE;
	int y = roomNum % ARRAY_SIZE;

	return mapArray[x][y];
}

//initialize game
//Game is contained in a while loop that checks to see if any game
//ending events have occured (character is dead, Wumpus is dead, etc).
//Gets input from the player for actions performed by the player
void Map::embark()
{
	//encouraging intro message
	cout << "Welcome to Chris Kelley's cavern of terror." << endl;
	cout << "You have recklessly decided to pursue the Wumpus." << endl;
	cout << "Your death is all but certain." << endl << endl;
	cout << "These are the actions your feeble body may perform: " << endl;
	cout << "DIRECTIONS: i(up), m(down), j(left), l(right)" << endl;
	cout << "SHOOT ARROW: L(up), M(down), J(left), L(right)" << endl;
	cout << endl;
	cout << "Should you need assistance, no one will heed your call." << endl;
	cout << "But pressing 'h' will remind you of your futility." << endl << endl;

	//continue loop while game ending events have not occurred.
	while (!isDead && !isWupusDead && numArrows > 0)
	{
		string input;

		//get activity from adjacent rooms
		viewAdjacent();
		cout << endl;
		cin >> input;
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		if(input.compare("h") == 0)
		{
			cout << "DIRECTIONS: i(up), m(down), j(left), l(right)" << endl;
			cout << "SHOOT ARROW: L(up), M(down), J(left), L(right)" << endl;
		}
		else if(input.compare("map") == 0)
		{
			printMap();
		}
		else if(input.compare("i") == 0)
		{
			goUp();
		}
		else if(input.compare("m") == 0)
		{
			goDown();
		}
		else if(input.compare("j") == 0)
		{
			goLeft();
		}
		else if(input.compare("l") == 0)
		{
			goRight();
		}
		else if(input.compare("I") == 0)
		{
			shootArrowUp();
		}
		else if(input.compare("M") == 0)
		{
			shootArrowDown();
		}
		else if(input.compare("J") == 0)
		{
			shootArrowLeft();
		}
		else if(input.compare("L") == 0)
		{
			shootArrowRight();
		}
		else
		{
			cout << "You feel confused..." << endl;
		}
		
		//clear the buffer
		cin.clear();

		if (numArrows == 0)
		{
			cout << "You ran out of arrows." << endl;
			cout << "You wander the caverns until you starve to death." << endl;
		}
	}
}

//move wumpus to an adjacent room or stay in same room(20% chance of each)
//this happens when you shoot an arrow that does not hit wumpus
void Map::moveWumpus()
{
	bool isSet = false;
	srand(unsigned(time(0)));
	int randNum;
	int randX;
	int randY;

	//continue loop until a new location for Wumpus has
	//been set.
	while (!isSet)
	{
		randNum = rand() % 4;
		randX = randNum / ARRAY_SIZE;
		randY = randNum % ARRAY_SIZE;

		//wumpus goes north
		if (randNum == 0)
		{
			//make sure there is a room to the north to put wumpus
			if (wumpusRoom.getX() > 0)
			{
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(false);
				wumpusRoom = mapArray[wumpusRoom.getX() - 1]
					[wumpusRoom.getY()];
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(true);
				isSet = true;

			}
		}
		//wumpus moves down
		else if (randNum == 1)
		{
			//make sure there is a room to the south to put Wumpus
			if (wumpusRoom.getX() < ARRAY_SIZE - 1)
			{
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(false);
				wumpusRoom = mapArray[wumpusRoom.getX() + 1]
					[wumpusRoom.getY()];
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(true);
				isSet = true;
			}
		}
		//wumpus moves right
		else if (randNum == 2)
		{
			//make sure there is a room to the east to put Wumpus
			if (wumpusRoom.getY() < ARRAY_SIZE - 1)
			{
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(false);
				wumpusRoom = mapArray[wumpusRoom.getX()]
					[wumpusRoom.getY() + 1];
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(true);
				isSet = true;
			}
		}
		//wumpus moves left
		else if (randNum == 3)
		{
			//Make sure there is a room to the west to put Wumpus
			if (wumpusRoom.getY() > 0)
			{
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(false);
				wumpusRoom = mapArray[wumpusRoom.getX()]
					[wumpusRoom.getY() - 1];
				mapArray[wumpusRoom.getX()][wumpusRoom.getY()]
					.setHasWumpus(true);
				isSet = true;
			}
		}
		//wumpus stays in place
		else if (randNum == 4)
		{
			isSet = true;
		}

		//check if wumpus moved into the room
		//with the character
		if (curRoom.getRoomNum() == wumpusRoom.getRoomNum())
		{
			isDead = true;
			cout << "You hear the arrow shoot off into the distance." << endl;
			cout << "You hear a roar..the Wumpus has awoken." << endl;
			cout << "You hear footstep...they are getting louder!" << endl;
			cout << "Wumpus lunges at you from the darkness!" << endl;
			cout << "You can feel his teeth clamped on your head." << endl;
			cout << "Wumpus bites down and eats half of your head" << endl;
			cout << "YOU ARE DEAD" << endl;
		}
	}
}

//When a player enters a room that is occupied by a bat, the bat moves
//the player to a randomly generated room
void Map::batTeleport(Room& curRoom)
{
	//move bat from old room
	mapArray[curRoom.getX()][curRoom.getY()].setHasBat(false);

	//move character to new room
	srand(unsigned(time(0)));
	int randNum;
	int randX;
	int randY;
	bool isSet = false;
	//while the character has not been set in a valid new random position
	//continue to attempt to place character.
	while (!isSet)
	{
		randNum = rand() % 63;
		randX = randNum / ARRAY_SIZE;
		randY = randNum % ARRAY_SIZE;
		if (!mapArray[randX][randY].getHasBat() &&
			!mapArray[randX][randY].getHasBat() &&
			!mapArray[randX][randY].getHasWumpus())
		{
			mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(false);
			mapArray[randX][randY].setHasCharacter(true);
			curRoom = mapArray[randX][randY];
			isSet = true;
		}
	}
	//find new place for the bat to go
	isSet = false;
	//continue loop while the bat has not been set at 
	//a valid location
	while (!isSet)
	{
		randNum = rand() % 63;
		randX = randNum / ARRAY_SIZE;
		randY = randNum % ARRAY_SIZE;

		if (!mapArray[randX][randY].getHasBat() &&
			!mapArray[randX][randY].getHasCharacter())
		{
			mapArray[randX][randY].setHasBat(true);
			isSet = true;
		}
	}
	//check if bat dropped you in the wumpus room
	if (curRoom.getRoomNum() == wumpusRoom.getRoomNum())
	{
		cout << endl << "It eventually drops you, but your not sure";
		cout << " how far it has carried you." << endl;
		cout << "You hear movement from the corner of the room." << endl;
		cout << "A massive grotesque shape emerges from the shadows." << endl;
		cout << "The bat has dropped you in the same room with the Wumpus!" << endl;
		cout << "The Wumpus lets out a terrible scream, then lunges for you!" << endl;
		cout << "Everything goes black" << endl;
		cout << "You are dead." << endl;
		isDead = true;
	}
	//check if the bat dropped you in a room with a pit
	else if(mapArray[curRoom.getX()][curRoom.getY()].getHasPit())
	{
		cout << "It eventually drops you." << endl;
		cout << "You quickly realize that you have been falling for too long."; 
		cout << endl << "You are falling into a pit, you know your end is near.";
		cout << endl << "You land on your face." << endl;
		cout << "You are dead." << endl;
		isDead = true;
	}
	else
	{
		cout << endl << "It eventually drops you, but your not sure";
		cout << " how far it has carried you." << endl;
	}
}

//prints message to the console when the Wumpus has been successfully killed.
void Map::deadWumpusMessage()
{
	//possibly make random message
	cout << "You hear a terrible scream!" << endl;
	cout << "You hear a thumping on the floor...something is coming your";
	cout << " direction!" << endl << "The Wupus comes into view!" << endl;
	cout << "You are frozen in terror as it runs toward you." << endl;
	cout << "You see an arrow sticking out of its neck";
	cout << "; there is so much blood!" << endl;
	cout << "The Wumpus falls to the floor and slides up to you." << endl;
	cout << "The Wumpus is Dead!" << endl;
	cout << "You wonder what Wumpus jerkey tastes like" << endl;
}

//shoot arrow into room north adjacent of character, 
//if it hits wumpus, then the game is won.
//If arrow doesn't hit wumpus, wumpus wakes up and moves to 
//an adjacent room.
void Map::shootArrowUp()
{
	numArrows--;
	//shot arrow in the room with the Wumpus. The Wumpus is dead
	//and the game has been won by the player.
	if (mapArray[curRoom.getX() - 1][curRoom.getY()].getHasWumpus())
	{
		isWupusDead = true;
		deadWumpusMessage();
	}
	//If the arrow missed, move Wumpus and print status of arrow shot
	//and remaining arrows.
	else
	{
		cout << "You just wasted an arrow." << endl;
		cout << "Only " << numArrows << " left." << endl << endl;
		moveWumpus();
	}
}

//shoot arrow into room south adjacent of character, 
//if it hits wumpus, then the game is won.
//If arrow doesn't hit wumpus, wumpus wakes up and moves to 
//an adjacent room.
void Map::shootArrowDown()
{
	numArrows--;
	//check to see if arrow hit wumpus
	if (mapArray[curRoom.getX() + 1][curRoom.getY()].getHasWumpus())
	{
		isWupusDead = true;
		deadWumpusMessage();
	}
	else
	{
		cout << "You just wasted an arrow." << endl;
		cout << "Only " << numArrows << " left." << endl << endl;
		moveWumpus();
	}
}

//shoot arrow into room east adjacent of character, 
//if it hits wumpus, then the game is won.
//If arrow doesn't hit wumpus, wumpus wakes up and moves to 
//an adjacent room.
void Map::shootArrowRight()
{
	numArrows--;
	//check to see if arrow hit Wumpus.
	if (mapArray[curRoom.getX()][curRoom.getY() + 1].getHasWumpus())
	{
		isWupusDead = true;
		deadWumpusMessage();
	}
	else
	{
		cout << "You just wasted an arrow." << endl;
		cout << "Only " << numArrows << " left." << endl << endl;
		moveWumpus();
	}
}

//shoot arrow into room west adjacent of character, 
//if it hits wumpus, then the game is won.
//If arrow doesn't hit wumpus, wumpus wakes up and moves to 
//an adjacent room.
void Map::shootArrowLeft()
{
	numArrows--;
	//Check to see if Wumpus has been hit
	if (mapArray[curRoom.getX()][curRoom.getY() - 1].getHasWumpus())
	{
		isWupusDead = true;
		deadWumpusMessage();
	}
	else
	{
		cout << "You just wasted an arrow." << endl;
		cout << "Only " << numArrows << " left." << endl << endl;
		moveWumpus();
	}
}

//Move character into room adjacent north of character's current position
//Checks for any events to initialize in the room 
void Map::goUp()
{
	//check to see if north adjacent room is a wall
	if (curRoom.getX() == 0)
	{
		cout << "That's a wall." << endl;
		cout << "You can't walk through walls." << endl;
	}
	else
	{
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(false);
		curRoom = mapArray[curRoom.getX() - 1][curRoom.getY()];
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(true);
		doEvent(curRoom);

	}

}

//Move character into room adjacent south of character's current position
//Checks for any events to initialize in the room 
void Map::goDown()
{
	//check to see if room adjacent south is a wall
	if (curRoom.getX() == ARRAY_SIZE - 1)
	{
		cout << "That's a wall." << endl;
		cout << "You can't walk through walls." << endl;
	}
	else
	{
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(false);
		curRoom = mapArray[curRoom.getX() + 1][curRoom.getY()];
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(true);
		doEvent(curRoom);

	}

}

//Move character into room adjacent east of character's current position
//Checks for any events to initialize in the room 
void Map::goRight()
{
	//check to see if room east adjacent to character is a wall.
	if (curRoom.getY() == ARRAY_SIZE - 1)
	{
		cout << "That's a wall." << endl;
		cout << "You can't walk through walls." << endl;
	}
	else
	{
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(false);
		curRoom = mapArray[curRoom.getX()][curRoom.getY() + 1];
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(true);
		doEvent(curRoom);

	}
}

//Move character into room adjacent west of character's current position
//Checks for any events to initialize in the room 
void Map::goLeft()
{
	//check to see if room adjacent west of character is a wall
	if (curRoom.getY() == 0)
	{
		cout << "That's a wall." << endl;
		cout << "You can't walk through walls." << endl;
	}
	else
	{
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(false);
		curRoom = mapArray[curRoom.getX()][curRoom.getY() - 1];
		mapArray[curRoom.getX()][curRoom.getY()].setHasCharacter(true);
		doEvent(curRoom);

	}
}

//iterates through the rows and columns of the 2D array in the map class
//and prints out the contents of each room.
void Map::printMap()
{
	bool hasSet = false;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			hasSet = false;
			if (mapArray[i][j].getHasBat() &&
				mapArray[i][j].getHasPit() &&
				mapArray[i][j].getHasWumpus())
			{

				cout << "*";
				hasSet = true;

			}
			else if (mapArray[i][j].getHasWumpus() &&
				mapArray[i][j].getHasBat() && !hasSet)
			{
				cout << "#";
				hasSet = true;
			}
			else if (mapArray[i][j].getHasBat() &&
				mapArray[i][j].getHasPit() && !hasSet)
			{
				cout << "$";
				hasSet = true;
			}
			else if (mapArray[i][j].getHasWumpus() &&
				mapArray[i][j].getHasPit() && !hasSet)
			{
				cout << "a";
				hasSet = true;
			}
			else if (mapArray[i][j].getHasWumpus() && !hasSet)
			{
				cout << "?";
				hasSet = true;
			}
			else if (mapArray[i][j].getHasPit() && !hasSet)
			{
				cout << "&";
				hasSet = true;
			}
			else if (mapArray[i][j].getHasBat() && !hasSet)
			{
				cout << "^";
				hasSet = true;;
			}
			else if (mapArray[i][j].getHasCharacter() && !hasSet)
			{
				cout << "+";
				hasSet = true;
			}
			else
			{
				cout << "_";
			}
		}
		cout << endl;
	}
	//print legend for map
	cout << endl << endl;
	cout << "* = bat + wumpus + pit" << endl;
	cout << "# = wumpus + bat" << endl;
	cout << "$ = bat + pit" << endl;
	cout << "a = wumpus + pit" << endl;
	cout << "? = wumpus" << endl;
	cout << "& = pit" << endl;
	cout << "^ = bat" << endl;
	cout << "+ = Your Character" << endl << endl;
}
