
#include "sssf\gsm\ai\bots\RandomSpider.h"
#include "sssf\gsm\sprite\bullet.h"

void RandomSpider::attackPlayer(Game* game)
{
	float maxV;
	int randNum = rand() % 12 + 1;
	wstring bCurrentState;
	if(randNum == 5)
	{
		maxV = 30.0f;
		bCurrentState = L"NET";
	}else
	{
		maxV = 40.0f;
		bCurrentState = L"ACID";
	}
	float playerX = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().x * 5.0f;
	float playerY = game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().y * -5.0f;
	float botX = body->GetPosition().x * 5.0f;
	float botY = body->GetPosition().y * -5.0f;
	float diffX = playerX - botX;
	float diffY = playerY - botY;
	float distance = sqrt((diffX * diffX) + (diffY * diffY));
	float unitX = diffX/distance;
	float unitY = diffY/distance;
	float vX = unitX * 40.0f;
	float vY = -unitY * 40.0f;

	if(abs(vX) > abs(vY))
	{
		if(diffX > 0)
			rotationInRadians = PI/2.0f;
		else
			rotationInRadians = -PI/2.0f;

	}else{
		if(diffY > 0)
			rotationInRadians = PI;
		else
			rotationInRadians = 0;
	}

	Bullet *bullet = new Bullet();
	AnimatedSpriteType *bulletSpriteType = game->getGSM()->getSpriteManager()->getSpriteType(11);
	bullet->setSpriteType(bulletSpriteType);
	bullet->setCurrentState(bCurrentState);
	bullet->setAlpha(255);
	bullet->setHealth(120);
	bullet->setAttack(attack);
	bullet->setOwner(this);
	// bullet->setRotationInRadians(calcBulletRotation(vX,-vY));
	game->getGSM()->getSpriteManager()->addBullet(bullet);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	float x = body->GetPosition().x;
	float y = body->GetPosition().y;
	// float r=getPlayer()->getRotationInRadians();
	if (rotationInRadians == PI/2.0f) 
	{
		x += (getSpriteType()->getTextureHeight()*0.5f/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureWidth() + 1)/2.0f)/5.0f;
		//vx = 120.0f;
	}else if(rotationInRadians == PI){
		y -= (getSpriteType()->getTextureWidth()*0.5f/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureHeight() + 1)/2.0f)/5.0f;
		//		vy =- 120.0f;
	}else if (rotationInRadians == -PI/2.0f){
		x -=  (getSpriteType()->getTextureHeight()*0.5f/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureWidth() + 1)/2.0f)/5.0f;
		//		vx = -120.0f;
	}else{
		y += (getSpriteType()->getTextureWidth()*0.5f/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureHeight() + 1/2.0f))/5.0f;
		//		vy = 120.0f;
	}
	bodyDef.position.Set(x, y);
	b2Body* body = (game->getGSM()->getWorld()->boxWorld)->CreateBody(&bodyDef);
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((bullet->getSpriteType()->getTextureWidth()/2.0f)/5.0f,(bullet->getSpriteType()->getTextureHeight()/2.0f)/5.0f);
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	fixtureDef.friction = 0.0f;
	fixtureDef.filter.categoryBits = 0x0006;
	fixtureDef.filter.maskBits = 0x0001|0x0002;
	// Add the shape to the body.
	body->SetLinearVelocity(b2Vec2(vX,vY));
	body->CreateFixture(&fixtureDef);
	bullet->setB2Body(body);
	body->SetUserData(bullet);
}

float RandomSpider::calcBulletRotation(float vX, float vY)
{
	float epsilon = 0.00001f;
	if (fabs(vY) < epsilon)
	{
		// IF X ISN'T MOVING EITHER, LEAVE IT WHAT IT IS
		// AND PUT IT INTO AN IDLE STATE
		if (fabs(vX) > epsilon)
		{
			if (vX < 0.0f)
			{
				return PI;
			}
			else
				return 0.0f;
		}
	}
	else
	{
		float tanTheta = vY/vX;
		float bulletRotation = atan(tanTheta);
		if (vX < 0.0f)
		{
			if (vY < 0.0f)
				return bulletRotation += PI;
			else
				return bulletRotation -= PI;
		}
	}
}