#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

/**
* This is where all the effect goes, such as explosion.
**/
class Effect : public AnimatedSprite
{
	private:
		int effectTimes;
		int effectCounter;
	
	public:
		void setEffectTimes(int initEffectTimes){effectCounter = 0; effectTimes = initEffectTimes;}
		void changeFrame();
		void updateSprite();
};