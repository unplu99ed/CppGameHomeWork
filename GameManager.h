#ifndef __GameManager__
#define __GameManager__

#include <conio.h>
#include <windows.h>
#include <vector>
#include <queue>

#include <iostream>
using namespace std;

#include "GlobalVariable.h"
#include "Point.h"
#include "Gotoxy.h"
#include "DisplayBoard.h"
#include "GameObj.h"
#include "GamePlayer.h"
#include "GameArrow.h"
#include "GlobalVariable.h"


class GameManager {
	
	GlobalConsts::MapObjectType matrix[GlobalConsts::MAX_HEIGHT][GlobalConsts::MAX_WIDTH];
	vector<GameObj*> objects;
	queue<GameObj*> addObj,delObj;
	GamePlayer** playerArr;
	int numOfPlayers,alivePlayers;
	GameManager(const GameManager&);

	static const int SLEEPING_TIME = 150;


public :
	GameManager(char*);
	~GameManager();
	void createPlayer(const Point&);
	void createArrow(const Point&,const Point&);
	void deleteObj(GameObj*);
	bool isValidPosition(const Point&);
	void Collisions(GamePlayer*);
	Point GetEmptyPosition();
	void SetMapObject(const Point& position,GlobalConsts::MapObjectType type);
	GlobalConsts::MapObjectType GetMapObject(const Point& position) const;

};

#endif