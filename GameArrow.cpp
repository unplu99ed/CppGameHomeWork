#include "GameArrow.h"
#include "GameManager.h"

//Constractors
//GameArrow: Constractors get arrow position and direction
GameArrow::GameArrow(const Point& position,const Point& direction): GameObj(position,ARROW_SYMBOL), m_direction(direction) { }
//GameArrow: Constractors get arrow position (x,y) and direction
GameArrow::GameArrow(int x,int y,const Point& direction):GameObj(x,y,ARROW_SYMBOL), m_direction(direction) { }


//Move: Performs game round for Arrow.
void GameArrow::Move(GameManager* mgr) {
	Point p = GetPosition();
	Undraw();
	
	mgr->DisplayMapObject(p);
	p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());

	// validate arrow position if valid continue if not delete arrow
	if ( ( p.getX() >= 0 && p.getX() <=  GlobalConsts::MAX_WIDTH )  && ( p.getY() >= 0 && p.getY() <= GlobalConsts::MAX_HEIGHT ) && mgr->isValidPosition(p)) {
		//position is valid
		SetPosition(p);
		Draw(mgr);
	}
	else {
		//position is not valid
		mgr->deleteObj(this);
	}
}

//GameObjClassType: return GameObjClassType::typeGameArrow.
GameObj::GameObjClassType GameArrow::ClassType() {
	return GameObj::typeGameArrow;
}
