#include "bugs\BugsContactListener.h"
#include "bugs\BugsGame.h"
#include "sssf\input\GameInput.h"

void BugsContactListener::BeginContact(b2Contact* contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
		TopDownSprite* t1 = static_cast<TopDownSprite*>(bodyUserData1);
		TopDownSprite* t2 = static_cast<TopDownSprite*>(bodyUserData2);
		
		if(t1!= NULL && t2 != NULL)
		{
			float x1 = t1->getB2Body()->GetPosition().x * 5;
			float y1 = t1->getB2Body()->GetPosition().y * -5;
			float x2 = t2->getB2Body()->GetPosition().x * 5;
			float y2 = t2->getB2Body()->GetPosition().y * -5;

			int diffX =(int) x2 - x1;
			int diffY =(int) y2 - y1;

			// t1's bottom edge collides t2's upper edge.
			if(diffX > -64 && diffX < 64 && diffY > (64 - RADII)  && diffY < (64 + RADII))
			{
				e1 = 1;
				e2 = 0;

				if(!t1->getIsPlayer())
				{
					t1->setCurrentState(L"ATTACK DOWN");
					game->getInput()->wKeyDisabled = true;
				}else{
					t2->setCurrentState(L"ATTACK UP");
					game->getInput()->sKeyDisabled = true;
				}
			}else if(diffX > -64 && diffX < 64 && diffY > (-64 - RADII) && diffY < (-64 + RADII))
			{
				// t1's upper edge vs t2's bottom edge
				e1 = 0;
				e2 = 1;

				if(!t1->getIsPlayer())
				{
					// t1 is enemy.
					t1->setCurrentState(L"ATTACK UP");
					game->getInput()->sKeyDisabled = true;
				}else{
					t2->setCurrentState(L"ATTACK DOWN");
					game->getInput()->wKeyDisabled = true;
				}
			}else if(diffX > (-64 - RADII) && diffX < (-64 + RADII) && diffY > -64 && diffY < 64)
			{
				// t1's left edge vs t2's right edge
				e1 = 2;
				e2 = 3;

				if(!t1->getIsPlayer())
				{
					t1->setCurrentState(L"ATTACK LEFT");
					game->getInput()->dKeyDisabled = true;
				}else{
					t2->setCurrentState(L"ATTACK RIGHT");
					game->getInput()->aKeyDisabled = true;
				}
			}else if(diffX > (64 - RADII) && diffX < (64 + RADII) && diffY > -64 && diffY < 64)
			{
				e1 = 3;
				e2 = 2;
				if(!t1->getIsPlayer())
				{
					t1->setCurrentState(L"ATTACK RIGHT");
					game->getInput()->aKeyDisabled = true;
				}else{
					t2->setCurrentState(L"ATTACK LEFT");
					game->getInput()->dKeyDisabled = true;
				}
			}
			 (t1->getHitObject())[e1] = true;
			 (t2->getHitObject())[e2] = true;
		}
	/*
    if (bodyUserData)
		static_cast<TopDownSprite*>( bodyUserData )->beginContact();

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<TopDownSprite*>( bodyUserData )->beginContact();
	*/
}

void BugsContactListener::EndContact(b2Contact* contact) 
{
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
		TopDownSprite* t1 = static_cast<TopDownSprite*>(bodyUserData1);
		TopDownSprite* t2 = static_cast<TopDownSprite*>(bodyUserData2);

		if(t1 != NULL && t2 != NULL)
		{
			if(t1->getIsPlayer()){
				if(t2->getCurrentState() == L"ATTACK UP"){
					t2->setCurrentState(L"IDLE UP");
				}else if(t2->getCurrentState() == L"ATTACK DOWN"){
					t2->setCurrentState(L"IDLE DOWN");
				}else if(t2->getCurrentState() == L"ATTACK RIGHT"){
					t2->setCurrentState(L"IDLE RIGHT");
				}else if(t2->getCurrentState() == L"ATTACK LEFT"){
					t2->setCurrentState(L"IDLE LEFT");
				}
			}else{
				if(t1->getCurrentState() == L"ATTACK UP"){
					t1->setCurrentState(L"IDLE UP");
				}else if(t1->getCurrentState() == L"ATTACK DOWN"){
					t1->setCurrentState(L"IDLE DOWN");
				}else if(t1->getCurrentState() == L"ATTACK RIGHT"){
					t1->setCurrentState(L"IDLE RIGHT");
				}else if(t1->getCurrentState() == L"ATTACK LEFT"){
					t1->setCurrentState(L"IDLE LEFT");
				}
			}
			(t1->getHitObject())[e1] = false;
			(t2->getHitObject())[e2] = false;
		}
}