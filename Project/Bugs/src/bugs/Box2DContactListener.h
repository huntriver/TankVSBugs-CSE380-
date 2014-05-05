#pragma once

#include "Box2D\Box2D.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\game\Game.h"


class Box2DContactListener:public b2ContactListener
{
private:
	// int collisionEdge[2];
	Game* game;
	void beginTankBugContact(TopDownSprite* player, TopDownSprite* bug);
	void endTankBugContact(TopDownSprite* player, TopDownSprite* bug);

	public:
		void BeginContact(b2Contact* contact);
		void setGame(Game* initGame) { game = initGame;}
		void EndContact(b2Contact* contact); 
 /**
        //eck if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if ( bodyUserData )
            static_cast<TopDownSprite*>( bodyUserData )->endContact();

        //eck if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyUserData )
            static_cast<TopDownSprite*>( bodyUserData )->endContact();
**/
	
};
