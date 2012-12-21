#ifndef __GAMEPLAYER__
#define __GAMEPLAYER__

#include "GameObj.h"

class GamePlayer : public GameObj  {
	// dada members
	Point m_direction;
	int m_power,m_numOfArrows;
	int m_pauseMoveRounds,m_pauseArrowsRounds;
	//initBaseValues: set the first values of the player's data members
	void initBaseValues();

	//surpises values :

	static const int LOSE_POWER=750; //take bomb
	static const int ADD_ARROWS=3;   //take quiver
	static const int ADD_POWER=200;  //take food

	//******** initiate values ******

	static const int START_POWER=1000;
	static const int NUMBER_OF_ARROWS=4;
	static const int PAUSE_MOVE_AFTER_MOVE=1;
	static const int PAUSE_ARROWS_AFTER_SHOOT=3;
	static const unsigned char PLAYER_SYMBOL = 232;

public:
	//HIT_BY_PLAYER_POWER: half of the damage when two players collisions
	enum HIT_BY_PLAYER_POWER {
		Lower=5,
		Same=25,
		Higher=100
	};

	//Constractors
	GamePlayer(Point position);
	GamePlayer(int x,int y);
	//Move: play one round.
	void Move(GameManager* mgr);
	//getPower: return the power of the player
	int getPower();
	//getNumberOfArrows: return the number of arrows of the player
	int getNumberOfArrows();
	//announceDamage: announce to the player that he had injured
	void announceDamage(GameObj* obj,GameManager* mgr);
	//GameObjClassType: return GameObjClassType::typeGamePlayer
	virtual GameObjClassType ClassType();
	//HitByPlayer: handle situation that there is more then one player at the same location
	void HitByPlayer(GamePlayer::HIT_BY_PLAYER_POWER,GameManager* mgr);
	//HandleDeath: handle the situation that player dead 
	void HandleDeath(GameManager*);

	
};

#endif