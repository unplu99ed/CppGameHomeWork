#include "Gotoxy.h"

//gotoxy: move the screen Cursor to the position of (x,y) -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

//clrscr: Clear screan -- requires windows.h
void clrscr()
{
	system("cls");
}


