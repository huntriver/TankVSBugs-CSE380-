#include "sssf\gsm\sprite\Effect.h"

class TextEffect : public Effect
{
public:
	TextEffect(){rotationInRadians = 0.0f;}
	void updateSprite();
};