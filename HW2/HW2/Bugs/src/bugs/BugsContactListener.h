#include "Box2D\Box2D.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\game\game.h"

class BugsContactListener:public b2ContactListener
{
	public:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		void setGame(Game* initGame){game = initGame;}

	private:
		int e1;
		int e2;
		Game* game;
};
