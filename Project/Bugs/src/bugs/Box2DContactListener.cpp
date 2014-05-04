#include "bugs\Box2DContactListener.h"
#include "bugs\BugsSpriteType.h"

void Box2DContactListener::BeginContact(b2Contact* contact)
{
	   TopDownSprite* t1 = static_cast<TopDownSprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
	   TopDownSprite* t2 = static_cast<TopDownSprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
	   
	   if(t1 == NULL && t2 != NULL)
	   {
		   if(t2->getSpriteType()->getSpriteTypeID() == TYPE_BULLET)
			   t2->setHealth(0);
	   }else if(t2 == NULL && t1 != NULL)
	   {
		   if(t1->getSpriteType()->getSpriteTypeID() == TYPE_BULLET)
			   t1->setHealth(0);
	   }
}