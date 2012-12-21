#ifndef __GAMEARROW__
#define __GAMEARROW__

#include "GameObj.h"

//GameArrow: class of arrow item
class GameArrow : public GameObj  {
	//moving Direction
	Point m_direction;
	
	//symobol of arrow
	static const unsigned char ARROW_SYMBOL = (char)29;

public:
	//Constractors
	//GameArrow: Constractors get arrow position and direction
	GameArrow(const Point&, const Point&); 
	//GameArrow: Constractors get arrow position (x,y) and direction
	GameArrow(int, int, const Point&); 
	
	//Move: Performs game action for Arrow.
	void Move(GameManager*); 
	//GameObjClassType: return GameObjClassType::typeGameArrow.
	virtual GameObjClassType ClassType();
};

#endif