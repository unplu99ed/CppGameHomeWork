#ifndef __DISPLAYBOARD__
#define __DISPLAYBOARD__


#include <iostream>
using namespace std;
#include <fstream>

#include "GamePlayer.h"
#include "GlobalVariable.h"
#include "Gotoxy.h"
#include "Point.h"
#include <iomanip>

using namespace std;


class GameManager;
class GamePlayer;

class DisplayBoard {
	char* m_filePath;
	Point legendPosition;

public:
	DisplayBoard(char*);
	void LegendToMatrix(const Point&,GameManager*);
	void loadMap(GameManager*);
	void printBoard(const GameManager*);
	GlobalConsts::MapObjectType CastToMapObjectType(char);
	void displayLegend(int,GamePlayer**);
	void printObject(const Point& position,GlobalConsts::MapObjectType);
	char EnemToChar(int);
};

#endif