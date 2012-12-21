#ifndef __POINT__
#define __POINT__

#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
#include "GlobalVariable.h"

//Point: class with x,y positions
class Point {
	int m_x/* X position */,m_y/* Y position */;

public:

	Point(int x,int y); //
	Point(const Point& p);
	Point();

	// set the x and y of the class
	void set(int x,int y); 
	
	//return the x position
	int getX() const; 
	
	//return the y position
	int getY() const; 
	
	// return the distance between the points
	int comper(Point); 
	
	// randomize values for x and y.
	void generateNewPosition(); 
};

#endif