#include "sssf\gsm\sprite\FireEffect.h"


void FireEffect::changeFrame()
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState))
	{
		frameIndex = 0;
		if(currentState != L"MOVE")
			effectCounter++;
	}
	if(effectCounter == 1)
	{
		setCurrentState(L"MOVE");
		inProgress = true;
	}
	if(effectCounter == 6)
	{
		setCurrentState(L"IDLE");
		inProgress = false;
		stop = false;
		start = false;
	}
}



void FireEffect::updateSprite()
{
	unsigned int duration = spriteType->getDuration(currentState, frameIndex);
	animationCounter++;

	// WE ONLY CHANGE THE ANIMATION FRAME INDEX WHEN THE
	// ANIMATION COUNTER HAS REACHED THE DURATION
	if (animationCounter >= duration)
		changeFrame();

	if(stop && currentState != L"DYING")
	{
		effectCounter = 5;
		setCurrentState(L"DYING");
	}
	if(start && !stop && !inProgress)
	{
		effectCounter = 0;
		setCurrentState(L"ATTACK");
	}
	
	if(start == false && stop == false)
	{
		setCurrentState(L"IDLE");
	}
	
	if(currentState != L"IDLE")
	{
		if(player->getRotationInRadians() == 0)
		{
			pp.setX(player->getB2Body()->GetPosition().x * 5.0f);
			pp.setY(player->getB2Body()->GetPosition().y * -5.0f - spriteType->getTextureHeight()/2.0f - player->getSpriteType()->getTextureHeight()/2.0f);
			rotationInRadians = 0.0f;
		}else if(player->getRotationInRadians() == PI)
		{
			pp.setX(player->getB2Body()->GetPosition().x * 5.0f);
			pp.setY(player->getB2Body()->GetPosition().y * -5.0f + spriteType->getTextureHeight()/2.0f + player->getSpriteType()->getTextureHeight()/2.0f);
			rotationInRadians = PI;
		}else if(player->getRotationInRadians() == PI/2.0f)
		{
			pp.setX(player->getB2Body()->GetPosition().x * 5.0f +  spriteType->getTextureHeight()/2.0f + player->getSpriteType()->getTextureWidth()/2.0f);
			pp.setY(player->getB2Body()->GetPosition().y * -5.0f);
			rotationInRadians = PI/2.0f;
		}else
		{
			pp.setX(player->getB2Body()->GetPosition().x * 5.0f - spriteType->getTextureHeight()/2.0f - player->getSpriteType()->getTextureWidth()/2.0f);
			pp.setY(player->getB2Body()->GetPosition().y * -5.0f);
			rotationInRadians = -PI/2.0f;
		}
	}
}