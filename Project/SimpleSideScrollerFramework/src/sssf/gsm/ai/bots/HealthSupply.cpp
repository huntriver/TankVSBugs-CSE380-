#include "sssf\gsm\ai\bots\HealthSupply.h"
#include "sssf\gsm\state\GameStateManager.h"

void HealthSupply::think(Game* game)
{
	
	if(hostAlive)
	{
	}
	else if(currentState == L"DYING"){
		setCurrentState(L"IDLE");
 		float randX = rand()%7 - 3;
		float randY = rand()%7 - 3;
		float vector = sqrt((randX * randX) + (randY * randY));
		float unitX = randX/vector;
		float unitY = randY/vector;
		float vX = unitX * 35.0f;
		float vY = -unitY * 35.0f;
		body->SetLinearVelocity(b2Vec2(vX,vY));
		// body->ApplyForce(b2Vec2(vX,vY), body->GetWorldCenter(), true);
		// ApplyForce( b2Vec2(0,50), bodies[0]->GetWorldCenter() );
	}else{
		if(currentState == L"IDLE" && health <= 100)
		{
			setCurrentState(L"MOVE");
		}
		float pX = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().x * BOX2D_SCALE;
		float pY = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().y * -BOX2D_SCALE;
		float bX = getB2Body()->GetPosition().x * BOX2D_SCALE;
		float bY = getB2Body()->GetPosition().y * -BOX2D_SCALE;
		if(abs(pX - bX) <= 200 && abs(pY - bY) <= 200)
		{
			float playerX = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().x * 5.0f;
			float playerY = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().y * -5.0f;
			float botX = body->GetPosition().x * 5.0f;
			float botY = body->GetPosition().y * -5.0f;
			float diffX = playerX - botX;
			float diffY = playerY - botY;
			float distance = sqrt((diffX * diffX) + (diffY * diffY));
			float unitX = diffX/distance;
			float unitY = diffY/distance;
			float vX = unitX * 35.0f;
			float vY = -unitY * 35.0f;
			this->body->SetLinearVelocity(b2Vec2(vX, vY));
		}else{
			if(upEdgeCC > 0 || downEdgeCC > 0 || leftEdgeCC > 0 || rightEdgeCC > 0)
			{
				float randX = rand()%7 - 3;
				float randY = rand()%7 - 3;
				float vector = sqrt((randX * randX) + (randY * randY));
				float unitX = randX/vector;
				float unitY = randY/vector;
				float vX = unitX * 35.0f;
				float vY = -unitY * 35.0f;
				body->SetLinearVelocity(b2Vec2(vX,vY));
			}
		}
		health--;
	}
}
