#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\ai\bots\RandomBot.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\physics\Physics.h"


/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
RandomBot::RandomBot()
{
	// INIT THE BASIC STUFF
//	initBot(initMin, initMax, initMaxVelocity);
	pp.setVelocity(0.0f, 0.0f);
	approachFailed = false;
	attempApproach = false;
	fightBack = false;
	// AND START THE BOT OFF IN A RANDOM DIRECTION AND VELOCITY
	// AND WITH RANDOM INTERVAL UNTIL IT THINKS AGAIN
	
//	pickRandomCyclesInRange();


}

Bot* RandomBot::clone()
{
	RandomBot *botClone = new RandomBot();
	return botClone;
}


/*
	initBot - this initialization method sets up the basic bot
	properties, but does not setup its velocity.
*/
void RandomBot::initBot(	unsigned int initMin,
							unsigned int initMax,
							unsigned int initMaxV,
							bool initXTerm)
{
	// IF THE MAX IS SMALLER THAN THE MIN, SWITCH THEM
	if (initMax < initMin)
	{
		unsigned int temp = initMax;
		initMax = initMin;
		initMin = temp;
	}
	// IF THEY ARE THE SAME, ADD 100 CYCLES TO THE MAX
	else if (initMax == initMin)
		initMax += 100;

	// INIT OUR RANGE VARIABLES
	minCyclesBeforeThinking = initMin;
	maxCyclesBeforeThinking = initMax;
	maxVelocity = initMaxV;

	// AND WE'LL USE THIS TO ENSURE OUR BOTS ALL LOOK A LITTLE DIFFERENT
	animationRandomizer = (rand() % 45) + 5;

	xTerm = initXTerm;
	if(xTerm)
		yTerm = false;
	else
		yTerm = true;
}

/*
	pickRandomCyclesInRange - a randomized method for determining when this bot
	will think again. This method sets that value.
*/

/*
	pickRandomVelocity - calculates a random velocity vector for this
	bot and initializes the appropriate instance variables.
*/
void RandomBot::pickRandomDestination(Game *game)
{

	game->getGSM()->getWorld()->getWorldWidth();
	int worldCoordinateX = ((float)rand()/RAND_MAX)*game->getGSM()->getWorld()->getWorldWidth();
	int worldCoordinateY = ((float)rand()/RAND_MAX)*game->getGSM()->getWorld()->getWorldHeight();
	// NOW WE CAN SCALE OUR X AND Y VELOCITIES
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	GridPathfinder *pathfinder = spriteManager->getPathfinder();
	pathfinder->mapPath(this, (float)worldCoordinateX, (float)worldCoordinateY);

}

void RandomBot::pickRandomCyclesInRange()
{
	cyclesRemainingBeforeThinking = maxCyclesBeforeThinking - minCyclesBeforeThinking + 1;
	cyclesRemainingBeforeThinking = rand() % cyclesRemainingBeforeThinking;
	cyclesRemainingBeforeThinking += minCyclesBeforeThinking;
}

void RandomBot::pickRandomCyclesInRange2()
{
	cyclesRemainingBeforeThinking = 60 - 10 + 1;
	cyclesRemainingBeforeThinking = rand() % cyclesRemainingBeforeThinking;
	cyclesRemainingBeforeThinking += minCyclesBeforeThinking;
}


bool RandomBot::isPlayerCloseBy(Game *game)
{
	float pX = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().x * BOX2D_SCALE;
	float pY = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().y * -BOX2D_SCALE;
	float bX = getB2Body()->GetPosition().x * BOX2D_SCALE;
	float bY = getB2Body()->GetPosition().y * -BOX2D_SCALE;

	if(abs(pX - bX) <= 400 && abs(pY - bY) <= 400)
	{
		return true;
	}else
		return false;
}

