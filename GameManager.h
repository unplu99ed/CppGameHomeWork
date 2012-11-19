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
	GlobalConsts::MapObjectType matrix[GlobalConsts::MAX_WIDHT][GlobalConsts::MAX_LENGHT];
	vector<GameObj*> objects;
	queue<GameObj*> addObj,delObj;
	GamePlayer** playerArr;
	int numOfPlayers;

public :
	GameManager(char*);
	void createPlayer(Point);
	void createArrow(Point,Point);
	void deleteObj(GameObj*);
	bool isValidPosition(Point);
	void Collisions(GamePlayer*);
	Point GetEmptyPosition();
	void SetMapObject(Point position,GlobalConsts::MapObjectType type);
	GlobalConsts::MapObjectType GetMapObject(Point position);

};

#endif