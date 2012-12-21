#include "GameManager.h"


void main(int argc,char** argv) {
	if(argc > 1){
		GameManager g(argv[1]);
		g.run();
	} else {
		cout<<"File not found " << endl;         
		system("pause");
	}
}