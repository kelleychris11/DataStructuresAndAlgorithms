#ifndef MAP_H
#define MAP_H
const int ARRAY_SIZE = 8;

/////////////////////////////////////
//Author: Chris Kelley
//CSS 342
//Project #6
//Time: 15 hours
//////////////////////////////////////

////////////////////////////////////////////////////
//Room class
//		Each Room object represents a physical room
//		in the map class.
//		Contains information about what is contained
//		in each room.
/////////////////////////////////////////////////////

class Room
{

private:
	bool hasWumpus = false;
	bool hasPit = false;
	bool hasBat = false;
	bool hasFootsteps = false;
	bool hasCharacter = false;
	int roomNum;
	int x;
	int y;

public:

	//room default constructor
	Room(){}
	
	//constructor with room number argument
	Room(const int thisRoomNum);

	//sets the room number
	void setRoomNum(const int newRoomNum);

	//returns the room number
	int getRoomNum() const;

	//set true if the room has Wumpus
	void setHasWumpus(const bool newVal);

	//set true if the room has a bat
	void setHasBat(const bool newVal);

	//set true if the room has a pit
	void setHasPit(const bool newVal);

	//return true if the character is in the room
	bool getHasCharacter() const;

	//set true if the character is in the room
	void setHasCharacter(const bool newVal);

	//return true if the room has Wumpus
	bool getHasWumpus() const;
	
	//return true if the room has a bat
	bool getHasBat() const;

	//return true if the room has a pit
	bool getHasPit() const;

	//returns the row number of the room in 
	//the map class
	int getX() const;

	//returns the column number of the room
	//in the map class
	int getY() const;

	//set true if the character has been 
	//in the room before
	void setHasFootsteps(bool newVal);

	//return true if the character has been in the 
	//room before
	bool getHasFootsteps() const;
};

///////////////////////////////////////////////////
//Map class
//		Contains a 2 dimensional array of Rooms
//		Represents a physical maze or cavern
//		The character must navigate through the 
//		rooms to defeat the Wumpus and win the game
////////////////////////////////////////////////////

class Map
{
private:
	Room mapArray[ARRAY_SIZE][ARRAY_SIZE];
	Room curRoom;
	Room wumpusRoom;
	int numArrows = 4;
	bool isDead = false;
	bool isWupusDead = false;

public:
	//randomly create rooms in the default constructor
	Map();

	//returns the Room object of the room number provided
	Room getRoom(int roomNum) const;

	//initialize the game
	void embark();

	//move the Wumpus to an adjacent room to where the
	//Wumpus previously was
	void moveWumpus();

	//Handles event of character walking into a room with
	//a bat. The bat teleports the character to a random
	//room.
	void batTeleport(Room& curRoom);

	//Handle action of shooting an arrow in the row above
	//the row the character is currently in
	void shootArrowUp();

	//Handle the action of shooting an arrow in the row
	//below the row the character is currently in
	void shootArrowDown();

	//Handle the action of shooting an arrow in the column
	//to the right of the column the character is currently in
	void shootArrowRight();

	//Handle the action of shooting an arrow in the column
	//to the left of the column the character is currently in
	void shootArrowLeft();

	//analyze adjacent rooms for information about what is contained
	//in those rooms. Provide clues to the player based on those
	//room contents
	void viewAdjacent();

	//Move character one row up from the current row.
	void goUp();

	//Move the character down from the current row.
	void goDown();

	//Move the character to the right of the current column.
	void goRight();

	//Move the character to the left of the current column.
	void goLeft();

	//Perform event based on what is contained in a room
	//that the character has entered.
	void doEvent(Room& curRoom);

	//Print map to screen with legend
	void printMap();

	//Print message upon death of the Wumpus
	void deadWumpusMessage();
};












#endif

