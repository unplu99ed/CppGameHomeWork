#ifndef __GAMEARROW__
#define __GAMEARROW__

#include "GameObj.h"

class GameArrow : public GameObj  {
	Point m_direction;
public:
	
	//Constractors
	GameArrow(Point position,Point direction);
	GameArrow(int x,int y,Point direction);
	
	void Move(GameManager* mgr);
	virtual GameObjClassType ClassType();
};

#endif