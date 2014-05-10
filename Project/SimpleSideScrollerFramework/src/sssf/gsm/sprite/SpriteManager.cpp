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
#include "sssf\gsm\sprite\FireEffect.h"

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

	if(sprite->getSpriteType()->getSpriteTypeID() == 3 || 
		sprite->getSpriteType()->getSpriteTypeID() == 5 ||
		sprite->getSpriteType()->getSpriteTypeID() == 6)
	{
		if(viewport->areWorldCoordinatesInViewport(
			pp->getX(),pp->getY(),spriteType->getTextureWidth(),
			spriteType->getTextureHeight()))
		{
			RenderItem itemToAdd;
			itemToAdd.id = sprite->getFrameIndex();
			renderList->addRenderItem(sprite->getCurrentImageID(),
				pp->round(pp->getX()-spriteType->getTextureWidth()/2.0f-viewport->getViewportX()),
				pp->round(pp->getY() - spriteType->getTextureHeight()/2.0f-viewport->getViewportY()),0,
				sprite->getAlpha(),spriteType->getTextureWidth(),
				spriteType->getTextureHeight(), rotation);
		}
	}else
	{
		int leftX = pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2.0f);
		int topY = pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2.0f);
		int rightX = pp->round((body->GetPosition().x)*5.0f+spriteType->getTextureWidth()/2.0f);
		int downY = pp->round((-1)*(body->GetPosition().y)*5.0f+spriteType->getTextureHeight()/2.0f);
		// IS THE SPRITE VIEWABLE?
		if (viewport->areWorldCoordinatesInViewport(	
			leftX,
			topY,
			spriteType->getTextureWidth(),
			spriteType->getTextureHeight()))
		{
			// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
			int width =spriteType->getTextureWidth();
			int height = spriteType->getTextureHeight();
			int x = pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2.0f-viewport->getViewportX());
			int y = pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2.0f-viewport->getViewportY());
			RenderItem itemToAdd;
			itemToAdd.id = sprite->getFrameIndex();

			renderList->addRenderItem(sprite->getCurrentImageID(), x, y,0, sprite->getAlpha(), width, height,rotation);
			/*
			if(healthDisplay && (spriteType->getSpriteTypeID() == 0 || spriteType->getSpriteTypeID() == 1))
			{
				int imageId;
				if(sprite->getSpriteType()->getSpriteTypeID() == 0)
					imageId = getSpriteType(4)->getAnimationFrameID(L"IDLE", 0);
				else
					imageId = getSpriteType(4)->getAnimationFrameID(L"MOVE", 0);
				for(int i = 0; i < sprite->getHealth(); ++i)
				{
					if(i != sprite->getHealth() - 1)
					{
					renderList->addRenderItem(imageId,
						pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2-viewport->getViewportX())+i*getSpriteType(4)->getTextureWidth(),
						pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2-viewport->getViewportY())-getSpriteType(4)->getTextureHeight(),
						0,
						255,getSpriteType(4)->getTextureWidth(),getSpriteType(4)->getTextureHeight(),0);
					}else
					{
						float factor = sprite->getHP()/100.0f;
						renderList->addRenderItem(imageId,
						pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2-viewport->getViewportX())+i*getSpriteType(4)->getTextureWidth(),
						pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2-viewport->getViewportY())-getSpriteType(4)->getTextureHeight(),
						0,
						255,(int)(factor*getSpriteType(4)->getTextureWidth()),getSpriteType(4)->getTextureHeight(),0);
					}
				}
			}*/
		}
	}
}

