#ifndef __GOTOXY__
#define __GOTOXY__
/***************************************
  Credit for finding this code goes to:
          Yoav  Aharoni
      [yoav_ah@netvision.net.il]
***************************************/

#include <iostream>
using namespace std;

#include <windows.h>
#include <process.h>

//gotoxy: move the screen Cursor to the position of (x,y) -- requires windows.h
void gotoxy(int, int);

//Clear screan -- requires windows.h
void clrscr(); 

#endif