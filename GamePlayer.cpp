#include "GamePlayer.h"
#include "GameManager.h"

void GamePlayer::initBaseValues() {
	m_power=START_POWER;
	m_numOfArrows=NUMBER_OF_ARROWS;
	m_pauseMoveRounds=0;
	m_pauseArrowsRounds=0;
	m_direction.set(1,1);
}
GamePlayer::GamePlayer(Point position): GameObj(position,PLAYER_SYMBOL) {
	initBaseValues();
}
GamePlayer::GamePlayer(int x,int y):GameObj(x,y,PLAYER_SYMBOL) {
	initBaseValues();
}

void GamePlayer::Move(GameManager* mgr) {
	if (m_pauseMoveRounds == 0) {
		Undraw();
		Point p;

		p = GetPosition();
		p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());
		fixPoint(p);
		bool move=!mgr->isValidPosition(p);

		if (!move)
			move = (rand() % 10 == 0);

		while (move) {
			p=GetPosition();
			m_direction.set(rand() % 3 - 1,rand() % 3 - 1);
			p.set(p.getX()+m_direction.getX(),p.getY()+m_direction.getY());
			fixPoint(p);

			if ( mgr->isValidPosition(p) && GetPosition().comper(p) != 0 ) 
				move=false;
		}

		int x=p.getX();
		SetPosition(p);
		m_pauseMoveRounds=PAUSE_MOVE_AFTER_MOVE;
		Draw(mgr);

		switch(mgr->TakeMapObject(p)) {
		case GlobalConsts::MapObjectType::Food:
			m_power+=ADD_POWER;
			break;
		case GlobalConsts::MapObjectType::Quiver:
			m_numOfArrows+=ADD_ARROWS;
			break;
		case GlobalConsts::MapObjectType::Bomb:
			m_power-=LOSE_POWER;
			break;
		}

		HandleDeath(mgr);

		if (m_pauseArrowsRounds == 0 && m_numOfArrows > 0 )
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

int GamePlayer::getPower(){
	return m_power;
}
int GamePlayer::getNumberOfArrows(){
	return m_numOfArrows;
}

void GamePlayer::announceDamage(GameObj* obj,GameManager* mgr) {
	if ( obj->ClassType() == GameObjClassType::typeGamePlayer ) {
		GamePlayer* otherPlayer = (GamePlayer*)obj;
		if (otherPlayer->getPower() == getPower()) {
			otherPlayer->HitByPlayer(HIT_BY_PLAYER_POWER::Same,mgr);
			HitByPlayer(HIT_BY_PLAYER_POWER::Same,mgr);
		}
		else if (otherPlayer->getPower() < getPower()) {
			otherPlayer->HitByPlayer(HIT_BY_PLAYER_POWER::Higher,mgr);
			HitByPlayer(HIT_BY_PLAYER_POWER::Lower,mgr);
		}
		else {
			otherPlayer->HitByPlayer(HIT_BY_PLAYER_POWER::Lower,mgr);
			HitByPlayer(HIT_BY_PLAYER_POWER::Higher,mgr);
		}
	}
	else if ( obj->ClassType() == GameObjClassType::typeGameArrow ) {
		m_power -= 500;
		HandleDeath(mgr);
	}
}

void GamePlayer::HandleDeath(GameManager* mgr) {
	if (m_power <= 0) {
		mgr->deleteObj(this);
	}
}

GameObjClassType GamePlayer::ClassType() {
	return GameObjClassType::typeGamePlayer;
}

void GamePlayer::HitByPlayer(GamePlayer::HIT_BY_PLAYER_POWER otherPlayer,GameManager* mgr) {
	switch (otherPlayer) {
	case HIT_BY_PLAYER_POWER::Lower :
		m_power -= HIT_BY_PLAYER_POWER::Lower;
		break;
	case HIT_BY_PLAYER_POWER::Same :
		m_power -= HIT_BY_PLAYER_POWER::Same;
		break;
	case HIT_BY_PLAYER_POWER::Higher :
		m_power -= HIT_BY_PLAYER_POWER::Higher;
		break;
	}

	if (m_power <= 0) {
		mgr->deleteObj(this);
	}
}