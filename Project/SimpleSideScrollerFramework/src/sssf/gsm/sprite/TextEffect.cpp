#include "sssf\gsm\sprite\TextEffect.h"

void TextEffect::updateSprite()
{
	AnimatedSprite::updateSprite();
	alpha = alpha - 2;
	if(alpha <= 0)
		markForRemoval = true;
}