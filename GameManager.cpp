#include "GameManager.h"
#include "DisplayBoard.h"

GameManager::GameManager(char* path) : board(path) {

	board.loadMap(this);
	alivePlayers = numOfPlayers = objects.size();
	playerArr = new GamePlayer*[numOfPlayers];
	int i=0;
	for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++){
		playerArr[i]  = (GamePlayer*)*it;
		i++;
	}
	bool con = true;
	while(con) {

		while( (!kbhit() || getch()!=27) && alivePlayers > 1) {

			board.displayLegend(numOfPlayers,playerArr);

			for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++) {
				(*it)->Move(this);
			}

			while (!addObj.empty()) {
				objects.push_back(addObj.front());
				addObj.front()->Move(this);
				addObj.pop();
			}

			while (!delObj.empty()) {
				GameObj* obj = delObj.front();
				delObj.pop();
				for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++) {
					if (*it == obj) {
						if (obj->ClassType() == GameObjClassType::typeGamePlayer) {
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

			if(rand()%10 == 0) {
				CreateGift(GlobalConsts::MapObjectType::Food);
			}

			if(rand()%5 == 0) {
				CreateGift(GlobalConsts::MapObjectType::Quiver);
			}

			if(rand()%20 == 0) {
				CreateGift(GlobalConsts::MapObjectType::Bomb);
			}

			for(int i=0; i < numOfPlayers; ++i) {
				Collisions(playerArr[i]);
			}

			Sleep(SLEEPING_TIME);
		}

		if (alivePlayers <= 1) {
			con=false;
		}
		else {
			clrscr();
			gotoxy(10,10);
			cout << "Do you want to leave the game ?" << endl;
			char ch = getch();
			if (ch == 'y' || ch == 'Y' )
				con=false;

			board.printBoard(this);
		}
	}
}

void GameManager::Collisions(GamePlayer* player) {
	for(vector<GameObj*>::iterator it = objects.begin(); it < objects.end(); it++) {
		if (player != NULL && player != *it && player->GetPosition().comper((*it)->GetPosition()) == 0) {
			player->announceDamage(*it,this);
		}
	}
}

void GameManager::createPlayer(const Point& position) {
	objects.push_back(new GamePlayer(position));
}

void GameManager::createArrow(const Point& position,const Point& direction) { 
	addObj.push(new GameArrow(position,direction));
}

void GameManager::deleteObj(GameObj* arrow){
	delObj.push(arrow);
}

bool GameManager::isValidPosition(const Point& position) {

	if (matrix[position.getY()][position.getX()] == GlobalConsts::MapObjectType::Wall ||
		matrix[position.getY()][position.getX()] == GlobalConsts::MapObjectType::Legened ) {
			return false;
	}
	else {
		return true;
	}
}

bool GameManager::isCloseToPlayers(const Point& position) {
	for(int i=0; i < numOfPlayers; ++i) {
		if (playerArr[i] != NULL && playerArr[i]->GetPosition().comper(position) <= 2 )
			return true;
	}

	return false;
}

Point GameManager::GetEmptyPosition() {
	Point result;

	while( !isValidPosition(result) || isCloseToPlayers(result) ) {
		result.generateNewPosition();
	}

	return result;
}


void GameManager::SetMapObject(const Point& position,GlobalConsts::MapObjectType type) {
	matrix[position.getY()][position.getX()] = type;
}

GlobalConsts::MapObjectType GameManager::GetMapObject(const Point& position) const {
	return matrix[position.getY()][position.getX()];
}

GlobalConsts::MapObjectType GameManager::TakeMapObject(const Point& position) {
	GlobalConsts::MapObjectType result = GetMapObject(position);
	matrix[position.getY()][position.getX()] = GlobalConsts::MapObjectType::Empty;
	return result;
}

GameManager::~GameManager(){
	objects.clear(); //run items destructors.
	
	delete playerArr; //playerArr - copy elements from Object vector, don't need to trigger elements destructors.
	

	while (!addObj.empty()) {
		GameObj* item = addObj.front();
		addObj.pop();
		delete item;
	}

	while (!delObj.empty()) {
		GameObj* item = delObj.front();
		delObj.pop();
		delete item;
	}
}

void GameManager::CreateGift(GlobalConsts::MapObjectType type) {
	Point place = GetEmptyPosition();
	matrix[place.getY()][place.getX()]=type;
	board.printObject(Point(place.getX(),place.getY()),type);
}