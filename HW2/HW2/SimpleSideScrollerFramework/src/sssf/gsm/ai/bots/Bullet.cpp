#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\ai\bots\Bullet.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\physics\Physics.h"

Bot* Bullet::clone()
{
	Bullet* botClone = new Bullet();
	return botClone;
}

void Bullet::pickRandomDestination(Game *game)
{
}