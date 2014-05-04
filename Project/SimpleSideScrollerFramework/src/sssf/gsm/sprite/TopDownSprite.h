#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class TopDownSprite : public AnimatedSprite
{
protected:
	// USED TO RENDER A ROTATED SPRITE, NOT INVOLVED IN PHYSICS
	float rotationInRadians;
	wstring direction;

public:	
	float getRotationInRadians()	
	{ return rotationInRadians; }	
	void setRotationInRadians(float initRotation)
	{ rotationInRadians = initRotation; }
	wstring getDirection(){return direction;}
	void setDirection(wstring initDirection);
	void updateSprite();
	void beginContact();
};