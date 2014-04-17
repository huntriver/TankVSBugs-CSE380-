#include "Box2D\Box2D.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
class box2DContactListener:public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{

        //eck if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if ( bodyUserData )
            static_cast<TopDownSprite*>( bodyUserData )->beginContact();

        //eck if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyUserData )
            static_cast<TopDownSprite*>( bodyUserData )->beginContact();

    }

   void EndContact(b2Contact* contact) {
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
    }
	
};
