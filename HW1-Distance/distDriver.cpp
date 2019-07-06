#include "distance.h"
using namespace std;

/*
* Test file for Distance class. 
* 
* Author: Chris Kelley
* Date: 10/10/2017
*/

int main()
{
	Distance dist1(1, 10);
	Distance dist2;
	dist2.setDistance(3, 4);
	cout << "Test addition: output should be 5/2"<< endl;
	cout << "output: ";
	cout << dist2 + dist1 << endl;
	cout << "Test subtraction: output should be 1/6" << endl;
	cout << "output: ";
	cout << dist2 - dist1 << endl;
	cout << "Test multiplication: output shoud be 13/4" << endl;
	cout << "output: ";
	cout << dist2 * 4 << endl;
	cout << "Test division: output should be 0/6" << endl;
	cout << "output: ";
	cout << dist2 / 7 << endl;
	Distance dist3(1, -5);
	cout << "Test addition with negative inches: ";
	cout << "output should be 3/11" << endl;
	cout << "output: ";
	cout << dist2 + dist3 << endl;
	Distance dist4(-1, -5);
	cout << "Test addition with negative feet and inches: "; 
	cout << "output should be 1/11" << endl;
	cout << "output: ";
	cout << dist2 + dist4 << endl;
	cout << "Test getInches function: output should be 4" << endl;
	cout << "output: ";
	cout << dist2.getInches() << endl;
	cout << "Test getFeet function: output should be 3" << endl;
	cout << "output: ";
	cout << dist2.getFeet() << endl;
	dist2.setDistance(6, 20);
	cout << "test setDistance function: ouput should be 7/8" << endl;
	cout << "output: " << dist2 << endl;
	cout << "--------------------" << endl;
	Distance dist5(4, -2);
	cout << "test formatting: output should be 3/10" << endl;
	cout << "output: " << dist5 << endl;
	Distance dist6(-4, 145);
	cout << "test formatting: output should be 8/1" << endl;
	cout << "output: " << dist6 << endl;
	Distance dist7(-5, 3);
	cout << "test formatting: output should be -4/-9" << endl;
	cout << "output: " << dist7 << endl;
}
