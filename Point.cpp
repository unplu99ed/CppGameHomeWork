 #include "Point.h"

Point::Point(int x,int y) : m_x(x),m_y(y) {}

Point::Point() : m_x(rand() % (GlobalConsts::MAX_WIDTH - 1) + 1),m_y(rand() % (GlobalConsts::MAX_HEIGHT - 1) + 1) {}

Point::Point(const Point& p){
	this->m_x = p.getX();
	this->m_y = p.getY();
}

// set the x and y of the class
void Point::set(int x,int y) {
	m_x=x;
	m_y=y;
}

//return the x position
int Point::getX() const {
	return m_x;
}

//return the y position
int Point::getY() const {
	return m_y;
}

// return the distance between the points
int Point::comper(Point p2) {
	int result = (int)sqrt( pow((double)m_x-(double)p2.m_x,2) + pow((double)m_y-(double)p2.m_y,2));
	return result;
}

// randomize values for x and y
void Point::generateNewPosition(){
	 m_x=rand() % (GlobalConsts::MAX_WIDTH - 1) + 1;
	 m_y=rand() % (GlobalConsts::MAX_HEIGHT - 1) + 1;
}
