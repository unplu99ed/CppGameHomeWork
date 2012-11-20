#include "GameArrow.h"
#include "GameManager.h"

GameArrow::GameArrow(const Point& position,const Point& direction): GameObj(position,ARROW_SYMBOL), m_direction(direction) { }
GameArrow::GameArrow(int x,int y,const Point& direction):GameObj(x,y,ARROW_SYMBOL), m_direction(direction) { }

void GameArrow::Move(GameManager* mgr) {
	Undraw();
	Point p = GetPosition();

	mgr->DisplayMapObject(p);

	p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());
	if ( ( p.getX() >= 0 && p.getX() <=  GlobalConsts::MAX_WIDTH )  && ( p.getY() >= 0 && p.getY() <= GlobalConsts::MAX_HEIGHT ) && mgr->isValidPosition(p)) {
		SetPosition(p);
		Draw(mgr);
	}
	else {
		mgr->deleteObj(this);
	}
};

GameObjClassType GameArrow::ClassType() {
	return GameObjClassType::typeGameArrow;
}
