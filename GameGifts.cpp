#include "GameGifts.h"

GameFood::GameFood():GameObj(131) {};
GameFood::GameFood(Point p):GameObj(p,131) {}
GameFood::GameFood(int x, int y):GameObj(x,y,131) {}

GameQuiver::GameQuiver():GameObj(165) {};
GameQuiver::GameQuiver(Point p):GameObj(p,165) {}
GameQuiver::GameQuiver(int x, int y):GameObj(x,y,165) {}

GameBomb::GameBomb():GameObj(216) {};
GameBomb::GameBomb(Point p):GameObj(p,216) {}
GameBomb::GameBomb(int x, int y):GameObj(x,y,216) {}