#pragma once
#include "sssf\gsm\sprite\TopDownSprite.h"

class Tree: public TopDownSprite
{
private:
	int spawnRate;
	int spawnFrameCounter;
	int offsetX;
	int offsetY;

public:
	Tree(){spawnRate = 300; spawnFrameCounter = 0;}
	int getSpawnRate() { return spawnRate; }
	int getSpawnFrameCounter() { return spawnFrameCounter; }
	int getOffsetX() { return offsetX; }
	int getOffsetY() { return offsetY; }
	void setOffsetX(int initOffsetX) { offsetX = initOffsetX; }
	void setOffsetY(int initOffsetY) { offsetY = initOffsetY; }
	void resetSpawnFrameCounter() { spawnFrameCounter = spawnRate; }
	void updateSprite();
	void changeFrame();
};