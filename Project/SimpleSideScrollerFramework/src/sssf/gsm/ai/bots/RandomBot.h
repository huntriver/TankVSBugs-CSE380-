#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\sprite\SpriteManager.h"

class RandomBot : public Bot
{
private:
	HealthSupply* hs;
	int healthId;
	bool healthSupply;
	void pickRandomCyclesInRange2();
	unsigned int cyclesRemainingBeforeThinking;
	unsigned int minCyclesBeforeThinking;
	unsigned int maxCyclesBeforeThinking;
	unsigned int animationRandomizer;
	unsigned int maxVelocity;
	bool approachFailed;
	bool attempApproach;
	bool xTerm;
	bool yTerm;
	bool fightBack;
	int termCounter;
	float proxX;
	float prevbX;
	float proxY;
	float prevbY;
	float prevbX2;
	float prevbY2;
	bool firstTimeThink;
	int attackInterval;
	// bool preAttack;
	// bool attack;
	bool longDistanceAttack;
	int attackFrameCounter;
public:
	RandomBot();
	~RandomBot();
	void initBot(	unsigned int initMin,
					unsigned int initMax,
					unsigned int initMaxV,
					bool initXTerm,
					float proxy);
	void	pickRandomCyclesInRange();
	Bot*	clone();
	void	pickRandomDestination(Game *game);
	void    pickRandomDirection();
	void	think(Game *game);
	void    setHealthSupply(bool flag) { healthSupply = flag;}
	//void    setHS(HealthSupply* initHs) {hs = initHs;}
	// HealthSupply* getHS() {return hs;}
	void    approachPlayer(Game *game);
	bool    isPlayerCloseBy(Game *game);
	bool	isAttempApproach(){return attempApproach;}
	void    setApproachFailed(bool flag){approachFailed = flag;}
	void    setFightBack(bool flag) {fightBack = flag;}
	void setAttackInterval(int initAttackInterval) { attackInterval = initAttackInterval; attackFrameCounter = attackInterval;}
	void setLongDistanceAttack(bool initLongDistanceAttack) { longDistanceAttack = initLongDistanceAttack; }
	void setHealthId(int initHealthId) {healthId = initHealthId;}
	virtual void preAttack(Game *game){};
	virtual void attackPlayer(Game *game);

	// INLINED METHODS
	int getAttackInterval() { return attackInterval; }
	unsigned int getCyclesRemainingBeforeThinking()	{ return cyclesRemainingBeforeThinking; }
	unsigned int getMinCyclesBeforeThinking()		{ return minCyclesBeforeThinking;		}
	unsigned int getMaxCyclesBeforeThinking()		{ return maxCyclesBeforeThinking;		}
	int getHealthId(){return healthId;}
	bool hasHealthSupply() { return healthSupply; }
};