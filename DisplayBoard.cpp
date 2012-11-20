#include "DisplayBoard.h"
#include "GameManager.h"

DisplayBoard::DisplayBoard(char* path) : legendPosition(-1,-1) {
	m_filePath = path;
}

GlobalConsts::MapObjectType DisplayBoard::CastToMapObjectType(char ch) {
	switch(ch) {
	case 'W':
		return GlobalConsts::MapObjectType::Wall;
		break;
	case ' ':
	default:
		return GlobalConsts::MapObjectType::Empty;
	}
}

void DisplayBoard::loadMap(GameManager* mgr) {
	ifstream reader;
	reader.open(m_filePath);
	int i,j;

	for(i=0;i <GlobalConsts::MAX_HEIGHT; ++i) {

		for(j=0;j<GlobalConsts::MAX_WIDTH; ++j) {
			char ch = reader.get();

			while (ch == '\r' || ch == '\n'){
				ch = reader.get();
			}

			mgr->SetMapObject(Point(j,i),CastToMapObjectType(ch));

			gotoxy(j,i);

			if (ch == 'P') {
				//	if(legendPosition.getY()==-1 || legendPosition.getX()==-1) 
				mgr->createPlayer(Point(j,i));
				//	else

			}
			else if (ch == 'O'){
				if (legendPosition.comper(Point(-1,-1)) == 0 ) {
					legendPosition.set(j,i);


				}
				cout << ' ';
			}
			else if (ch == 'w' || ch == 'W') {
				cout << (char)178;
			}
			/*else {
			cout << matrix[i][j] ;
			}*/
		}


	}
	reader.close();
	LegendToMatrix(legendPosition,mgr);
	gotoxy(0,0);
}

void DisplayBoard::LegendToMatrix(const Point& position,GameManager* mgr){
	int i,j;
	if((legendPosition.getY()>18 && legendPosition.getY()<=GlobalConsts::MAX_HEIGHT) || ( legendPosition.getX()>68 && legendPosition.getX()<=GlobalConsts::MAX_WIDTH))
		legendPosition.set(67,17);
	for(i=0;i<12;i++){
		mgr->SetMapObject(Point(legendPosition.getX()+i,legendPosition.getY()),GlobalConsts::MapObjectType::Wall);
		mgr->SetMapObject(Point(legendPosition.getX()+i,legendPosition.getY()+6),GlobalConsts::MapObjectType::Wall);
	}
	for(i=1;i<6;i++){
		mgr->SetMapObject(Point(legendPosition.getX(),legendPosition.getY()+i),GlobalConsts::MapObjectType::Wall);
		mgr->SetMapObject(Point(legendPosition.getX()+11,legendPosition.getY()+i),GlobalConsts::MapObjectType::Wall);
	}
	for(i=1;i<11;i++) {
		for(j=1;j<6;j++) {
			mgr->SetMapObject(Point(legendPosition.getX()+i,legendPosition.getY()+j),GlobalConsts::MapObjectType::Legened);
		}
	}

	gotoxy(legendPosition.getX(),legendPosition.getY());
	cout<<"wwwwwwwwwwww";
	for(i=1;i<6;i++){
		gotoxy(legendPosition.getX(),legendPosition.getY()+i);
		cout<<'w';
		gotoxy(legendPosition.getX()+11,legendPosition.getY()+i);
		cout<<'w';
	}
	gotoxy(legendPosition.getX(),legendPosition.getY()+6);
	cout<<"wwwwwwwwwwww";

}


void DisplayBoard::displayLegend(int n,GamePlayer** playerArr ) {
	int i;
	if((legendPosition.getY()>18 && legendPosition.getY()<=GlobalConsts::MAX_HEIGHT) || ( legendPosition.getX()>68 && legendPosition.getX()<=GlobalConsts::MAX_WIDTH))
		legendPosition.set(67,17);
	for(i=0;i<n;i++){
		gotoxy(legendPosition.getX()+1,legendPosition.getY()+i+1);
		if (playerArr[i] != NULL) {
			cout <<" " << i+1 << " " <<  playerArr[i]->getPower()
				<< " " <<  playerArr[i]->getNumberOfArrows()  ;
		}
		else {
			cout <<" " << i+1 << " ---- --";
		}
	}
	for(i=n+1;i<=5;i++){

		gotoxy(legendPosition.getX()+1,legendPosition.getY()+i);
		cout<<" -------- ";
	}

}

void DisplayBoard::printBoard(const GameManager* mgr){
	for(int i=0;i <GlobalConsts::MAX_HEIGHT; ++i) {
		for(int j=0;j<GlobalConsts::MAX_WIDTH; ++j) {
			gotoxy(j,i);
			switch(mgr->GetMapObject(Point(j,i))) {
			case GlobalConsts::MapObjectType::Wall:
				cout << (char)178;
				break;
			case GlobalConsts::MapObjectType::Empty:
				cout << ' ';
				break;
			default:
				cout << mgr->GetMapObject(Point(j,i));
				break; 
			}
		}
	}
}


void DisplayBoard::printObject(const Point& position,GlobalConsts::MapObjectType obj){
	gotoxy(position.getX(),position.getY());
	cout << obj;
}
