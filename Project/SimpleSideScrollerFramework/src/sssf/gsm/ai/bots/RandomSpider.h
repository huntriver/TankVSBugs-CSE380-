#pragma once
#include "sssf\gsm\ai\bots\RandomBot.h"

class RandomSpider : public RandomBot
{
public:
	void attackPlayer(Game *game);
	float calcBulletRotation(float vx, float vy);
};