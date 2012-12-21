#include "GameManager.h"
#include "DisplayBoard.h"

GameManager::GameManager(char* path) : board(path) {

	srand((unsigned)time(0)); //resets the random function

	board.loadMap(this); // load map from file.

	numOfPlayers = alivePlayers = objects.size(); //init number of players.

	playerArr = new GamePlayer*[numOfPlayers];

	int i=0;
	for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++){
		playerArr[i]  = (GamePlayer*)*it;
		i++;
	}

	bool con = true;
	while(con) { //check if number of players is less or equal to 1 or the user want to exit

		while( (!kbhit() || getch()!=27) && alivePlayers > 1) { //run until user press esc or number of players is less or equal to 1

			board.displayLegend(numOfPlayers,playerArr); // update game score board

			for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++) { //game round for all the moving objects
				(*it)->Move(this);
			}

			while (!addObj.empty()) { //moving object that added in the last game round.
				objects.push_back(addObj.front());
				addObj.front()->Move(this);
				addObj.pop();
			}

			while (!delObj.empty()) {//delete object that died in the last game round.
				GameObj* obj = delObj.front();
				delObj.pop();
				for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++) {
					if (*it == obj) {
						if (obj->ClassType() == GameObj::typeGamePlayer) {
							for(int i = 0; i < numOfPlayers; ++i) {
								if (playerArr[i] == obj) {
									playerArr[i] = NULL;
									--alivePlayers;
								}
							}
						}
						obj->Undraw();
						objects.erase(it);
						delete obj;
						break;
					}
				}
			}

			//check if to add Food 
			if(rand() % 10 == 0) {
				CreateGift(GlobalConsts::Food);
			}

			//check if to add Quiver 
			if(rand() % 5 == 0) {
				CreateGift(GlobalConsts::Quiver);
			}

			//check if to add Bomb 
			if(rand() % 20 == 0) {
				CreateGift(GlobalConsts::Bomb);
			}

			//check Collisions
			for(int i=0; i < numOfPlayers; ++i) {
				Collisions(playerArr[i]);
			}

			//sleeping time in the end of the round. 
			Sleep(SLEEPING_TIME);
		}

		//check if number of alivePlayers is less or equal to 1 
		if (alivePlayers <= 1) {
			con=false;
		}
		else {
			//make sure that the user want to exit.
			clrscr();
			gotoxy(10,10);
			cout << "Do you want to leave the game ?" << endl;
			char ch = getch();
			if (ch == 'y' || ch == 'Y' ) 
				con=false;
			else
				board.printBoard(this);
		}
	}
	//if the number of alivePlayers is less or equal to 1 declare on the winner.
	if (alivePlayers <= 1) {
		int WinPlayerNumber=-1;
		for(int i=0; i< numOfPlayers; ++i) {
			if ( playerArr[i] != NULL )
				WinPlayerNumber=i;
		}

		clrscr();
		gotoxy(22,8);
		cout << "Player Number " << WinPlayerNumber + 1 << " WIN !!!" << endl;
		
		gotoxy(22,9);
		getchar();
	}
}

//Collisions: check Collisions between moving objects
void GameManager::Collisions(GamePlayer* player) {
	for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++) {
		if (player != NULL && player != *it && player->GetPosition().comper((*it)->GetPosition()) == 0) {
			player->announceDamage(*it,this);
		}
	}
}

//createPlayer: create game player.
void GameManager::createPlayer(const Point& position) {
	objects.push_back(new GamePlayer(position));
}

//createArrow: create game arrow.
void GameManager::createArrow(const Point& position,const Point& direction) { 
	addObj.push(new GameArrow(position,direction));
}

//deleteObj: object to delete after the game round.
void GameManager::deleteObj(GameObj* arrow){
	delObj.push(arrow);
}

//isValidPosition: check if the new position is valid (the new position is on empty space or gift).
bool GameManager::isValidPosition(const Point& position) {

	if (matrix[position.getY()][position.getX()] == GlobalConsts::Wall ||
		matrix[position.getY()][position.getX()] == GlobalConsts::Legened ) {
			return false;
	}
	else {
		return true;
	}
}

//isCloseToPlayers: check if the point is close to a player.
bool GameManager::isCloseToPlayers(const Point& position) {
	for(int i=0; i < numOfPlayers; ++i) {
		if (playerArr[i] != NULL && playerArr[i]->GetPosition().comper(position) <= 2 )
			return true;
	}

	return false;
}

//GetEmptyPosition: get empty and valid position ( only empty places).
Point GameManager::GetEmptyPosition() {
	Point result;

	while( !isValidPosition(result) || isCloseToPlayers(result) ) {
		result.generateNewPosition();
	}

	return result;
}

//SetMapObject: update the matrix with static object
void GameManager::SetMapObject(const Point& position,GlobalConsts::MapObjectType type) {
	matrix[position.getY()][position.getX()] = type;
}

//DisplayMapObject: draw a static object on the screen
void GameManager::DisplayMapObject(const Point& position) {
	board.printObject(position,matrix[position.getY()][position.getX()]);
}

//GetMapObject: get the static element from the matrix.
GlobalConsts::MapObjectType GameManager::GetMapObject(const Point& position) const {
	return matrix[position.getY()][position.getX()];
}

//TakeMapObject: return the type of element of this position and erase it with empty position.
GlobalConsts::MapObjectType GameManager::TakeMapObject(const Point& position) {
	GlobalConsts::MapObjectType result = GetMapObject(position);
	matrix[position.getY()][position.getX()] = GlobalConsts::Empty;
	return result;
}

//object destructor
GameManager::~GameManager(){
	objects.clear(); //run items destructors.

	delete playerArr; //playerArr - copy elements from Object vector, don't need to trigger elements destructors.


	while (!addObj.empty()) { //clear addObj queue
		GameObj* item = addObj.front();
		addObj.pop();
		delete item;
	}

	while (!delObj.empty()) { //clear delObj queue
		GameObj* item = delObj.front();
		delObj.pop();
		delete item;
	}
}

//CreateGift: set a new gift (Food,Quiver,Bomb) at random valid position.
void GameManager::CreateGift(GlobalConsts::MapObjectType type) {
	Point place = GetEmptyPosition();
	matrix[place.getY()][place.getX()]=type;
	board.printObject(Point(place.getX(),place.getY()),type);
}