#ifndef __POINT__
#define __POINT__

#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
#include "GlobalVariable.h"

class Point {
	int m_x,m_y;

public:
	Point(int x,int y);
	Point(const Point& p);
	Point();
	void set(int x,int y);
	int getX() const;
	int getY() const;
	int comper(Point);
	void generateNewPosition();

};

#endif