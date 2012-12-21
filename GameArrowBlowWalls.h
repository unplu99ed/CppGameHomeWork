#include "GameArrow.h"
#include "GameManager.h"

class GameArrowBlowWalls : public GameArrow {
public:
	GameArrowBlowWalls(const Point&, const Point&);
	GameArrowBlowWalls(int, int, const Point&);
	virtual void Move(GameManager* mgr);
};

void GameArrowBlowWalls::Move(GameManager* mgr) {
	Point p = GetPosition();
	Undraw();
	
	mgr->DisplayMapObject(p);
	p.set(p.getX()+GetDirection().getX(),p.getY()+GetDirection().getY());

	// validate arrow position if valid continue if not delete arrow
	if ( ( p.getX() >= 0 && p.getX() <=  GlobalConsts::MAX_WIDTH )  && ( p.getY() >= 0 && p.getY() <= GlobalConsts::MAX_HEIGHT ) && mgr->isValidPosition(p)) {
		//position is valid
		SetPosition(p);
		Draw(mgr);
	}
	else {
		//position is not valid
		if (mgr->GetMapObject(p) == GlobalConsts::Wall)
		{
			mgr->TakeMapObject(p);
		}
		mgr->deleteObj(this);
	}
};