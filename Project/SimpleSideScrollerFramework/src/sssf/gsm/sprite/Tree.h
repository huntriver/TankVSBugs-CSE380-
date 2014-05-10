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
	Tree(){spawnRate=350; spawnFrameCounter=350;}
	int getSpawnRate() { return spawnRate; }
	int getSpawnFrameCounter() { return spawnFrameCounter; }
	int getOffsetX() { return offsetX; }
	int getOffsetY() { return offsetY; }
	void initOffsetX(int initOffsetX) { offsetX = initOffsetX; }
	void initOffsetY(int initOffsetY) { offsetY = initOffsetY; }
	void updateSprite();
};