void SpriteManager::addSpriteHealthToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	b2Body* body = sprite->getB2Body();
	PhysicalProperties *pp = sprite->getPhysicalProperties();
	float rotation = sprite->getRotationInRadians();

	int imageId;
	if(sprite->getSpriteType()->getSpriteTypeID() == 0)
		imageId = getSpriteType(4)->getAnimationFrameID(L"IDLE", 0);
	else
		imageId = getSpriteType(4)->getAnimationFrameID(L"MOVE", 0);
	for(int i = 0; i < sprite->getHealth(); ++i)
	{
		if(i != sprite->getHealth() - 1)
		{
			renderList->addRenderItem(imageId,
			pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2-viewport->getViewportX())+i*getSpriteType(4)->getTextureWidth(),
			pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2-viewport->getViewportY())-getSpriteType(4)->getTextureHeight(),
			0,255,getSpriteType(4)->getTextureWidth(),getSpriteType(4)->getTextureHeight(),0);
		}else
		{
			float factor = sprite->getHP()/100.0f;
			renderList->addRenderItem(imageId,
			pp->round((body->GetPosition().x)*5.0f-spriteType->getTextureWidth()/2-viewport->getViewportX())+i*getSpriteType(4)->getTextureWidth(),
			pp->round((-1)*(body->GetPosition().y)*5.0f-spriteType->getTextureHeight()/2-viewport->getViewportY())-getSpriteType(4)->getTextureHeight(),
			0,255,(int)(factor*getSpriteType(4)->getTextureWidth()),getSpriteType(4)->getTextureHeight(),0);
		}
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

		list<Effect*>::iterator dyingEffectIterator;
		dyingEffectIterator = dyingEffects.begin();
		while(dyingEffectIterator != dyingEffects.end())
		{
			Effect* effect = (*dyingEffectIterator);
			addSpriteToRenderList(effect, renderList, viewport);
			dyingEffectIterator++;
		}

		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		botIterator = bots.begin();
		while (botIterator != bots.end())
		{			
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}
		list<TopDownSprite*>::iterator bulletIterator;
		bulletIterator = bullets.begin();
		while (bulletIterator != bullets.end())
		{			
			TopDownSprite *bullet = (*bulletIterator);
			addSpriteToRenderList(bullet, renderList, viewport);
			bulletIterator++;
		}

		list<Tree*>::iterator treeIterator;
		treeIterator = trees.begin();
		while (treeIterator != trees.end())
		{
			Tree *tree = (*treeIterator);
			addSpriteToRenderList(tree, renderList, viewport);
			treeIterator++;
		}

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);

		list<Effect*>::iterator effectIterator;
		effectIterator = effects.begin();
		while(effectIterator != effects.end())
		{
			Effect* effect = (*effectIterator);
			addSpriteToRenderList(effect, renderList, viewport);
			effectIterator++;
		}

		if(healthDisplay)
		{
			addSpriteHealthToRenderList(&player, renderList, viewport);
			botIterator = bots.begin();
			while (botIterator != bots.end())
			{			
				Bot *bot = (*botIterator);
				addSpriteHealthToRenderList(bot, renderList, viewport);
				botIterator++;
			}
			treeIterator = trees.begin();
			while (treeIterator != trees.end())
			{
				Tree* tree = (*treeIterator);
				addSpriteHealthToRenderList(tree, renderList, viewport);
				treeIterator++;
			}
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
	dummyBots.push_back(botToAdd);
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
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
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

	list<Effect*>::iterator effectsIt = effects.begin();
	while(effectsIt != effects.end())
	{
		list<Effect*>::iterator tempIt = effectsIt;
		effectsIt++;
		Effect *effectToDelete = (*tempIt);
		if(effectToDelete != &fEffect)
			delete effectToDelete;
	}
	effects.clear();

	effectsIt = dyingEffects.begin();
	while(effectsIt != dyingEffects.end())
	{
		list<Effect*>::iterator tempIt = effectsIt;
		effectsIt++;
		Effect *effectToDelete = (*tempIt);
		delete effectToDelete;
	}
	dyingEffects.clear();

	list<Tree*>::iterator treeIt = trees.begin();
	while (treeIt != trees.end())
	{
		list<Tree*>::iterator tempIt = treeIt;
		treeIt++;
		Tree *treeToDelete = (*tempIt);
		delete treeToDelete;
	}

	trees.clear();
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
	
	// list<Bot*>::iterator dummyBotIterator;
	
	timeLeft--;
	if(timeLeft <= 0)
	{
		if(dummyBotsIterator != dummyBots.end())
		{
			Bot* botToAdd = *dummyBotsIterator;
			bots.push_back(botToAdd);
			dummyBotsIterator++;
		}
		timeLeft = 100;
	}
	
	/*
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
	*/
	// FIRST LET'S DO THE NECESSARY PATHFINDING
	// pathfinder->updatePath(&player);

    /*
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
		// pathfinder->updatePath(bot);
		botIterator++;
	}
	*/

	// THEN UPDATE THE PLAYER SPRITE ANIMATION FRAME/STATE/ROTATION
	player.updateSprite();

	// NOW UPDATE THE REST OF THE SPRITES ANIMATION FRAMES/STATES/ROTATIONS
	game->getInput()->wKeyDisabled = false;
	game->getInput()->sKeyDisabled = false;
	game->getInput()->dKeyDisabled = false;
	game->getInput()->aKeyDisabled = false;
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		if(fEffect.getCurrentState() != L"IDLE")
		{
			int attackDistance = player.getSpriteType()->getTextureWidth()/2.0f + fEffect.getSpriteType()->getTextureHeight()/2.0f + bot->getSpriteType()->getTextureHeight()/2.0f;
			if(((((player.getRotationInRadians() == 0 && bot->getRotationInRadians() == PI) ||
			(player.getRotationInRadians() == PI && bot->getRotationInRadians() == 0))&&
			abs(player.getB2Body()->GetPosition().y*-5.0f- bot->getB2Body()->GetPosition().y*-5.0f) <= attackDistance&&
			abs(player.getB2Body()->GetPosition().x*5.0f- bot->getB2Body()->GetPosition().x*5.0f) <= attackDistance))||
			((((player.getRotationInRadians() == PI/2.0f && bot->getRotationInRadians() == -PI/2.0f) ||
			(player.getRotationInRadians() == -PI/2.0f && bot->getRotationInRadians() == PI/2.0f))&&
			abs(player.getB2Body()->GetPosition().x*5.0f- bot->getB2Body()->GetPosition().x*5.0f) <= attackDistance &&
			abs(player.getB2Body()->GetPosition().y*-5.0f- bot->getB2Body()->GetPosition().y*-5.0f) <= attackDistance))){
					bot->decHP(fEffect.getAttack());
			}
		}
		bot->updateSprite();
		if(bot->getMarkForRemoval()){
			addDyingEffect(bot);
			game->getGSM()->getWorld()->boxWorld->DestroyBody(bot->getB2Body());
			delete bot;
			botIterator = bots.erase(botIterator);
		}else
		{
			if(bot->getCurrentState() == L"ATTACK")
			{
				player.decHP(bot->getAttack());
			}
			((RandomBot*)bot)->think(game);
			botIterator++;
		}
	}

	list<TopDownSprite*>::iterator bulletIterator;
	bulletIterator = bullets.begin();
	
	while(bulletIterator != bullets.end())
	{
		TopDownSprite *bullet = (*bulletIterator);
		bullet->setHealth(bullet->getHealth() - 1);
		bullet->updateSprite();

		if(bullet->getMarkForRemoval())
		{
			/*
			if(effects.size() >= 5)
			{
				list<Effect*>::iterator it = effects.begin();
				effects.erase(it);
			}*/
			addBulletEffect(bullet);
			game->getGSM()->getWorld()->boxWorld->DestroyBody(bullet->getB2Body());
			delete bullet;
			bulletIterator = bullets.erase(bulletIterator);
		}else
			bulletIterator++;
	}

	list<Effect*>::iterator effectIterator;
	effectIterator = effects.begin();
	while(effectIterator != effects.end())
	{
		Effect* effect = (*effectIterator);
		effect->updateSprite();
		
		if(effect->getMarkForRemoval())
		{
			delete effect;
			effectIterator = effects.erase(effectIterator);
		}else
			effectIterator++;
	}

	effectIterator = dyingEffects.begin();
	while(effectIterator != dyingEffects.end())
	{
		Effect* effect = (*effectIterator);
		effect->updateSprite();

		if(effect->getMarkForRemoval())
		{
			delete effect;
			effectIterator = dyingEffects.erase(effectIterator);
		}else
			effectIterator++;
	}
}

