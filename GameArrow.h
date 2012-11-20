#ifndef __GAMEARROW__
#define __GAMEARROW__

#include "GameObj.h"

class GameArrow : public GameObj  {
	Point m_direction;
	static const char ARROW_SYMBOL = '-';
public:
	
	//Constractors
	GameArrow(Point position,const Point& direction);
	GameArrow(int x,int y,const Point& direction);
	
	void Move(GameManager* mgr);
	virtual GameObjClassType ClassType();
};

#endif