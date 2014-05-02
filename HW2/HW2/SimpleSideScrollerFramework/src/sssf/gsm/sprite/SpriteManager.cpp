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
SpriteManager::SpriteManager()
{
	TT = 0;
	luaPState = LuaState::Create();
	int result = luaPState->DoFile("data/lua/script.lua");
}
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport,GameStateManager *gsm)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	b2Body* body = sprite->getB2Body();
	PhysicalProperties *pp = sprite->getPhysicalProperties();
	float rotation = sprite->getRotationInRadians();
	float xx,yy;
	if (sprite->getHealth()==0)
		{
			xx=sprite->getPhysicalProperties()->getX();
			yy=sprite->getPhysicalProperties()->getY();
		}
	else
	{
		xx=body->GetPosition().x * 5.0f;
		yy=(-1)*(body->GetPosition().y * 5.0f);
	}
	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(	
		xx,
		yy,
		spriteType->getTextureWidth(),
		spriteType->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		/*float xx,yy;
		if (sprite->getHealth()==0)
		{
			xx=sprite->getPhysicalProperties()->getX();
			yy=sprite->getPhysicalProperties()->getY();
		}
		else
{
			xx=(body->GetPosition().x)*5.0f);
			 yy=(-1)*(body->GetPosition().y)*5.0f;
		}*/
		renderList->addRenderItem(	sprite->getCurrentImageID(),pp->round(xx-spriteType->getTextureWidth()/2-viewport->getViewportX()),
			pp->round(yy-spriteType->getTextureHeight()/2-viewport->getViewportY()),
			
			
			0,
			sprite->getAlpha(),
			spriteType->getTextureWidth(),
			spriteType->getTextureHeight(),
			0);
		int aa=gsm->getSpriteManager()->getSpriteType(3)->getAnimationFrameID(L"IDLE", 0);
		for (int i=0;i<sprite->getHealth();i++)
			renderList->addRenderItem(aa	,
			pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2-viewport->getViewportX())+i*12,
			pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2-viewport->getViewportY())-12,
			0,
			sprite->getAlpha(),
			20,
			10,
			0);
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


		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		botIterator = bots.begin();
		while (botIterator != bots.end())
		{			
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport,gsm);
			botIterator++;
		}
		addSpriteToRenderList(&player, renderList, viewport,gsm);
		list<TopDownSprite*>::iterator bulletIterator;
		bulletIterator = bullets.begin();
		while (bulletIterator != bullets.end())
		{			
			TopDownSprite *bullet = (*bulletIterator);
			addSpriteToRenderList(bullet, renderList, viewport,gsm);
			bulletIterator++;
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
void SpriteManager::addBullet(TopDownSprite *bulletToAdd)
{
	bullets.push_back(bulletToAdd);
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
	 //@TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
	list<Bot*>::iterator botsIt = bots.begin();
	while (botsIt != bots.end())
	{
	list<Bot*>::iterator tempIt = botsIt;
	botsIt++;
	Bot *botToDelete = (*tempIt);
	delete botToDelete;
	}
	bots.clear();

	list<TopDownSprite*>::iterator bulletsIt = bullets.begin();
	while (bulletsIt != bullets.end())
	{
	list<TopDownSprite*>::iterator tempIt = bulletsIt;
	bulletsIt++;
	TopDownSprite *bulletToDelete = (*tempIt);
	delete bulletToDelete;
	}
	bullets.clear();

/*	vector<AnimatedSpriteType*>::iterator spriteTypesIt = spriteTypes.begin();
	while (spriteTypesIt != spriteTypes.end())
	{
	vector<AnimatedSpriteType*>::iterator tempIt = spriteTypesIt;
	spriteTypesIt++;
	AnimatedSpriteType *astToDelete = (*tempIt);
	delete astToDelete;
	}
	spriteTypes.clear();*/

	// DELETE THE PATHFINDER IF THERE IS ONE
	if (pathfinder != NULL)
	delete pathfinder;
	
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
	TT++;
	if (TT % 120 == 0 && bots.size() <= 6)
	{
		//Physics *physics = game->getGSM()->getPhysics();
		RandomBot *bot = new RandomBot();
		//physics->addCollidableObject(bot);
		//PhysicalProperties *pp = bot->getPhysicalProperties();
		//pp->setPosition(200, 300);
		AnimatedSpriteType *botSpriteType = this->getSpriteType(1);
		bot->setSpriteType(botSpriteType);
		bot->setCurrentState(L"IDLE LEFT");
		bot->setAlpha(255);
		this->addBot(bot);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(2300.0f/5.0f, -520.0f/5.0f);
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
		TT = 0;
	}
	

	
	
	// FIRST LET'S DO THE NECESSARY PATHFINDING
	//pathfinder->updatePath(&player);
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		if(bot->getSpriteType()->getSpriteTypeID() == 4)
		{
			botIterator++;
			continue;
		}
		if (botIterator==bots.end()) break;
		if(bot->getHealth() != 0){
		if(bot->getCurrentState() != L"ATTACK UP" &&
		bot->getCurrentState() != L"ATTACK DOWN" &&
		bot->getCurrentState() != L"ATTACK LEFT" &&
		bot->getCurrentState() != L"ATTACK RIGHT")
		{
			//if (bot->hasReachedDestination())
			{
	//			pathfinder->mapPath(bot, player.getB2Body()->GetPosition().x * 5.0f, player.getB2Body()->GetPosition().y * -5.0f);
	//		}else{
				if(bot->collide)
				{
					bot->getB2Body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					bot->changeToIdleState(bot->getCurrentState());
				}

				static_cast<RandomBot*>(bot)->think(game);
			}
		}
		}
	//	pathfinder->updatePath(bot);
		botIterator++;
	}

	// THEN UPDATE THE PLAYER SPRITE ANIMATION FRAME/STATE/ROTATION
	player.updateSprite();
	if(!(player.getHitObject())[0])
	{
		game->getInput()->wKeyDisabled = false;
	}
	if(!(player.getHitObject())[1])
	{
		game->getInput()->sKeyDisabled = false;
	}
	if(!(player.getHitObject())[2])
	{
		game->getInput()->aKeyDisabled = false;
	}
	if(!(player.getHitObject())[3])
	{
		game->getInput()->dKeyDisabled = false;
	}
	list<TopDownSprite*>::iterator bulletIterator;
    bulletIterator = bullets.begin();
	while (bulletIterator != bullets.end())
	{
		TopDownSprite *bullet = (*bulletIterator);
		if (bullet->dead){
			bulletIterator=bullets.erase(bulletIterator);
			game->getGSM()->getWorld()->boxWorld->DestroyBody(bullet->getB2Body());
			if (bulletIterator==bullets.end()) break;
			bullet = (*bulletIterator);
		}
		bullet->updateSprite();
		bulletIterator++;
	}
	// NOW UPDATE THE REST OF THE SPRITES ANIMATION FRAMES/STATES/ROTATIONS
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		if(bot->getSpriteType()->getSpriteTypeID() == 4)
		{
			if(bot->getHealth() == 0){
				botIterator=bots.erase(botIterator);
				game->getGSM()->getWorld()->boxWorld->DestroyBody(bot->getB2Body());
				if (botIterator==bots.end()) break;
			}
			botIterator++;
		}else{
			if(bot->getHealth() != 0)
			{
			if(bot->getCurrentState() == L"ATTACK UP" ||
			   bot->getCurrentState() == L"ATTACK DOWN" ||
			   bot->getCurrentState() == L"ATTACK LEFT" ||
		       bot->getCurrentState() == L"ATTACK RIGHT" ||
		       bot->getCurrentState() == L"IDLE UP" ||
		       bot->getCurrentState() == L"IDLE DOWN" ||
		       bot->getCurrentState() == L"IDLE LEFT" ||
		       bot->getCurrentState() == L"IDLE RIGHT")
		      {
				bot->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			  }
			if(bot->getCurrentState() == L"ATTACK UP" ||
				bot->getCurrentState() == L"ATTACK DOWN" ||
			   bot->getCurrentState() == L"ATTACK LEFT" ||
		       bot->getCurrentState() == L"ATTACK RIGHT")
			{
					LuaFunction<int> healthDec = luaPState->GetGlobal("healthDec");
					int decFlag = healthDec();

					if(decFlag == 1 && player.undead == false)
					{
						player.setHealth(player.getHealth() - 1);
					}
			}
			}
			bot->updateSprite();
			if (bot->getHealth() == 0){
			   bot->changeToDyingState(bot->getCurrentState());
			   // bot->getB2Body()->SetType(b2_kinematicBody);
			   if(bot->getB2Body() != NULL)
			   {
				 bot->getPhysicalProperties()->setX(bot->getB2Body()->GetPosition().x * 5.0f);
				 bot->getPhysicalProperties()->setY(bot->getB2Body()->GetPosition().y * -5.0f);
				 game->getGSM()->getWorld()->boxWorld->DestroyBody(bot->getB2Body());
				  bot->setB2Body(NULL);
			   }
				if(bot->getDyingCounter() == 60)
				{
					// game->getGSM()->getWorld()->boxWorld->DestroyBody(bot->getB2Body());
					botIterator=bots.erase(botIterator);
					if (botIterator==bots.end()) break;
				}
				 //bot = (*botIterator);
			}
			botIterator++;
		}
	}
}