#ifndef __GAMEARROW__
#define __GAMEARROW__

#include "GameObj.h"

class GameArrow : public GameObj  {
	Point m_direction;
	static const char ARROW_SYMBOL = (char)29;
public:
	
	//Constractors
	GameArrow(const Point&, const Point&);
	GameArrow(int, int, const Point&);
	void Move(GameManager*);
	virtual GameObjClassType ClassType();
};

#endif