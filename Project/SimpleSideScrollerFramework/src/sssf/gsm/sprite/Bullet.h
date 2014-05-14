#pragma once

#include "sssf\gsm\sprite\TopDownSprite.h"

class Bullet : public TopDownSprite
{
private:
	TopDownSprite* owner;
public:
	void setOwner(TopDownSprite *initOwner) { owner = initOwner; }
	TopDownSprite* getOwner() { return owner; }
};