#pragma once
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\ai\Bot.h"

class Tree: public TopDownSprite
{
private:
	int spawnRate;
	int spawnFrameCounter;
	int spawnRateDec;
	int offsetX;
	int offsetY;
	int interval;
	int intervalFrameCounter;
	bool maxSpawnRate;
	list<Bot*> dummyBots;
	list<Bot*>::iterator dummyBotsIterator;
public:
	Tree(){spawnRate = 300; spawnFrameCounter = 0;intervalFrameCounter = 0;maxSpawnRate=false;}
	~Tree();
	int getSpawnRate() { return spawnRate; }
	int getSpawnFrameCounter() { return spawnFrameCounter; }
	int getOffsetX() { return offsetX; }
	int getOffsetY() { return offsetY; }
	int getInterval() { return interval; }
	int getIntervalFrameCounter() { return intervalFrameCounter; }
	bool isMaxSpawnRate() { return maxSpawnRate; }
	void setOffsetX(int initOffsetX) { offsetX = initOffsetX; }
	void setOffsetY(int initOffsetY) { offsetY = initOffsetY; }
	void resetSpawnFrameCounter() { spawnFrameCounter = spawnRate; }
	void setIterval(int initInterval){ interval = initInterval; }
	void setMaxSpawnRate(bool flag) { maxSpawnRate = flag; }
	void resetIntervalFrameCounter() { intervalFrameCounter = 0; }
	void updateSprite();
	void changeFrame();
	void increaseSpawnRate();
	void addBot(Bot* botToAdd){ dummyBots.push_back(botToAdd); }
	void initSpawnRate(int initSpawnRate){ spawnRate = initSpawnRate; }
	void initSpanRateDec(int initSpawnRateDec) { spawnRateDec = initSpawnRateDec; }
	void resetDummyBotsIterator(){ dummyBotsIterator = dummyBots.begin(); }
	list<Bot*>::iterator getDumyBotIterator() { return dummyBotsIterator; }
	void incDummyBotsIterator() { dummyBotsIterator++; }
};