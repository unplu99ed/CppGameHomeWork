#include "GamePlayer.h"
#include "GameManager.h"

//initBaseValues: set the first values of the player's data members
void GamePlayer::initBaseValues() {
	m_power=START_POWER;
	m_numOfArrows=NUMBER_OF_ARROWS;
	m_pauseMoveRounds=0;
	m_pauseArrowsRounds=0;
	m_direction.set(1,1);
}
//Constractors
GamePlayer::GamePlayer(Point position): GameObj(position,PLAYER_SYMBOL) {
	initBaseValues(); //init values
}

GamePlayer::GamePlayer(int x,int y):GameObj(x,y,PLAYER_SYMBOL) {
	initBaseValues(); //init values
}

//Move: Performs game round for Player.
void GamePlayer::Move(GameManager* mgr) {
	if (m_pauseMoveRounds == 0) { // check if player can move
		
		Undraw();

		Point p = GetPosition();
		p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY()); // set new postion
		fixPoint(p); //if needed fix the position of the point
		bool move=!mgr->isValidPosition(p);

		if (!move) // in case the new position is valid,  do change of direction randomly
			move = (rand() % 10 == 0);

		while (move) { // if new poisiton is not valid get valid new position.
			p=GetPosition();
			m_direction.set(rand() % 3 - 1,rand() % 3 - 1);
			p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());
			fixPoint(p);

			if ( mgr->isValidPosition(p) && GetPosition().comper(p) != 0 ) 
				move=false;
		}

		SetPosition(p); //set the new position

		m_pauseMoveRounds=PAUSE_MOVE_AFTER_MOVE; //update waiting rounds

		Draw(mgr);

		switch(mgr->TakeMapObject(p)) { // check if payer is on gift
		case GlobalConsts::Food:
			m_power+=ADD_POWER;
			break;
		case GlobalConsts::Quiver:
			m_numOfArrows+=ADD_ARROWS;
			break;
		case GlobalConsts::Bomb:
			m_power-=LOSE_POWER;
			break;
		}

		HandleDeath(mgr); // check death

		if (m_pauseArrowsRounds == 0 && m_numOfArrows > 0 ) // handle shooting arrow
		{
			Point arrowPosition(GetPosition());
			arrowPosition.set(arrowPosition.getX() + m_direction.getX(),arrowPosition.getY() + m_direction.getY());
			if (mgr->isValidPosition(arrowPosition)) {
				mgr->createArrow(arrowPosition,m_direction);
				m_pauseArrowsRounds = PAUSE_ARROWS_AFTER_SHOOT;
				--m_numOfArrows;
			}
		}
		else if ( m_pauseArrowsRounds > 0 )  {
			m_pauseArrowsRounds--;
		}
	}
	else {
		--m_pauseMoveRounds;
	}
}
//getPower: return the power of the player
int GamePlayer::getPower(){
	return m_power;
}
//getNumberOfArrows: return the number of arrows of the player
int GamePlayer::getNumberOfArrows(){
	return m_numOfArrows;
}
//announceDamage: announce to the player that he had injured
void GamePlayer::announceDamage(GameObj* obj,GameManager* mgr) {
	if ( obj->ClassType() == typeGamePlayer ) {
		GamePlayer* otherPlayer = (GamePlayer*)obj;
		if (otherPlayer->getPower() == getPower()) {
			otherPlayer->HitByPlayer(Same,mgr);
			HitByPlayer(Same,mgr);
		}
		else if (otherPlayer->getPower() < getPower()) {
			otherPlayer->HitByPlayer(Higher,mgr);
			HitByPlayer(Lower,mgr);
		}
		else {
			otherPlayer->HitByPlayer(Lower,mgr);
			HitByPlayer(Higher,mgr);
		}
	}
	else if ( obj->ClassType() == typeGameArrow ) {
		m_power -= 500;
		HandleDeath(mgr);
	}
}
//HandleDeath: handle the situation that player dead 
void GamePlayer::HandleDeath(GameManager* mgr) {
	if (m_power <= 0) {
		mgr->deleteObj(this);
	}
}
//GameObjClassType: return GameObjClassType::typeGamePlayer
GameObj::GameObjClassType GamePlayer::ClassType() {
	return GameObj::typeGamePlayer;
}
//HitByPlayer: handle situation that there is more then one player at the same location
void GamePlayer::HitByPlayer(GamePlayer::HIT_BY_PLAYER_POWER otherPlayer,GameManager* mgr) {
	
	m_power -= otherPlayer;

	if (m_power <= 0) {
		mgr->deleteObj(this);
	}
}