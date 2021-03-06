/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugsKeyEventHandler.cpp

	See BugsKeyEventHandler.h for a class description.
*/

#include "bugs_VS\stdafx.h"
#include "bugs\BugsGame.h"
#include "bugs\BugsKeyEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\game\WStringTable.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\Bullet.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
#include "bugs\_entityCategory.h"

/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
void BugsKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	TopDownSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();
	
	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDown((unsigned int)'U'))
		{
			input->upKeyDisabled = false;
			input->downKeyDisabled = false;
			input->leftKeyDisabled = false;
			input->rightKeyDisabled = false;
		}
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'I'))
		{
			if(player->getUnDead())
				player->setUnDead(false);
			else
				player->setUnDead(true);
		}
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'0'))
		{
			gsm->goToLevel(game,L"Level 0");
		}
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'1'))
		{
			gsm->goToLevel(game,L"Level 1");
		}
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'2'))
		{
			gsm->goToLevel(game,L"Level 2");
		}
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'3'))
		{
			gsm->goToLevel(game,L"Level 3");
		}
		if(input->isKeyDownForFirstTime((unsigned int)'H'))
		{
			if(!gsm->getSpriteManager()->healthDisplay)
				gsm->getSpriteManager()->healthDisplay = true;
			else
				gsm->getSpriteManager()->healthDisplay = false;
		}
		if(input->isKeyDownForFirstTime(VK_ESCAPE))
		{
			gsm->pauseGame();
		}
		if (input->isKeyDownForFirstTime(P_KEY))
		{
			gsm->getPhysics()->togglePhysics();
		}
		if (input->isKeyDownForFirstTime(T_KEY))
		{
			gsm->getPhysics()->activateForSingleUpdate();
		}
		/*
		if (input->isKeyDownForFirstTime(D_KEY))
		{
			viewport->toggleDebugView();
			game->getGraphics()->toggleDebugTextShouldBeRendered();
		}
		*/
		/*
		if (input->isKeyDownForFirstTime(L_KEY))
		{
			game->getGraphics()->togglePathfindingGridShouldBeRendered();
		}
		if (input->isKeyDownForFirstTime(F_KEY))
		{
			game->getGraphics()->togglePathfindingPathShouldBeRendered();
		}*/

		if(input->isKeyDownForFirstTime((unsigned int)'M')){
			// PlaySound(BURN, NULL, SND_ASYNC);
			PlaySound(L"data/sound/burning.wav", NULL, SND_ASYNC);
			game->getGSM()->getSpriteManager()->getFireEffect()->setStart(true);
			game->getGSM()->getSpriteManager()->getFireEffect()->setStop(false);
		}else if(input->isKeyDown((unsigned int)'M')){
			// PlaySound(BURN, NULL, SND_ASYNC);
			game->getGSM()->getSpriteManager()->getFireEffect()->setStart(true);
			game->getGSM()->getSpriteManager()->getFireEffect()->setStop(false);
		}else if (input->isKeyDownForFirstTime(SPACE_KEY) && game->getGSM()->getSpriteManager()->getPlayerBulletCounter() <= 5)
		{
			PlaySound(SHOOT, NULL, SND_ASYNC);
			if(game->getGSM()->getSpriteManager()->getFireEffect()->isStart())
				game->getGSM()->getSpriteManager()->getFireEffect()->setStop(true);
			Bullet *bullet = new Bullet();
			//physics->addCollidableObject(bot);
			//PhysicalProperties *pp = bot->getPhysicalProperties();
			//pp->setPosition(200, 300);
			AnimatedSpriteType *bulletSpriteType = gsm->getSpriteManager()->getSpriteType(2);
			bullet->setSpriteType(bulletSpriteType);
			bullet->setCurrentState(L"MOVE");
			bullet->setAlpha(255);
			bullet->setHealth(30);
			bullet->setAttack(player->getAttack());
			bullet->setOwner(player);
			gsm->getSpriteManager()->addBullet(bullet);
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			float x=player->getB2Body()->GetPosition().x;
			float y=player->getB2Body()->GetPosition().y;
			// float r=getPlayer()->getRotationInRadians();
			float vx=0.0f;
			float vy=0.0f;
			if (player->getRotationInRadians() == PI/2.0f) 
			{
				x += (player->getSpriteType()->getTextureHeight()/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureWidth() + 1)/2.0f)/5.0f;
				vx = 120.0f;
			}else if(player->getRotationInRadians() == PI){
				y -= (player->getSpriteType()->getTextureWidth()/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureHeight() + 1)/2.0f)/5.0f;
				vy =- 120.0f;
			}else if (player->getRotationInRadians() == -PI/2.0f){
				x -=  (player->getSpriteType()->getTextureHeight()/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureWidth() + 1)/2.0f)/5.0f;
				vx = -120.0f;
			}else{
				y += (player->getSpriteType()->getTextureWidth()/2.0f)/5.0f + ((bullet->getSpriteType()->getTextureHeight() + 1/2.0f))/5.0f;
				vy = 120.0f;
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
			fixtureDef.filter.categoryBits = BULLET;
			fixtureDef.filter.maskBits = WALL|BUG;
			// Add the shape to the body.
			body->SetLinearVelocity(b2Vec2(vx,vy));
			body->CreateFixture(&fixtureDef);
			bullet->setB2Body(body);
			body->SetUserData(bullet);
		}else{
			if(game->getGSM()->getSpriteManager()->getFireEffect()->isStart())
				game->getGSM()->getSpriteManager()->getFireEffect()->setStop(true);
		}

		bool tankMoved = false;
		float tankVx = 0.0f;
		float tankVy = 0.0f;
		TopDownSprite* player = game->getGSM()->getSpriteManager()->getPlayer();
		if(input->isKeyDown(W_KEY))
		{
			if(!input->wKeyDisabled)
			{
				tankVy = MAX_TANK_SPEED;
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,tankVy));
			}else
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			player->setCurrentState(MOVE);
			player->setDirection(L"UP");
		}
		else if(input->isKeyDown(S_KEY))
		{
			if(!input->sKeyDisabled)
			{
				tankVy = -1.0f * MAX_TANK_SPEED;
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,tankVy));
			}else
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			player->setCurrentState(MOVE);
			player->setDirection(L"DOWN");
		}else if(input->isKeyDown(A_KEY))
		{
			if(!input->aKeyDisabled)
			{
				tankVx = -1.0f * MAX_TANK_SPEED;
				player->getB2Body()->SetLinearVelocity(b2Vec2(tankVx,0));
			}else
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			player->setCurrentState(MOVE);
			player->setDirection(L"LEFT");
		}else if(input->isKeyDown(D_KEY))
		{
			if(!input->dKeyDisabled)
			{
				tankVx = MAX_TANK_SPEED;
				player->getB2Body()->SetLinearVelocity(b2Vec2(tankVx,0));
			}else
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			player->setCurrentState(MOVE);
			player->setDirection(L"RIGHT");
		}else{
			player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			player->setCurrentState(IDLE);
		}

		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		if (input->isKeyDown(UP_KEY) && !input->upKeyDisabled)
		{
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY) && !input->downKeyDisabled)
		{
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(LEFT_KEY) && !input->leftKeyDisabled)
		{
			viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(RIGHT_KEY) && !input->rightKeyDisabled)
		{
			viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx+0.5f), (int)floor(viewportVy+0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());
		
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;		
		cursor->setActiveCursorID(id);
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();
	int fps = timer->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		timer->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		timer->setTargetFPS(fps - FPS_INC);
}