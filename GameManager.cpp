#include "GameManager.h"

GameManager::GameManager(char* path) {

	DisplayBoard board(path);
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
						objects.erase(it);
						delete obj;
						break;
					}
				}
			}

			if(rand()%10 == 0) {
				Point place = GetEmptyPosition();
				matrix[place.getY()][place.getX()]=GlobalConsts::MapObjectType::Food;
				board.printObject(Point(place.getX(),place.getY()),GlobalConsts::MapObjectType::Food);
			}

			if(rand()%5 == 0) {
				Point place = GetEmptyPosition();
				matrix[place.getY()][place.getX()]=GlobalConsts::MapObjectType::Quiver;
				board.printObject(Point(place.getX(),place.getY()),GlobalConsts::MapObjectType::Quiver);
			}

			if(rand()%20 == 0) {
				Point place = GetEmptyPosition();
				matrix[place.getY()][place.getX()]=GlobalConsts::MapObjectType::Bomb;
				board.printObject(Point(place.getX(),place.getY()),GlobalConsts::MapObjectType::Bomb);
			}

			for(int i=0; i<this->numOfPlayers; ++i) {
				Collisions(playerArr[i]);
			}

			Sleep(100);
		}
		if (alivePlayers <= 1) {
			con=false;
		}
		else {
			clrscr();
			gotoxy(10,10);
			cout << "Do you want to leave the game ?" << endl;
			char ch = cin.get();
			if (ch == 'y')
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
		matrix[position.getY()][position.getX()] == GlobalConsts::MapObjectType::Legened )
		return false;

	return true;
}

Point GameManager::GetEmptyPosition() {
	Point result;

	while(!isValidPosition(result)) {
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

GameManager::~GameManager(){
	objects.clear(); //run items destructors.
	//playerArr - copy elements from Object vector

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
