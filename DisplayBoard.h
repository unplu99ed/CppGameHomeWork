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

// DisplayBoard: class that manage the display of the console and update the game matrix

class GameManager; // declaration
class GamePlayer; // declaration

class DisplayBoard {
	char* m_filePath;
	Point legendPosition;

public:
	//DisplayBoard: consractor
	DisplayBoard(char*);
	//LegendToMatrix: set the walls and the starting position of the legend at the matrix
	void LegendToMatrix(const Point&,GameManager*);
	//loadMap: load the map from the text file 
	void loadMap(GameManager*);
	//printBoard: responsible of printing our static objects and our dinamic objects at real time
	void printBoard(const GameManager*);
	//CastToMapObjectType: get char and return object type
	GlobalConsts::MapObjectType CastToMapObjectType(char);
	//displayLegend: manage the legend of the matrix and update it real time
	void displayLegend(int,GamePlayer**);
	//printObject: get an object and it's position and print the object at the console 
	void printObject(const Point& position,GlobalConsts::MapObjectType);
	//EnemToChar: get enum that represents an object and return it's char 
	char EnemToChar(GlobalConsts::MapObjectType ToReturn);
};

#endif