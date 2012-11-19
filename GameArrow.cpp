#include "GameArrow.h"
#include "GameManager.h"

GameArrow::GameArrow(Point position,const Point& direction): GameObj(position,'-'), m_direction(direction) { }
GameArrow::GameArrow(int x,int y,const Point& direction):GameObj(x,y,'-'), m_direction(direction) { }

void GameArrow::Move(GameManager* mgr) {
	Undraw();
	Point p = GetPosition();
	p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());
	int x=p.getX(),y=p.getY(); //Debugging
	if ( ( p.getX() >= 0 && p.getX() <=  GlobalConsts::MAX_LENGHT )  && ( p.getY() >= 0 && p.getY() <= GlobalConsts::MAX_WIDHT ) && mgr->isValidPosition(p)) {
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
