#include "GameObj.h"

class GameFood: public GameObj {
public:
	GameFood();
	GameFood(Point);
	GameFood(int, int);
	virtual GameObjClassType ClassType() { return GameObjClassType::typeGameFood; };
	virtual void Move(GameManager* mgr) {Draw();};
};

class GameQuiver: public GameObj {
public:
	GameQuiver();
	GameQuiver(Point);
	GameQuiver(int, int);
	virtual GameObjClassType ClassType() { return GameObjClassType::typeGameQuiver; };
	virtual void Move(GameManager* mgr) {Draw();};
};

class GameBomb: public GameObj {
public:
	GameBomb();
	GameBomb(Point);
	GameBomb(int, int);
	virtual GameObjClassType ClassType() { return GameObjClassType::typeGameBomb; };
	virtual void Move(GameManager* mgr) {Draw();};
};