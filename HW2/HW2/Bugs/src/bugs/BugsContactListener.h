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
		void respondPlayerBugContact(TopDownSprite* t1, TopDownSprite* t2);
		void respondBugBugContact();
		void respondBulletBugContact();
		void respondBulletWallContact();
		int e1;
		int e2;
		Game* game;
};
