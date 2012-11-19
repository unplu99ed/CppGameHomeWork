#ifndef __GAMEPLAYER__
#define __GAMEPLAYER__

#include "GameObj.h"

class GamePlayer : public GameObj  {
	Point m_direction;
	int m_power,m_numOfArrows;
	int m_pauseMoveRounds,m_pauseArrowsRounds;
	void initBaseValues();
public:
	
	//Constractors
	GamePlayer(Point position);
	GamePlayer(int x,int y);
	void Move(GameManager* mgr);
	int getPower();
	int getNumberOfArrows();
	void announceDamage(GameObj* obj,GameManager* mgr);
	virtual GameObjClassType ClassType();
};

#endif