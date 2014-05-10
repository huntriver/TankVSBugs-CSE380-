#include "sssf\gsm\sprite\Tree.h"

void Tree::changeFrame()
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState))
	{
		frameIndex = 0;
		if(currentState == L"DYING")
			markForRemoval = true;
	}
}


void Tree::updateSprite()
{
	unsigned int duration = spriteType->getDuration(currentState, frameIndex);
	animationCounter++;

	// WE ONLY CHANGE THE ANIMATION FRAME INDEX WHEN THE
	// ANIMATION COUNTER HAS REACHED THE DURATION
	if (animationCounter >= duration)
		changeFrame();

	if(hp <= 0.0f)
	{
		health = health - 1;
		hp = 100.0f;
	}

	if(health <= 0)
		setCurrentState(L"DYING");
	
	spawnFrameCounter--;
}

