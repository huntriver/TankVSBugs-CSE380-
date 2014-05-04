#include"sssf\gsm\sprite\Effect.h"

void Effect::changeFrame()
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState))
	{
		frameIndex = 0;
		effectCounter++;
	}
}

void Effect::updateSprite()
{
	AnimatedSprite::updateSprite();

	if(effectCounter >= effectTimes)
		markForRemoval = true;
}