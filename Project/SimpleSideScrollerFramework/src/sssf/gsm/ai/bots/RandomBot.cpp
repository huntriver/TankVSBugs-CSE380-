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
	firstTimeThink = true;
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
							bool initXTerm,
							float proxy)
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
	cyclesRemainingBeforeThinking = 0;

	// AND WE'LL USE THIS TO ENSURE OUR BOTS ALL LOOK A LITTLE DIFFERENT
	animationRandomizer = (rand() % 45) + 5;

	xTerm = initXTerm;
	if(xTerm)
	{
		yTerm = false;
		proxX = proxy;
		proxY = 0;
	}else
	{
		yTerm = true;
		proxX = 0;
		proxY = proxy;
	}
	prevbX = -1000.0f;
	prevbY = -1000.0f;
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

void RandomBot::pickRandomDirection()
{
	bool setComplete = false;
	while(!setComplete)
	{
		int randNum = rand() % 4;
		if(randNum == 0 && upEdgeCC == 0)
		{
			rotationInRadians = 0;
			body->SetLinearVelocity(b2Vec2(0, maxVelocity));
			setComplete = true;
		}else if(randNum == 1 && downEdgeCC == 0)
		{
			rotationInRadians = PI;
			body->SetLinearVelocity(b2Vec2(0, -1.0 * maxVelocity));
			setComplete = true;
		}else if(randNum == 2 && leftEdgeCC == 0)
		{
			rotationInRadians = -PI/2.0f;
			body->SetLinearVelocity(b2Vec2(-1.0 * maxVelocity, 0));
			setComplete = true;
		}else if(randNum == 3 && rightEdgeCC == 0){
			rotationInRadians = PI/2.0f;
			body->SetLinearVelocity(b2Vec2(maxVelocity, 0));
			setComplete = true;
		}
	}
	setCurrentState(L"MOVE");
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

	// Bot gets stuck behind the wall
	if(abs(bX-prevbX) <= 0.3f && abs(bY-prevbY) <= 0.3f && attempApproach){
		approachFailed = true;
		return;
	}
	
	// Final Approach
	if(abs(pX + proxX - bX) <= (abs((pWidth+bWidth)/2.0f) + 20.0f)&& abs(pY + proxY- bY) <= (abs((pHeight+bHeight)/2.0f) + 20.0f))
	{
	if(abs(pX + proxX - bX) > abs(pY + proxY - bY))
	{
		if(pX + proxX > bX){
			rotationInRadians = PI/2.0f;
			body->SetLinearVelocity(b2Vec2(maxVelocity, 0));
			setCurrentState(L"MOVE");
		}else if(pX + proxX < bX){
			rotationInRadians = -PI/2.0f;
			body->SetLinearVelocity(b2Vec2(-1.0f*maxVelocity, 0));
			setCurrentState(L"MOVE");
		}		
	}else
	{
		if(pY + proxY > bY){
			rotationInRadians = -PI;
			body->SetLinearVelocity(b2Vec2(0, -1.0f*maxVelocity));
			setCurrentState(L"MOVE");
		}else if(pY + proxY < bY){
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
				prevbX = getB2Body()->GetPosition().x * BOX2D_SCALE;
				prevbY = getB2Body()->GetPosition().y * -BOX2D_SCALE;
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
				prevbX = getB2Body()->GetPosition().x * BOX2D_SCALE;
				prevbY = getB2Body()->GetPosition().y * -BOX2D_SCALE;
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
	prevbX = getB2Body()->GetPosition().x * BOX2D_SCALE;
	prevbY = getB2Body()->GetPosition().y * -BOX2D_SCALE;
}
/*
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
*/
void RandomBot::think(Game *game)
{
	if(currentState == L"ATTACK")
	{
		attempApproach = false;
		approachFailed = false;
		body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		if(rotationInRadians == 0)
			game->getInput()->sKeyDisabled = true;
		else if(rotationInRadians == PI)
			game->getInput()->wKeyDisabled = true;
		else if(rotationInRadians == PI/2.0f)
			game->getInput()->aKeyDisabled = true;
		else
			game->getInput()->dKeyDisabled = true;
	}else
	{
		if(isPlayerCloseBy(game) && !approachFailed)
		{
			approachPlayer(game);
		}else{
			if(approachFailed && attempApproach)
			{	
				attempApproach = false;
				firstTimeThink = true;
				pickRandomDirection();
				pickRandomCyclesInRange();
			}else{
				if (cyclesRemainingBeforeThinking == 0)
				{
					approachFailed = false;
					pickRandomDirection();
					pickRandomCyclesInRange();
					leftEdgeCC = 0;
					rightEdgeCC = 0;
					upEdgeCC = 0;
					downEdgeCC = 0;
					firstTimeThink = true;
				}
			}
			if((rotationInRadians == -PI/2.0f && leftEdgeCC > 0) ||
				(rotationInRadians == PI/2.0f && rightEdgeCC > 0) ||
				(rotationInRadians == 0 && upEdgeCC > 0) ||
				(rotationInRadians == PI && downEdgeCC > 0))
				{
					setCurrentState(L"IDLE");
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					cyclesRemainingBeforeThinking = 1;
			}else if(!firstTimeThink){
				if(rotationInRadians == -PI/2.0f || rotationInRadians == PI/2.0f)
				{
					float diff = abs(body->GetPosition().x * 5.0f - prevbX2);
					if(diff <= 0.3)
					{
						// It is stuck
						if(rotationInRadians == PI/2.0f)
							rightEdgeCC += 1;
						else
							leftEdgeCC += 1;
						setCurrentState(L"IDLE");
						body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
						cyclesRemainingBeforeThinking = 1;
					}
				}else{
					float diff = abs(body->GetPosition().y * -5.0f - prevbY2);
					if(diff <= 0.3)
					{
						if(rotationInRadians == 0)
							upEdgeCC += 1;
						else
							downEdgeCC += 1 ;
						setCurrentState(L"IDLE");
						body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
						cyclesRemainingBeforeThinking = 1;
					}
				}
			}
			cyclesRemainingBeforeThinking--;
		}
	}

	prevbX2 = body->GetPosition().x * 5.0f;
	prevbY2 = body->GetPosition().y * -5.0f;
	firstTimeThink = false;
}