#ifndef __DISPLAYBOARD__
#define __DISPLAYBOARD__


#include <iostream>
using namespace std;
#include <fstream>

#include "GameManager.h"
#include "GamePlayer.h"
#include "GlobalVariable.h"
#include "Gotoxy.h"
#include "Point.h"


class GameManager;
class GamePlayer;

class DisplayBoard {
	char* m_filePath;
	Point legendPosition;

public:
	DisplayBoard(char*);
	void LegendToMatrix(const Point& position,GameManager* mgr);
	void loadMap(GameManager* mgr);
	void printBoard(const GameManager* mgr);
	GlobalConsts::MapObjectType CastToMapObjectType(char ch);
	void displayLegend(int,GamePlayer**);
	void printObject(const Point& position,GlobalConsts::MapObjectType obj);
};

#endif