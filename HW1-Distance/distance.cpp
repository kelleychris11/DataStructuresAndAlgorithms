#include "distance.h"

/*
* Implementation file for Distance Class.
* Distance Objects contain feet and inches.
* 
* Author: Chris Kelley
* 10/10/2017
*/

/*
* Default Constructor
*/
Distance::Distance() : feet(0), inches(0)
{
}

/*
* Complete Constructor
* Paramaters: int feet; number of feet of distance
int inches; number of inches in distance
*/
Distance::Distance(int thisFeet, int thisInches)
{
	int totalInches = thisFeet * 12 + thisInches;
	thisFeet = totalInches / INCHES_PER_FOOT;
	thisInches = totalInches % INCHES_PER_FOOT;
	feet = thisFeet;
	inches = thisInches;
}

/*
* Deconstructor
*/
Distance::~Distance()
{
}

/*
* Overloaded operator.  Used to add two distance objects.
* Return Value: Distance object that is the sum of this
*				 Distance object and the Distance Object
*				 passed as an argument.
* Parameters:	const &Distance rhs;
*				Distance ojbect added to this Distance object.
*/
Distance Distance::operator+(const Distance & rhs) const
{
	int lhsInches = feet * INCHES_PER_FOOT + inches;
	int rhsInches = rhs.getFeet() * INCHES_PER_FOOT + rhs.getInches();
	int sumInches = lhsInches + rhsInches;
	int newFeet = sumInches / INCHES_PER_FOOT;
	int newInches = sumInches % INCHES_PER_FOOT;
	Distance newDistance(newFeet, newInches);

	return newDistance;
}

/*
* Overloaded operator.Used to subtract two Distance objects.
* Return value: Distance object that is the difference of
*				 this Distance object less the Distance
*				 object passed as an argument.
* Parameters: const &Distance rhs;
*				Distance object subtracted from this Distance
*				object.
*/
Distance Distance::operator-(const Distance & rhs) const
{
	int lhsInches = feet * INCHES_PER_FOOT + inches;
	int rhsInches = rhs.getFeet() * INCHES_PER_FOOT + rhs.getInches();
	int differenceInches = lhsInches - rhsInches;
	int newFeet = differenceInches / INCHES_PER_FOOT;
	int newInches = differenceInches % INCHES_PER_FOOT;
	Distance newDistance(newFeet, newInches);
	return newDistance;
}

/*
* Overloaded operator. Used to multiply this Distance object
*		by the integer parameter provided.
* Return value: Resulting distance object from calculation
* Parameter:const int rhs;
*				Integer used to multiply this Distance object.
*/
Distance Distance::operator*(const int rhs) const
{
	int totalInches = feet * INCHES_PER_FOOT + inches;
	int multipleInches = totalInches * rhs;
	int newFeet = multipleInches / INCHES_PER_FOOT;
	int newInches = multipleInches % INCHES_PER_FOOT;
	Distance newDistance(newFeet, newInches);
	return newDistance;
}

/*
* Overloaded operator. Used to divide this Distance object
*		by the integer parameter provided.
* Return Value: Resulting distance object from calculation.
* Parameter:const int rhs;
*				 Integer used to divide this Distance object.
*/
Distance Distance::operator/(const int rhs) const
{
	int totalInches = feet * INCHES_PER_FOOT + inches;
	int dividedInches = round(((totalInches * 100.0)/ rhs) /100);
	int newFeet = dividedInches / INCHES_PER_FOOT;
	int newInches = dividedInches % INCHES_PER_FOOT;
	Distance newDistance(newFeet, newInches);
	return newDistance;
}

/*
* Set new inches and feet
* Parameters : int feet; new feet
*				int inches; new inches
*/
void Distance::setDistance(int thisFeet, int thisInches)
{
	int totalInches = thisFeet * 12 + thisInches;
	thisFeet = totalInches / INCHES_PER_FOOT;
	thisInches = totalInches % INCHES_PER_FOOT;
	feet = thisFeet;
	inches = thisInches;
}



