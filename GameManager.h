#ifndef __GameManager__
#define __GameManager__

#include <conio.h>
#include <windows.h>
#include <vector>
#include <queue>
#include <time.h>
#include <iostream>
using namespace std;

#include "GlobalVariable.h"
#include "Point.h"
#include "Gotoxy.h"
#include "GameObj.h"
#include "GamePlayer.h"
#include "GameArrow.h"
#include "GlobalVariable.h"
#include "DisplayBoard.h"

class GameManager {
	
	DisplayBoard board;
	int alivePlayers,numOfPlayers;
	GlobalConsts::MapObjectType matrix[GlobalConsts::MAX_HEIGHT][GlobalConsts::MAX_WIDTH];
	vector<GameObj*> objects;
	queue<GameObj*> addObj,delObj;
	GamePlayer** playerArr;
	

	static const int SLEEPING_TIME = 50;
	GameManager(const GameManager&);


public :
	GameManager(char*);
	~GameManager();
	void createPlayer(const Point&);
	void createArrow(const Point&,const Point&);
	void deleteObj(GameObj*);
	bool isValidPosition(const Point&);
	void Collisions(GamePlayer*);
	Point GetEmptyPosition();
	void SetMapObject(const Point&, GlobalConsts::MapObjectType);
	GlobalConsts::MapObjectType GetMapObject(const Point&) const;
	GlobalConsts::MapObjectType TakeMapObject(const Point&);
	bool isCloseToPlayers(const Point&);
	void CreateGift(GlobalConsts::MapObjectType);
	void DisplayMapObject(const Point&);

};

#endif