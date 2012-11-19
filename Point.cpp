#include "Point.h"

Point::Point(int x,int y) : m_x(x),m_y(y) {}

Point::Point() : m_x(rand() % (GlobalConsts::MAX_LENGHT - 1) + 1),m_y(rand() % (GlobalConsts::MAX_WIDHT - 1) + 1) {}

Point::Point(const Point& p){
	this->m_x = p.getX();
	this->m_y = p.getY();
}

void Point::set(int x,int y) {
	m_x=x;
	m_y=y;
}

int Point::getX() const {
	return m_x;
}

int Point::getY() const {
	return m_y;
}

int Point::comper(Point p2) {
	if (m_x==p2.m_x && m_y==p2.m_y )
		return 0;
	else if (m_x <= p2.m_x && m_y<=p2.m_y )
		return -1;
	else 
		return 1;
}


void Point::generateNewPosition(){
	 m_x=rand() % (GlobalConsts::MAX_LENGHT - 1) + 1;
	 m_y=rand() % (GlobalConsts::MAX_WIDHT - 1) + 1;
}
