#ifndef __GAMEOBJ__
#define __GAMEOBJ__

#include "Point.h"
#include "Gotoxy.h"

class GameManager;

enum GameObjClassType {
	typeGameObj,
	typeGameArrow,
	typeGamePlayer,
	typeGameFood,
	typeGameQuiver,
	typeGameBomb
};

class GameObj {
	Point M_MyPos;
	const char SIMBOL_OF_OBJECT;

protected:

	GameObj();
	GameObj(char);
	GameObj(Point,char);
	GameObj(int, int,char);
	void fixPoint(Point& p);

public:
	enum gameobjclasstype {
		typeGameObj,
		typeGameArrow,
		typeGamePlayer
	};
	void Draw();
	void Undraw();
	virtual void Move(GameManager* mgr) = 0;
	virtual void SetPosition(Point pos);
	Point GetPosition();
	virtual GameObjClassType ClassType();
};


#endif