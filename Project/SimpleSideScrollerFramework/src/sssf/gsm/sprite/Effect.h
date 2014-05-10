#pragma once

#include "sssf\gsm\sprite\TopDownSprite.h"

/**
* This is where all the effect goes, such as explosion.
**/
class Effect : public TopDownSprite
{
	protected:
		int effectTimes;
		int effectCounter;
	
	public:
		void setEffectTimes(int initEffectTimes){effectCounter = 0; effectTimes = initEffectTimes;rotationInRadians=0.0f;}
		virtual void changeFrame();
		virtual void updateSprite();
};