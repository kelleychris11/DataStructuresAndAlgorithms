#ifndef DISTANCE_H
#define DISTANCE_H
#include <iostream>
#include <math.h>
const int INCHES_PER_FOOT = 12;

/* Header file for distance class.  Distance objects hold feet and
 * inches as distance integer values.
 * 
 * Author: Chris Kelley
 * Date:   10/10/2017
*/
class Distance
{

	/*
	 * Override output operator. Creates custom output for Distance class.
	 * Return value: new output stream
	 * Parameters: ostream& output; overriden output stream
				   const Distance& d; Distance object to output.
	*/
	friend std::ostream& operator <<(std::ostream& output, const Distance& d)
	{
		return output << d.getFeet() << "/" << d.getInches();
	}

private:
	int feet;
	int inches;
	
public:

	/*
	 * Default Constructor
	*/
	Distance();

	/*
	 * Complete Constructor
	 * Paramaters: int feet; number of feet of distance
				   int inches; number of inches in distance
	*/
	Distance(int feet, int inches);

	/*
	 * Deconstructor
	*/
	~Distance();

	/*
	 * Overloaded operator.  Used to add two distance objects.
	 * Return Value: Distance object that is the sum of this
	 *				 Distance object and the Distance Object
	 *				 passed as an argument.
	 * Parameters:	const &Distance rhs; 
	 *				Distance ojbect added to this Distance object.
	*/
	Distance operator + (const Distance& rhs) const;

	/*
	 * Overloaded operator.Used to subtract two Distance objects.
	 * Return value: Distance object that is the difference of 
	 *				 this Distance object less the Distance
	 *				 object passed as an argument.
	 * Parameters: const &Distance rhs; 
	 *				Distance object subtracted from this Distance 
	 *				object.
	*/
	Distance operator - (const Distance& rhs) const;

	/*
	 * Overloaded operator. Used to multiply this Distance object
	 *		by the integer parameter provided.
	 * Return value: Resulting distance object from calculation
	 * Parameter:const int rhs;
	 *				Integer used to multiply this Distance object.
	*/
	Distance operator * (const int rhs) const;

	/*
	 * Overloaded operator. Used to divide this Distance object
	 *		by the integer parameter provided.
	 * Return Value: Resulting distance object from calculation.
	 * Parameter:const int rhs; 
	 *				 Integer used to divide this Distance object.
	*/
	Distance operator / (const int rhs) const;

	/*
	 * Get feet value contained in object.
	 * Return Value: feet of object
	*/
	int getFeet() const
	{
		return feet;
	}

	/*
	 * Get inches value contained in object
	 * Return Value: inches of object.
	*/
	int getInches() const
	{
		return inches;
	}

	/*
	 * Set new inches and feet
	 * Parameters : int feet; new feet
	 *				int inches; new inches
	*/
	void setDistance(int feet, int inches);

};
#endif

