#pragma once
#include "sssf\gsm\sprite\TopDownSprite.h"

class Tree: public TopDownSprite
{
private:
	int spawnRate;
	int spawnFrameCounter;
	int offsetX;
	int offsetY;
	int interval;
	int intervalFrameCounter;
	bool maxSpawnRate;
public:
	Tree(){spawnRate = 300; spawnFrameCounter = 0;intervalFrameCounter = 0;maxSpawnRate=false;}
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
	void resetIntervalFrameCounter() { intervalFrameCounter = 0; }
	void updateSprite();
	void changeFrame();
	void increaseSpawnRate();
};