#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\game\Game.h"

class RandomBot : public Bot
{
private:
	void    pickRandomCyclesInRange2();
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

public:
	RandomBot();
	~RandomBot();
	void initBot(	unsigned int initMin,
					unsigned int initMax,
					unsigned int initMaxV,
					bool initXTerm);
	void	pickRandomCyclesInRange();
	Bot*	clone();
	void	pickRandomDestination(Game *game);
	void	think(Game *game);
	void    approachPlayer(Game *game);
	bool    isPlayerCloseBy(Game *game);
	bool	isAttempApproach(){return attempApproach;}
	void    setApproachFailed(bool flag){approachFailed = flag;}
	void    setFightBack(bool flag) {fightBack = flag;}

	// INLINED METHODS
	unsigned int getCyclesRemainingBeforeThinking()	{ return cyclesRemainingBeforeThinking; }
	unsigned int getMinCyclesBeforeThinking()		{ return minCyclesBeforeThinking;		}
	unsigned int getMaxCyclesBeforeThinking()		{ return maxCyclesBeforeThinking;		}
};