/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.h

	This class manages all of the sprites in a given game level. Note
	that the player sprite is also managed by this class.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\BotRecycler.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\ai\pathfinding\GridPathfinder.h"
#include "sssf\gsm\sprite\Effect.h"
#include "sssf\gsm\sprite\FireEffect.h"
#include "sssf\gsm\sprite\Tree.h"
#include "sssf\gsm\sprite\Bullet.h"
#include "sssf\gsm\ai\bots\HealthSupply.h"
#include"sssf\sound\SDKwavefile.h"
#include<windows.h>
#include<iostream>
#include<xaudio2.h>



class SpriteManager
{
private:
	// IXAudio2* xAudio2Engine;
	// IXAudio2SourceVoice* burningSrcVoice;
	// bool playBurningSound;
	// NOTE THAT MULTIPLE SPRITES MAY SHARE ARTWORK, SO SPRITE TYPES
	// SPECIFIES A TYPE OF SPRITE, OF WHICH THERE MAY BE MANY INSTANCES
	vector<AnimatedSpriteType*> spriteTypes;
	vector<HealthSupply*> dummyHealth;
	// THESE ARE THE BOTS IN THE GAME, LIKE ENEMIES, ROCKETS, OR ANYTHING
	// THAT MOVES AROUND AND IS NOT THE PLAYER
	list<Tree*> trees;
	list<Bot*> bots;
	list<Bot*> dummyBots;
	list<Bot*>::iterator dummyBotsIterator;
	list<Bullet*> bullets;
	list<Effect*>  effects;
	list<Effect*>  dyingEffects;
	FireEffect fEffect;
	// AND THIS IS THE PLAYER. AS-IS, WE ONLY ALLOW FOR ONE PLAYER AT A TIME
	TopDownSprite player;
	short playerBulletCounter;
	// THE BotRecycler MAKES SURE WE DON'T HAVE TO CONSTRUCT BOTS WHENEVER
	// WE NEED TO SPAWN THEM, INSTEAD IT WILL RECYCLE THEM FOR US
	BotRecycler recyclableBots;

	// THIS GUY HELPS SPRITES FIND THEIR WAY. NOTE THAT IT IS CUSTOMIZABLE, SINCE
	// WE MAY BE RENDERING AN ORTHOGRAPHIC MAP OR AN ISOMETRIC ONE
	GridPathfinder *pathfinder;
	bool firstTime;
public:
	// NOTHING TO INIT OR DESTROY
	bool healthDisplay;
	SpriteManager()		{healthDisplay=true;firstTime=true;/*initSoundEngine();initBurningSoundEffect(L"data/sound/burning.wav");playBurningSound=false;*/}
	~SpriteManager()	{}

	// INLINED ACCESSOR 
	int                     getBotSize() {return bots.size();}
	int						getBulletsSize()        { return bullets.size();    }
	int						getNumberOfSprites()	{ return bots.size();		}
	TopDownSprite*			getPlayer()				{ return &player;			}
	FireEffect*            getFireEffect()         { return &fEffect;           }
	list<Bot*>::iterator	getBotsIterator()		{ return bots.begin();		}
	list<Bot*>::iterator	getEndOfBotsIterator()	{ return bots.end();		}
	GridPathfinder*			getPathfinder()			{ return pathfinder;		}

	// METHODS DEFINED IN SpriteManager.cpp
	int addHealth(HealthSupply* hs) {dummyHealth.push_back(hs); return dummyHealth.size()-1;}
	void                addDyingEffect(TopDownSprite* sprite);
	void                addBulletEffect(TopDownSprite* bullet);
	void                addFireEffect(FireEffect* initFireEffect){effects.push_back(initFireEffect);}
	void				addBot(Bot *botToAdd);
	void                addTree(Tree *treeToAdd) {trees.push_back(treeToAdd);};
	void                addBullet(Bullet *bullet);
	void				addSpriteItemsToRenderList(Game *game);
	unsigned int		addSpriteType(AnimatedSpriteType *spriteTypeToAdd);
	void				addSpriteToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void				addSpriteHealthToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void				clearSprites();
	void                initDummyBotIterator(){ dummyBotsIterator = dummyBots.begin();}
	AnimatedSpriteType* getSpriteType(unsigned int typeIndex);
	Bot*				removeBot(Bot *botToRemove);
	void				setPathfinder(GridPathfinder *initPathfinder) { pathfinder = initPathfinder; }
	void				unloadSprites();
	void				update(Game *game);
	void				makeRandomBot(Game *game, float initX, float initY);
	// int                 soundPlay(LPWSTR fileName);
	short               getPlayerBulletCounter(){return playerBulletCounter;};
//	int                initSoundEngine();
//	int                initBurningSoundEffect(LPWSTR fileName);
};