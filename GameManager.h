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

//GameManager: class the manage the game, players, arrows and matrix with static objects.
class GameManager {
	
	DisplayBoard board; 
	//alivePlayers: the current number of alive players, numOfPlayers: the number of player from the begining
	int alivePlayers,numOfPlayers;

	//matrix: have all the static element of the map wall,food,bomb ... etc
	GlobalConsts::MapObjectType matrix[GlobalConsts::MAX_HEIGHT][GlobalConsts::MAX_WIDTH];

	//objects: all alive moving objects in the game
	vector<GameObj*> objects;

	//addObj: object to add after the current game round, delObj: ovject to delete after the current game round.
	queue<GameObj*> addObj,delObj;

	//playerArr: array of players.
	GamePlayer** playerArr;
	
	//SLEEPING_TIME: const of sleeping time after round.
	static const int SLEEPING_TIME = 50;
	
	//GameManager: blocking copy contractor.
	GameManager(const GameManager&);

	//Collisions: check Collisions between moving objects
	void Collisions(GamePlayer*);

	//isCloseToPlayers: check if the point is close to a player. 
	bool isCloseToPlayers(const Point&);

	//CreateGift: set a new gift (Food,Quiver,Bomb) at random valid position.
	void CreateGift(GlobalConsts::MapObjectType);

public :
	GameManager(char*);
	~GameManager();

	//run: start and handle the game.
	void run();
	
	//createPlayer: create game player.
	void createPlayer(const Point&);
	
	//createArrow: create game arrow.
	void createArrow(const Point&,const Point&);
	
	//deleteObj: object to delete after the game round.
	void deleteObj(GameObj*);
	
	//isValidPosition: check if the new position is valid (the new position is on empty space or gift).
	bool isValidPosition(const Point&);

	//GetEmptyPosition: get empty and valid position ( only empty places).
	Point GetEmptyPosition();

	//SetMapObject: update the matrix with static object
	void SetMapObject(const Point&, GlobalConsts::MapObjectType);

	//GetMapObject: get the static element from the matrix.
	GlobalConsts::MapObjectType GetMapObject(const Point&) const;

	//TakeMapObject: return the type of element of this position and erase it with empty position.
	GlobalConsts::MapObjectType TakeMapObject(const Point&);

	//DisplayMapObject: draw a static object on the screen
	void DisplayMapObject(const Point&);

};

#endif