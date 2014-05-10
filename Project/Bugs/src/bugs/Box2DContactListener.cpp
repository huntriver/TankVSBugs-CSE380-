#include "bugs\Box2DContactListener.h"
#include "bugs\BugsSpriteType.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\ai\bots\RandomBot.h"

void Box2DContactListener::BeginContact(b2Contact* contact)
{
	   TopDownSprite* t1 = static_cast<TopDownSprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
	   TopDownSprite* t2 = static_cast<TopDownSprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
	   
	   if(t1 == NULL && t2 != NULL)
	   {
		   if(t2->getSpriteType()->getSpriteTypeID() == TYPE_BULLET)
				t2->setHealth(0);
		   else if(t2->getSpriteType()->getSpriteTypeID() == TYPE_ANT)
		   {
			   RandomBot* b2 = (RandomBot*)t2;
			   if(b2->isAttempApproach())
				   b2->setApproachFailed(true);
			   if(b2->getRotationInRadians() == 0)
				   b2->setUpEdgeCC(b2->getUpEdgeCC() + 1);
			   else if(b2->getRotationInRadians() == PI)
				   b2->setDownEdgeCC(b2->getDownEdgeCC() + 1);
			   else if(b2->getRotationInRadians() == -PI/2.0f)
				   b2->setLeftEdgeCC(b2->getLeftEdgeCC() + 1);
			   else if(b2->getRotationInRadians() == PI/2.0f)
				   b2->setRightEdgeCC(b2->getRightEdgeCC() + 1);
		   }
	   }else if(t2 == NULL && t1 != NULL)
	   {
		   if(t1->getSpriteType()->getSpriteTypeID() == TYPE_BULLET)
			   t1->setHealth(0);
		   else if(t1->getSpriteType()->getSpriteTypeID() == TYPE_ANT)
		   {
			   RandomBot* b1 = (RandomBot*)t1;
			   if(b1->isAttempApproach())
				   b1->setApproachFailed(true);
			   if(b1->getRotationInRadians() == 0)
				   b1->setUpEdgeCC(b1->getUpEdgeCC() + 1);
			   else if(b1->getRotationInRadians() == PI)
				   b1->setDownEdgeCC(b1->getDownEdgeCC() + 1);
			   else if(b1->getRotationInRadians() == -PI/2.0f)
				   b1->setLeftEdgeCC(b1->getLeftEdgeCC() + 1);
			   else if(b1->getRotationInRadians() == PI/2.0f)
				   b1->setRightEdgeCC(b1->getRightEdgeCC() + 1);
		   }
	   }else if(t1 != NULL && t2 != NULL)
	   {
		   if(t1->getSpriteType()->getSpriteTypeID() == TYPE_TANK && 
			  t2->getSpriteType()->getSpriteTypeID() == TYPE_ANT)
		   {
			   beginTankBugContact(t1, t2);
		   }else if(t1->getSpriteType()->getSpriteTypeID() == TYPE_ANT &&
			   t2->getSpriteType()->getSpriteTypeID() == TYPE_TANK)
		   {
			   beginTankBugContact(t2, t1);
		   }else if(t1->getSpriteType()->getSpriteTypeID() == TYPE_BULLET &&
			   (t2->getSpriteType()->getSpriteTypeID() == TYPE_ANT || t2->getSpriteType()->getSpriteTypeID() == TYPE_TREE))
		   {
			   t1->setHealth(0);
			   t2->decHP(t1->getAttack());
			   ((RandomBot*)t2)->setFightBack(true);
		   }else if((t1->getSpriteType()->getSpriteTypeID() == TYPE_ANT || t1->getSpriteType()->getSpriteTypeID() == TYPE_TREE)&&
			   t2->getSpriteType()->getSpriteTypeID() == TYPE_BULLET)
		   {
			   t1->decHP(t2->getAttack());
			    ((RandomBot*)t1)->setFightBack(true);
			   t2->setHealth(0);
		   }
	   }
}

void Box2DContactListener::EndContact(b2Contact* contact)
{	
	 TopDownSprite* t1 = static_cast<TopDownSprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
	 TopDownSprite* t2 = static_cast<TopDownSprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

	 if(t1 == NULL && t2 != NULL)
	 {
		 if(t2->getSpriteType()->getSpriteTypeID() == TYPE_ANT)
		 {
			 ((RandomBot*)t2)->setUpEdgeCC(0);
			 ((RandomBot*)t2)->setDownEdgeCC(0);
			 ((RandomBot*)t2)->setLeftEdgeCC(0);
			 ((RandomBot*)t2)->setRightEdgeCC(0);
		 }
	 }else if(t1 != NULL && t2 == NULL)
	 {
		 if(t1->getSpriteType()->getSpriteTypeID() == TYPE_ANT)
		 {
			 ((RandomBot*)t1)->setUpEdgeCC(0);
			 ((RandomBot*)t1)->setDownEdgeCC(0);
			 ((RandomBot*)t1)->setLeftEdgeCC(0);
			 ((RandomBot*)t1)->setRightEdgeCC(0);
		 }
	 }else if(t1 != NULL && t2 != NULL)
	 {
		   if(t1->getSpriteType()->getSpriteTypeID() == TYPE_TANK && 
			  t2->getSpriteType()->getSpriteTypeID() == TYPE_ANT)
		   {
			   t2->setCurrentState(L"IDLE");
		   }else if(t1->getSpriteType()->getSpriteTypeID() == TYPE_ANT &&
			   t2->getSpriteType()->getSpriteTypeID() == TYPE_TANK)
		   {
			   t1->setCurrentState(L"IDLE");
		   }
	}
}

void Box2DContactListener::beginTankBugContact(TopDownSprite* player, TopDownSprite* bug)
{
	float pX = player->getB2Body()->GetPosition().x * 5.0f;
	float pY = player->getB2Body()->GetPosition().y * -5.0f;
	float bX = bug->getB2Body()->GetPosition().x * 5.0f;
	float bY = bug->getB2Body()->GetPosition().y * -5.0f;
	float diffX, diffY;

	diffX = pX - bX;
	diffY = pY - bY;

	if(abs(diffX) > abs(diffY))
	{
		if(pX > bX){
			bug->setRotationInRadians(PI/2.0f);
			bug->setCurrentState(L"ATTACK");
			// player->setLeftEdgeCC(player->getLeftEdgeCC() + 1);
			// bug->setRightEdgeCC(bug->getRightEdgeCC() + 1);
		}else if(pX < bX){
			bug->setRotationInRadians(-PI/2.0f);
			bug->setCurrentState(L"ATTACK");
			// player->setRightEdgeCC(player->getRightEdgeCC() + 1);
			// bug->setLeftEdgeCC(bug->getLeftEdgeCC() + 1);
		}else{
			// This is an error
		}
	}else if(abs(diffX) < abs(diffY))
	{
		if(pY < bY){
			bug->setRotationInRadians(0);
			bug->setCurrentState(L"ATTACK");
		}else if(pY > bY){
			bug->setRotationInRadians(PI);
			bug->setCurrentState(L"ATTACK");
		}
	}else{
		// They collide in corner.
	}
}