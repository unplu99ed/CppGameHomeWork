#include "GameArrow.h"
#include "GameManager.h"

GameArrow::GameArrow(Point position,Point direction): GameObj(position,'-'), m_direction(direction) { }
GameArrow::GameArrow(int x,int y,Point direction):GameObj(x,y,'-'), m_direction(direction) { }

void GameArrow::Move(GameManager* mgr) {
	Undraw();
	Point p = GetPosition();
	p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());
	if ( p.getX()  < (GlobalConsts::MAX_LENGHT)  && p.getY() < (GlobalConsts::MAX_WIDHT) && mgr->isValidPosition(p)) {
		SetPosition(p);
		Draw();
	}
	else {
		mgr->deleteObj(this);
	}
};

GameObjClassType GameArrow::ClassType() {
	return GameObjClassType::typeGameArrow;
}