void SpriteManager::addBulletEffect(TopDownSprite* bullet)
{
	AnimatedSpriteType *effectSpriteType = getSpriteType(3);
	Effect* effect = new Effect();
	float x = bullet->getB2Body()->GetPosition().x * BOX2D_SCALE;
	float y = bullet->getB2Body()->GetPosition().y * -BOX2D_SCALE;
	effect->setSpriteType(effectSpriteType);
	effect->setCurrentState(L"IDLE");
	effect->setHealth(1000);
	effect->setAlpha(255);
	effect->setEffectTimes(1);
	effect->getPhysicalProperties()->setX(x);
	effect->getPhysicalProperties()->setY(y);
	effects.push_back(effect);
}

void SpriteManager::addDyingEffect(TopDownSprite* sprite)
{
	AnimatedSpriteType *dyingEffectSpriteType = getSpriteType(5);
	Effect* dyingEffect = new Effect();
	float x = sprite->getB2Body()->GetPosition().x * BOX2D_SCALE;
	float y = sprite->getB2Body()->GetPosition().y * -BOX2D_SCALE;
	dyingEffect->setSpriteType(dyingEffectSpriteType);
	dyingEffect->setCurrentState(L"IDLE");
	dyingEffect->setHealth(1000);
	dyingEffect->setAlpha(255);
	dyingEffect->setEffectTimes(1);
	dyingEffect->getPhysicalProperties()->setX(x);
	dyingEffect->getPhysicalProperties()->setY(y);
	dyingEffects.push_back(dyingEffect);
}

void SpriteManager::makeRandomBot(Game *game, float initX, float initY)
{
//	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
//	Physics *physics = game->getGSM()->getPhysics();
	RandomBot *bot = new RandomBot();
	//physics->addCollidableObject(bot);
	//PhysicalProperties *pp = bot->getPhysicalProperties();
	//pp->setPosition(initX, initY);
	bot->setSpriteType(getSpriteType(1));
	bot->setCurrentState(L"IDLE");
	bot->setDirection(L"UP");
	bot->setAlpha(255);
	bot->setHealth((int)(getSpriteType(1)->getTextureWidth()/getSpriteType(4)->getTextureWidth()));
	bot->setAttack(0.2);
	int playerW = player.getSpriteType()->getTextureWidth()/2;
	float randNum = rand()% playerW;
	if(getBotSize() % 2 == 0)
		bot->initBot(30, 300, 50/1.4f, true,randNum);
	else
		bot->initBot(30, 300, 50/1.4f, false,-randNum);
	addBot(bot);
	//bot->affixTightAABBBoundingVolume();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(initX/5.0f, -initY/5.0f);
	b2Body* body = (game->getGSM()->getWorld()->boxWorld)->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(getSpriteType(1)->getTextureWidth()/10.0f, getSpriteType(1)->getTextureHeight()/10.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = 0x0004;
	fixtureDef.filter.maskBits = 0x0001|0x0008|0x0002;
	// Add the shape to the body.
	body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
	body->CreateFixture(&fixtureDef);
	bot->setB2Body(body);
	body->SetUserData(bot);
}