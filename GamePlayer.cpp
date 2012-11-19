#include "GamePlayer.h"
#include "GameManager.h"

void GamePlayer::initBaseValues() {
	m_power=1000;
	m_numOfArrows=0;
	m_pauseMoveRounds=0;
	m_pauseArrowsRounds=0;
	m_direction.set(1,1);
}
GamePlayer::GamePlayer(Point position): GameObj(position,232) {
	initBaseValues();
}
GamePlayer::GamePlayer(int x,int y):GameObj(x,y,232) {
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
		m_pauseMoveRounds=1;
		Draw(mgr);

		if (mgr->GetMapObject(p) != GlobalConsts::MapObjectType::Empty) {
			switch(mgr->GetMapObject(p)) {
			case GlobalConsts::MapObjectType::Food:
				break;
			case GlobalConsts::MapObjectType::Quiver:
				break;
			case GlobalConsts::MapObjectType::Bomb:
				break;
			}
			//לסדר את עניין המתנות
		}

		if (m_pauseArrowsRounds == 0 && m_numOfArrows > 0 )
		{
			Point arrowPosition(GetPosition());
			arrowPosition.set(arrowPosition.getX() + m_direction.getX(),arrowPosition.getY() + m_direction.getY());
			mgr->createArrow(GetPosition(),m_direction);
			m_pauseArrowsRounds = 3;
			m_numOfArrows--;
		}
		else {
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
		if (m_power <= 0) {
			mgr->deleteObj(this);
		}
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