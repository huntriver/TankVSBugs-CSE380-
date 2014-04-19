/*	
Author: Richard McKenna
Stony Brook University
Computer Science Department

SpriteManager.cpp

See SpriteManager.h for a class description.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\bots\RandomBot.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"

/*
addSpriteToRenderList - This method checks to see if the sprite
parameter is inside the viewport. If it is, a RenderItem is generated
for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	b2Body* body = sprite->getB2Body();
	PhysicalProperties *pp = sprite->getPhysicalProperties();
	float rotation = sprite->getRotationInRadians();

	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(	
		body->GetPosition().x * 5.0f,
		(-1)*(body->GetPosition().y * 5.0f),
		spriteType->getTextureWidth(),
		spriteType->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		renderList->addRenderItem(	sprite->getCurrentImageID(),
			pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2-viewport->getViewportX()),
			pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2-viewport->getViewportY()),
			0,
			sprite->getAlpha(),
			spriteType->getTextureWidth(),
			spriteType->getTextureHeight(),
			rotation);
	}
}

/*
addSpriteItemsToRenderList - This method goes through all of the sprites,
including the player sprite, and adds the visible ones to the render list.
This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(	Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);

		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		botIterator = bots.begin();
		while (botIterator != bots.end())
		{			
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}
	}
}

/*
addSprite - This method is for adding a new sprite to 
this sprite manager. Once a sprite is added it can be 
scheduled for rendering.
*/
void SpriteManager::addBot(Bot *botToAdd)
{
	bots.push_back(botToAdd);
}

/*
addSpriteType - This method is for adding a new sprite
type. Note that one sprite type can have many sprites. For
example, we may say that there may be a "Bunny" type of
sprite, and specify properties for that type. Then there might
be 100 different Bunnies each with their own properties, but that
share many things in common according to what is defined in
the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size()-1;
}

/*
clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	//spriteTypes.clear();
	//bots.clear();
}

/*
getSpriteType - This gets the sprite type object that corresponds
to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
unloadSprites - This method removes all artwork from memory that
has been allocated for game sprites.
*/
void SpriteManager::unloadSprites()
{
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
	/*list<Bot*>::iterator botsIt = bots.begin();
	while (botsIt != bots.end())
	{
	list<Bot*>::iterator tempIt = botsIt;
	botsIt++;
	Bot *botToDelete = (*tempIt);
	delete botToDelete;
	}
	bots.clear();

	vector<AnimatedSpriteType*>::iterator spriteTypesIt = spriteTypes.begin();
	while (spriteTypesIt != spriteTypes.end())
	{
	vector<AnimatedSpriteType*>::iterator tempIt = spriteTypesIt;
	spriteTypesIt++;
	AnimatedSpriteType *astToDelete = (*tempIt);
	delete astToDelete;
	}
	spriteTypes.clear();

	// DELETE THE PATHFINDER IF THERE IS ONE
	if (pathfinder != NULL)
	delete pathfinder;
	*/
}

Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	return NULL;
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
}

/*
update - This method should be called once per frame. It
goes through all of the sprites, including the player, and calls their
update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{

	if (bots.size()<0)
	{
		//Physics *physics = game->getGSM()->getPhysics();
		RandomBot *bot = new RandomBot();
		//physics->addCollidableObject(bot);
		//PhysicalProperties *pp = bot->getPhysicalProperties();
		//pp->setPosition(200, 300);
		AnimatedSpriteType *botSpriteType = this->getSpriteType(1);
		bot->setSpriteType(botSpriteType);
		bot->setCurrentState(L"IDLE");
		bot->setAlpha(255);
		this->addBot(bot);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(200.0f/5.0f, -400.0f/5.0f);
		b2Body* body = (game->getGSM()->getWorld()->boxWorld)->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(32.0f/5.0f, 32.0f/5.0f);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;

		// Override the default friction.
		fixtureDef.friction = 0.3f;

		// Add the shape to the body.
		body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
		body->CreateFixture(&fixtureDef);
		bot->setB2Body(body);
		body->SetUserData(bot);

		//bot->affixTightAABBBoundingVolume();
	}
	TT++;
	// FIRST LET'S DO THE NECESSARY PATHFINDING
	//pathfinder->updatePath(&player);
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		if (bot->dead){
			botIterator=bots.erase(botIterator);
			if (botIterator==bots.end()) break;
			bot = (*botIterator);
		}
		if (botIterator==bots.end()) break;
		//if (bot->hasReachedDestination())
			//bot->pickRandomDestination(game);
	//	pathfinder->updatePath(bot);
		botIterator++;
	}

	// THEN UPDATE THE PLAYER SPRITE ANIMATION FRAME/STATE/ROTATION
	player.updateSprite();

	// NOW UPDATE THE REST OF THE SPRITES ANIMATION FRAMES/STATES/ROTATIONS
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		bot->updateSprite();
		botIterator++;
	}
}