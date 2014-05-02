/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.cpp

	See AnimatedSprite.h for a class description.
*/

#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
/*
	AnimatedSprite - Default constructor, just sets everything to 0.
*/
AnimatedSprite::AnimatedSprite()  
{
	spriteType = 0;
	frameIndex = 0;
	animationCounter = 0;
	pp.setVelocity(0.0f, 0.0f);
	pp.setAccelerationX(0.0f);
	pp.setAccelerationY(0.0f);
	pp.setPosition(0.0f, 0.0f);
	dead=false;
	hitObject[0] = false; 
	hitObject[1] = false;
	hitObject[2] = false;
	hitObject[3] = false;
	health=5;
	isPlayer = false;
	undead = false;
	collide = false;
	dyingCounter = 0;
}

/*
	Destructor - Nothing to clean up. We don't want to clean up the
	sprite type because it is a shared variable.
*/
AnimatedSprite::~AnimatedSprite() 
{

}


/*
	changeFrame - This method allows for the changing of an image in an 
	animation sequence for a given animation state.
*/
void AnimatedSprite::changeFrame()
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState))
		frameIndex = 0;
}

/*
	getCurrentImageID - This method does the work of retrieving
	the image id that corresponds to this sprite's current state
	and frame index.
*/
unsigned int AnimatedSprite::getCurrentImageID()
{
	return spriteType->getAnimationFrameID(currentState, frameIndex);
}

/*
	setCurrentState - This method sets this sprite to the newState
	state and starts its animtion sequence from the beginning.
*/
void AnimatedSprite::setCurrentState(wstring newState) 
{
	string cs(currentState.begin(), currentState.end());
	string ns(newState.begin(), newState.end());
	if (strcmp(cs.c_str(), ns.c_str()) != 0)
	{
		// SET THE ANIMATINO STATE
		currentState = newState;

		// AND RESET OUR COUNTERS
		animationCounter = 0;
		frameIndex = 0;
	}
}

/*
	updateSprite - To be called every frame of animation. This
    method advances the animation counter appropriately per
	the animation speed. It also updates the sprite location
	per the current velocity.
*/
void AnimatedSprite::updateSprite()
{
	unsigned int duration = spriteType->getDuration(currentState, frameIndex);
	animationCounter++;

	// WE ONLY CHANGE THE ANIMATION FRAME INDEX WHEN THE
	// ANIMATION COUNTER HAS REACHED THE DURATION
	if (animationCounter >= duration)
		changeFrame();
}

void AnimatedSprite::affixTightAABBBoundingVolume()
{
	boundingVolume.setCenterX(pp.getX() + (spriteType->getTextureWidth()/2));
	boundingVolume.setCenterY(pp.getY() + (spriteType->getTextureHeight()/2));
	boundingVolume.setWidth((float)spriteType->getTextureWidth());
	boundingVolume.setHeight((float)spriteType->getTextureHeight());
}
	

void AnimatedSprite::correctToTightBoundingVolume()
{
	pp.setX(boundingVolume.getLeft());
	pp.setY(boundingVolume.getTop());
}

void AnimatedSprite::changeToIdleState(wstring state)
{
	if(state == L"MOVE UP")
	{
		setCurrentState(L"IDLE UP");
	}else if(state == L"MOVE DOWN")
	{
		setCurrentState(L"IDLE DOWN");
	}else if(state == L"MOVE RIGHT")
	{
		setCurrentState(L"IDLE RIGHT");
	}else{
		setCurrentState(L"IDLE LEFT");
	}
}

void AnimatedSprite::changeToDyingState(wstring state)
{
//	if(currentState == L"DYING UP" || currentState == 
	if(state == L"MOVE UP" || state == L"IDLE UP" || state == L"ATTACK UP")
	{
		setCurrentState(L"DYING UP");
	}else if(state == L"MOVE DOWN" || state == L"IDLE DOWN" || state == L"ATTACK DOWN")
	{
		setCurrentState(L"DYING DOWN");
	}else if(state == L"MOVE RIGHT" || state == L"IDLE RIGHT" || state == L"ATTACK RIGHT")
	{
		setCurrentState(L"DYING RIGHT");
	}else if(state == L"MOVE LEFT" || state == L"IDLE LEFT" || state == L"ATTACK LEFT")
	{
		setCurrentState(L"DYING LEFT");
	}
	dyingCounter++;
}