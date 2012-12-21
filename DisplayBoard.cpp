#include "DisplayBoard.h"
#include "GameManager.h"

//consractor
DisplayBoard::DisplayBoard(char* path) : legendPosition(-1,-1) {
	m_filePath = path;
}

//CastToMapObjectType: get char and return object type
GlobalConsts::MapObjectType DisplayBoard::CastToMapObjectType(char ch) {
	switch(ch) {
	case 'W':
		return GlobalConsts::Wall;
		break;
	case ' ':
	default:
		return GlobalConsts::Empty;
	}
}

//loadMap: load the map from the text file
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

			if (ch == 'P' ) {
				if (legendPosition.comper(Point(-1,-1)) != 0 
					&& legendPosition.getX() <= j && legendPosition.getY() <= i
					&& legendPosition.getX()+12 >= j && legendPosition.getY()+7 >= i) {

						mgr->createPlayer(mgr->GetEmptyPosition());
				}
				else {
					mgr->createPlayer(Point(j,i));
				}
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
		}
	}
	//create players in problematic position
	reader.close();
	LegendToMatrix(legendPosition,mgr);
	gotoxy(0,0);
}

//LegendToMatrix: set the walls and the starting position of the legend at the matrix
void DisplayBoard::LegendToMatrix(const Point& position,GameManager* mgr){
	int i,j;
	if((legendPosition.getY()>18 && legendPosition.getY()<=GlobalConsts::MAX_HEIGHT) || ( legendPosition.getX()>68 && legendPosition.getX()<=GlobalConsts::MAX_WIDTH))
		legendPosition.set(67,17);

	for(i=0;i<12;i++){ //Print Walls around the legend
		mgr->SetMapObject(Point(legendPosition.getX()+i,legendPosition.getY()),GlobalConsts::Wall);
		mgr->SetMapObject(Point(legendPosition.getX()+i,legendPosition.getY()+6),GlobalConsts::Wall);
	}

	for(i=1;i<6;i++){ //Print Walls around the legend
		mgr->SetMapObject(Point(legendPosition.getX(),legendPosition.getY()+i),GlobalConsts::Wall);
		mgr->SetMapObject(Point(legendPosition.getX()+11,legendPosition.getY()+i),GlobalConsts::Wall);
	}

	for(i=1;i<11;i++) { //set legend place on the matrix
		for(j=1;j<6;j++) {
			mgr->SetMapObject(Point(legendPosition.getX()+i,legendPosition.getY()+j),GlobalConsts::Legened);
		}
	}

	gotoxy(legendPosition.getX(),legendPosition.getY());
	for(i=0;i<12;i++)
		cout<<EnemToChar(GlobalConsts::Wall);
	for(i=1;i<6;i++){
		gotoxy(legendPosition.getX(),legendPosition.getY()+i);
		cout<<EnemToChar(GlobalConsts::Wall);
		gotoxy(legendPosition.getX()+11,legendPosition.getY()+i);
		cout<<EnemToChar(GlobalConsts::Wall);
	}
	gotoxy(legendPosition.getX(),legendPosition.getY()+6);
	for(i=0;i<12;i++)
		cout<<EnemToChar(GlobalConsts::Wall);

}

//displayLegend: manage the legend of the matrix and update it real time
void DisplayBoard::displayLegend(int n,GamePlayer** playerArr ) {

	if((legendPosition.getY()>18 && legendPosition.getY()<=GlobalConsts::MAX_HEIGHT) || ( legendPosition.getX()>68 && legendPosition.getX()<=GlobalConsts::MAX_WIDTH))
		legendPosition.set(67,17);

	for(int i=0;i<n;i++){
		gotoxy(legendPosition.getX()+1,legendPosition.getY()+i+1);
		if (playerArr[i] != NULL) {
			cout <<" " << i+1 << " " <<setw(4)<< playerArr[i]->getPower()
				<< " " << setw(2)<< playerArr[i]->getNumberOfArrows()  ;
		}
		else {
			cout <<" " << i+1 << " ---- --";
		}
	}

	for(int i=n+1;i<=5;i++){

		gotoxy(legendPosition.getX()+1,legendPosition.getY()+i);
		cout<<" -------- ";
	}

}

//printBoard: responsible of printing our static objects and our dinamic objects at real time
void DisplayBoard::printBoard(const GameManager* mgr){
	for(int i=0;i <GlobalConsts::MAX_HEIGHT; ++i) {
		for(int j=0;j<GlobalConsts::MAX_WIDTH; ++j) {

			gotoxy(j,i);
			cout << EnemToChar(mgr->GetMapObject(Point(j,i))) ;

		}
	}
}

//printObject: get an object and it's position and print the object at the console 
void DisplayBoard::printObject(const Point& position,GlobalConsts::MapObjectType obj){
	gotoxy(position.getX(),position.getY());
	cout <<EnemToChar(obj) ;
}

//EnemToChar: get enum that represents an object and return it's char 
char DisplayBoard:: EnemToChar(GlobalConsts::MapObjectType ToReturn)
{
	switch(ToReturn){
	case GlobalConsts::Wall :
		return (char)178;
		break;
	case GlobalConsts::Bomb:
		return (char)15;
		break;
	case GlobalConsts::Food :
		return (char)3 ;
		break;
	case GlobalConsts::Quiver :
		return (char)27 ;
		break;
	case GlobalConsts::Empty :
	default:
		return ' ';
		break;

	}
}