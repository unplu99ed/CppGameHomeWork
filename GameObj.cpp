#include "GameObj.h"
#include "GlobalVariable.h"
#include "GameManager.h"

GameObj::GameObj(char symbol) : SIMBOL_OF_OBJECT(symbol) { 
}

GameObj::GameObj(Point position,char simbol) : M_MyPos(position), SIMBOL_OF_OBJECT(simbol) { 
}

GameObj::GameObj(int x, int y ,char simbol) : M_MyPos(x,y), SIMBOL_OF_OBJECT(simbol) { 
}

//GetPosition: return the position of the object
Point GameObj::GetPosition() { 
	return M_MyPos; 
}


//Draw: Draw element on screen
void GameObj::Draw(GameManager* mgr) { 
	if ( mgr->isValidPosition(M_MyPos) ) {
		gotoxy(M_MyPos.getX(),M_MyPos.getY());
		cout << SIMBOL_OF_OBJECT ;
	}
}


//Undraw: undraw element on screen
void GameObj::Undraw() {
	gotoxy(M_MyPos.getX(),M_MyPos.getY());
	cout << ' ' ;
}

//SetPosition: set new object position
void GameObj::SetPosition(Point pos){
	M_MyPos = pos; 
}

////ClassType: return the type of the object
//GameObj::GameObjClassType GameObj::ClassType() {
//	return GameObj::typeGameObj;
//}


//fixPoint: if point is out of bound make it in bound
void GameObj::fixPoint(Point& p) {

	if ( p.getX() == GlobalConsts::MAX_WIDTH)
		p.set(0,p.getY());
	else if (p.getX() == -1)
		p.set(GlobalConsts::MAX_WIDTH - 1,p.getY());

	if ( p.getY() == GlobalConsts::MAX_HEIGHT)
		p.set(p.getX(),0);
	else if (p.getY() == -1)
		p.set(p.getX(), GlobalConsts::MAX_HEIGHT - 1);

}