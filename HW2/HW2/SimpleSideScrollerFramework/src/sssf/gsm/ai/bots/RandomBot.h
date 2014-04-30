#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\game\Game.h"

class RandomBot : public Bot
{
private:
	unsigned int thinkCounter;

public:
	RandomBot();
	~RandomBot();
//	void initBot(	unsigned int initMin,
//					unsigned int initMax,
//					unsigned int initMaxVelocity);
//	void	pickRandomCyclesInRange();
	Bot*	clone();
	void	pickRandomDestination(Game *game);
	void	think(Game *game);

	// INLINED METHODS
//	unsigned int getCyclesRemainingBeforeThinking()	{ return cyclesRemainingBeforeThinking; }
//	unsigned int getMinCyclesBeforeThinking()		{ return minCyclesBeforeThinking;		}
//	unsigned int getMaxCyclesBeforeThinking()		{ return maxCyclesBeforeThinking;		}
};