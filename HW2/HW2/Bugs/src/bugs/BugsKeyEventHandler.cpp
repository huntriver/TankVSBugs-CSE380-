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
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
#include "Box2D\Box2D.h"

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
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	b2Body* body=player->getB2Body();
	//PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();
	
	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		float vX = body->GetLinearVelocity().x;
		float vY = body->GetLinearVelocity().y;
		if(input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'1'))
		{
			game->getGSM()->unloadCurrentLevel();
			game->setCurrentLevelFileName(W_LEVEL_1_NAME);
		    game->setCurrentLevelDir(W_LEVEL_1_DIR);
			game->startGame();
		}
		if (input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime((unsigned int)'2'))
		{
			game->getGSM()->unloadCurrentLevel();
			game->setCurrentLevelFileName(W_LEVEL_2_NAME);
		    game->setCurrentLevelDir(W_LEVEL_2_DIR);
			game->startGame();
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
		if (input->isKeyDownForFirstTime(L_KEY))
		{
			game->getGraphics()->togglePathfindingGridShouldBeRendered();
		}
		if (input->isKeyDownForFirstTime(F_KEY))
		{
			game->getGraphics()->togglePathfindingPathShouldBeRendered();
		}
		if (input->isKeyDownForFirstTime(SPACE_KEY))
		{
			// player->shoot();
			TopDownSprite *bullet = new TopDownSprite();
			//physics->addCollidableObject(bot);
			//PhysicalProperties *pp = bot->getPhysicalProperties();
			//pp->setPosition(200, 300);
			AnimatedSpriteType *bulletSpriteType = gsm->getSpriteManager()->getSpriteType(2);
			bullet->setSpriteType(bulletSpriteType);
			bullet->setCurrentState(L"IDLE");
			bullet->setAlpha(255);
			bullet->setHealth(0);
			gsm->getSpriteManager()->addBullet(bullet);

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			float x=player->getB2Body()->GetPosition().x;
			float y=player->getB2Body()->GetPosition().y;
			// float r=getPlayer()->getRotationInRadians();
			float vx=0.0f;
			float vy=0.0f;
			if (player->getCurrentState() == MOVE_RIGHT || player->getCurrentState() == IDLE_RIGHT) 
			{
				x+=32.0f/5.0f+0.55f;
				vx=100.0f;
			}else if(player->getCurrentState() == MOVE_DOWN || player->getCurrentState() == IDLE_DOWN){
				y-=32.0f/5.0f+0.55f;
				vy=-100.0f;
			}else if (player->getCurrentState() == MOVE_LEFT || player->getCurrentState() == IDLE_LEFT){
				x-=32.0f/5.0f+0.55f;
				vx=-100.0f;
			}else{
				y+=32.0f/5.0f+0.55f;
				vy=100.0f;
			}
			bodyDef.position.Set(x, y);
			b2Body* body = (game->getGSM()->getWorld()->boxWorld)->CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(2.5f/5.0f, 2.5f/5.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.0f;

			// Add the shape to the body.
			body->SetLinearVelocity(b2Vec2(vx,vy));
			body->CreateFixture(&fixtureDef);
			bullet->setB2Body(body);
			body->SetUserData(bullet);
		}

		// bool tankMoved = false;
		float tankVx = 0.0f;
		float tankVy = 0.0f;
		TopDownSprite* player = game->getGSM()->getSpriteManager()->getPlayer();

		if(input->isKeyDown(W_KEY))
		{
			if(player->getCurrentState() != IDLE_UP && player->getCurrentState() != MOVE_UP)
			{
				input->wKeyDisabled = false;
			}
			tankVy = MAX_TANK_SPEED;
			if(!input->wKeyDisabled){
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,tankVy));
			}else{
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			}
			player->setCurrentState(MOVE_UP);
		}
		else if(input->isKeyDown(S_KEY))
		{
			    if(player->getCurrentState() != IDLE_DOWN && player->getCurrentState() != MOVE_DOWN)
			    {
				   input->sKeyDisabled = false;
			    }
				tankVy = -1.0f * MAX_TANK_SPEED;
				if(!input->sKeyDisabled)
				{
					player->getB2Body()->SetLinearVelocity(b2Vec2(0,tankVy));
				}
				else
				{
					player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
				}
				//if(player->getCurrentState() != MOVE_DOWN)
				player->setCurrentState(MOVE_DOWN);
			
		}else if(input->isKeyDown(A_KEY))
		{
			if(player->getCurrentState() != IDLE_LEFT && player->getCurrentState() != MOVE_LEFT)
			{
				input->aKeyDisabled = false;
			}
			tankVx = -1.0f * MAX_TANK_SPEED;
			if(!input->aKeyDisabled){
				player->getB2Body()->SetLinearVelocity(b2Vec2(tankVx,0));
			}else{
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			}
			//if(player->getCurrentState() != MOVE_LEFT)
			player->setCurrentState(MOVE_LEFT);
		}else if(input->isKeyDown(D_KEY))
		{
			if(player->getCurrentState() != IDLE_RIGHT && player->getCurrentState() != MOVE_RIGHT)
			{
				input->dKeyDisabled = false;
			}
			tankVx = MAX_TANK_SPEED;
			if(!input->dKeyDisabled){
				player->getB2Body()->SetLinearVelocity(b2Vec2(tankVx,0));
			}else{
				player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			}
			//if(player->getCurrentState() != MOVE_RIGHT)
			player->setCurrentState(MOVE_RIGHT);
		}else{
			player->getB2Body()->SetLinearVelocity(b2Vec2(0,0));
			if(player->getCurrentState() == MOVE_UP)
				player->setCurrentState(IDLE_UP);
			else if(player->getCurrentState() == MOVE_DOWN)
				player->setCurrentState(IDLE_DOWN);
			else if(player->getCurrentState() == MOVE_LEFT)
				player->setCurrentState(IDLE_LEFT);
			else if(player->getCurrentState() == MOVE_RIGHT)
				player->setCurrentState(IDLE_RIGHT);
		}


		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		if (input->isKeyDown(UP_KEY))
		{
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY))
		{
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(LEFT_KEY))
		{
			viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(RIGHT_KEY))
		{
			viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx+0.5f), (int)floor(viewportVy+0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());
	

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
}