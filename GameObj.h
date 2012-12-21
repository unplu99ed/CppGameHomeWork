#ifndef __GAMEOBJ__
#define __GAMEOBJ__

#include "Point.h"
#include "Gotoxy.h"

class GameManager;

//GameObj: abstract base class of Moving Game Object
class GameObj {
	//M_MyPos: object Positon
	Point M_MyPos;

	//SIMBOL_OF_OBJECT: const that contain simbol of object
	const unsigned char SIMBOL_OF_OBJECT;

protected:
	GameObj();
	GameObj(char);
	GameObj(Point,char);
	GameObj(int, int,char);
	
	//fixPoint: if point is out of bound make it in bound
	void fixPoint(Point& p);

public:
	//GameObjClassType: the types of moving Objects
	enum GameObjClassType {
		typeGameObj,
		typeGameArrow,
		typeGamePlayer
	};
	
	//Draw: Draw element on screen
	void Draw(GameManager* mgr);
	
	void Undraw();
	
	//Move: abstract function for moving
	virtual void Move(GameManager* mgr) = 0;

	//SetPosition: set new object position
	virtual void SetPosition(Point pos);

	//GetPosition: return the position of the object
	Point GetPosition();
	
	//ClassType: return the type of the object
	virtual GameObjClassType ClassType();
};


#endif