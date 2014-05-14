#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"


class HealthSupply : public Bot
{
private:
	// float vX;
	// float vY;
	bool hostAlive;
	bool addHealth;
public:
	HealthSupply(){hostAlive = true;addHealth=false;};
	void pickRandomDestination(Game *game){};
	Bot* clone(){return NULL;};
	void think(Game* game);
	// void setVx(float initVx) { vX = initVx;}
	// void setVy(float initVy) { vY = initVy;}
	void setHostAlive(bool flag){hostAlive = flag;}
	void setAddHealth(bool flag){addHealth = flag;};
	bool isAddHealth() { return addHealth;}
};