void RandomBot::approachPlayer(Game *game)
{	
	if(!attempApproach) pickRandomCyclesInRange2();
	int pWidth = game->getGSM()->getSpriteManager()->getPlayer()->getSpriteType()->getTextureWidth();
	int pHeight = game->getGSM()->getSpriteManager()->getPlayer()->getSpriteType()->getTextureWidth();
	int bWidth = spriteType->getTextureWidth();
	int bHeight = spriteType->getTextureHeight();
	float pX = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().x * BOX2D_SCALE;
	float pY = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().y * -BOX2D_SCALE;
	float bX = getB2Body()->GetPosition().x * BOX2D_SCALE;
	float bY = getB2Body()->GetPosition().y * -BOX2D_SCALE;

	// Final Approach
	if(abs(pX - bX) <= (abs((pWidth+bWidth)/2.0f) + 20.0f)&& abs(pY - bY) <= (abs((pHeight+bHeight)/2.0f) + 20.0f))
	{
	if(abs(pX - bX) > abs(pY - bY))
	{
		if(pX > bX){
			rotationInRadians = PI/2.0f;
			body->SetLinearVelocity(b2Vec2(maxVelocity, 0));
			setCurrentState(L"MOVE");
		}else if(pX < bX){
			rotationInRadians = -PI/2.0f;
			body->SetLinearVelocity(b2Vec2(-1.0f*maxVelocity, 0));
			setCurrentState(L"MOVE");
		}		
	}else
	{
		if(pY > bY){
			rotationInRadians = -PI;
			body->SetLinearVelocity(b2Vec2(0, -1.0f*maxVelocity));
			setCurrentState(L"MOVE");
		}else if(pY < bY){
			rotationInRadians = 0;
			body->SetLinearVelocity(b2Vec2(0, maxVelocity));
			setCurrentState(L"MOVE");
		}
	}
	}else{
		if(cyclesRemainingBeforeThinking <= 0)
		{
			if(xTerm){
				xTerm = false;
				yTerm = true;
			}else{
				xTerm = true;
				yTerm =  false;
			}
			pickRandomCyclesInRange2();
		}
		if(xTerm)
		{
			if(abs(pX - bX) <= maxVelocity)
			{
				cyclesRemainingBeforeThinking = 0;
				return;
			}else if(pX > bX){
			rotationInRadians = PI/2.0f;
			body->SetLinearVelocity(b2Vec2(maxVelocity, 0));
			setCurrentState(L"MOVE");
		}else if(pX < bX){
			rotationInRadians = -PI/2.0f;
			body->SetLinearVelocity(b2Vec2(-1.0f*maxVelocity, 0));
			setCurrentState(L"MOVE");
		}		
			cyclesRemainingBeforeThinking--;
		}else{
			if(abs(pY - bY) <= maxVelocity)
			{
				cyclesRemainingBeforeThinking = 0;
				return;
			}else if(pY > bY){
			rotationInRadians = -PI;
			body->SetLinearVelocity(b2Vec2(0, -1.0f*maxVelocity));
			setCurrentState(L"MOVE");
		}else if(pY < bY){
			rotationInRadians = 0;
			body->SetLinearVelocity(b2Vec2(0, maxVelocity));
			setCurrentState(L"MOVE");
		}
			cyclesRemainingBeforeThinking--;
		}
	}
	attempApproach = true;
}
/*
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
*/
void RandomBot::think(Game *game)
{
	if(isPlayerCloseBy(game) && !approachFailed)
	{
		approachPlayer(game);
	}else{
		approachFailed = false;
		fightBack = false;
		setCurrentState(L"IDLE");
		body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	}
	// EACH FRAME WE'LL TEST THIS BOT TO SEE IF WE NEED
	// TO PICK A DIFFERENT DIRECTION TO FLOAT IN
	/*
	if (cyclesRemainingBeforeThinking == 0)
	{
		pickRandomDirection();
		pickRandomCyclesInRange();
	}
	else
		cyclesRemainingBeforeThinking--;

	animationRandomizer--;
	if (animationRandomizer == 0)
	{
		animationCounter++;
		animationRandomizer = (rand() % 45) + 5;
	}
	*/
}