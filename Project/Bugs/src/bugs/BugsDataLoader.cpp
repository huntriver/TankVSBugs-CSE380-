#include "bugs_VS\stdafx.h"

// Bugs GAME INCLUDES
#include "bugs\BugsButtonEventHandler.h"
#include "bugs\BugsDataLoader.h"
#include "bugs\BugsGame.h"
#include "bugs\BugsKeyEventHandler.h"
#include "bugs\BugsTextGenerator.h"
#include "bugs\Box2DContactListener.h"
#include "bugs\_entityCategory.h"

// GAME OBJECT INCLUDES
#include "sssf\gsm\sprite\FireEffect.h"
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\bots\RandomBot.h"
#include "sssf\gsm\ai\pathfinding\OrthographicGridPathfinder.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\gui\ScreenGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\os\GameOS.h"
#include "sssf\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "sssf\platforms\Windows\WindowsOS.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

// DIRECTX INCLUDES
#include "sssf\platforms\DirectX\DirectXGraphics.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"

// TMX MAP LOADING
#include "tmxmi\TMXMapImporter.h"

// ANIMATED SPRITE TYPE LOADING
#include "psti\PoseurSpriteTypesImporter.h"

#include "Box2D\Box2D.h"

/*
	loadGame - This method loads the setup game data into the game and
	constructs all the needed objects for the game to work.
*/
void BugsDataLoader::loadGame(Game *game, wstring gameInitFile)
{
	// AND LET'S READ IN THE GAME SETUP INFO
	// FIRST LOAD ALL THE PROPERTIES
	map<wstring,wstring> *properties = new map<wstring,wstring>();
	loadGameProperties(game, properties, gameInitFile);

	// WE NEED THE TITLE AND USE_FULLSCREEN_MODE TO INITIALIZE OUR WINDOW
	wstring titleProp = (*properties)[W_TITLE];
	wstring useFullscreenProp = (*properties)[W_USE_FULLSCREEN_MODE];
	bool useFullscreen = false;
	if (useFullscreenProp.compare(L"true") == 0)
		useFullscreen = true;

	// GET THE SCREEN WIDTH AND HEIGHT
	int screenWidth, screenHeight;
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;

	// MAKE A CUSTOM GameOS OBJECT (WindowsOS) FOR SOME WINDOWS
	// PLATFORM STUFF, INCLUDING A Window OF COURSE
	WindowsOS *BugsOS = new WindowsOS(	hInstance, 
										nCmdShow,
										useFullscreen,
										titleProp,
										screenWidth, screenHeight,
										game);
	
	int textFontSize;
	wstring textFontSizeProp = (*properties)[W_TEXT_FONT_SIZE];
	wstringstream(textFontSizeProp) >> textFontSize;

	// RENDERING WILL BE DONE USING DirectX
	DirectXGraphics *BugsGraphics = new DirectXGraphics(game);
	BugsGraphics->init(screenWidth, screenHeight);
	BugsGraphics->initGraphics(BugsOS, useFullscreen);
	BugsGraphics->initTextFont(textFontSize);

	// AND NOW LOAD THE COLORS THE GRAPHICS WILL USE
	// AS A COLOR KEY AND FOR RENDERING TEXT
	initColors(BugsGraphics, properties);

	// WE'LL USE WINDOWS PLATFORM METHODS FOR GETTING INPUT
	WindowsInput *BugsInput = new WindowsInput();

	// AND WINDOWS FOR THE TIMER AS WELL
	WindowsTimer *BugsTimer = new WindowsTimer();

	// NOW INITIALIZE THE Game WITH ALL THE
	// PLATFORM AND GAME SPECIFIC DATA WE JUST CREATED
	game->initplatforms(	(GameGraphics*)BugsGraphics,
								(GameInput*)BugsInput,
								(GameOS*)BugsOS,
								(GameTimer*)BugsTimer);

	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DRAWS
	// TEXT ON THE SCREEN EACH FRAME
	BugsTextGenerator *bugsTextGenerator = new BugsTextGenerator();
	bugsTextGenerator->initText(game);
	GameText *text = game->getText();
	text->initDebugFile(W_DEBUG_FILE);
	text->setTextGenerator((TextGenerator*)bugsTextGenerator);

	// INIT THE VIEWPORT TOO
	initViewport(game->getGUI(), properties);	

	// WE DON'T NEED THE PROPERTIES MAP ANYMORE, THE GAME IS ALL LOADED
	delete properties;
}

/*
	initColors - this helper method loads the color key, used for loading
	images, and the font color, used for rendering text.
*/
void BugsDataLoader::initColors(	GameGraphics *graphics,
									map<wstring,wstring> *properties)
{
	int fontRed, fontGreen, fontBlue;
	wstring fontRedProp = (*properties)[W_FONT_COLOR_RED];
	wstring fontGreenProp = (*properties)[W_FONT_COLOR_GREEN];
	wstring fontBlueProp = (*properties)[W_FONT_COLOR_BLUE];
	wstringstream(fontRedProp) >> fontRed;
	wstringstream(fontGreenProp) >> fontGreen;
	wstringstream(fontBlueProp) >> fontBlue;

	// COLOR USED FOR RENDERING TEXT
	graphics->setFontColor(fontRed, fontGreen, fontBlue);

	int keyRed, keyGreen, keyBlue;
	wstring keyRedProp = (*properties)[W_COLOR_KEY_RED];
	wstring keyGreenProp = (*properties)[W_COLOR_KEY_GREEN];
	wstring keyBlueProp = (*properties)[W_COLOR_KEY_BLUE];
	wstringstream(keyRedProp) >> keyRed;
	wstringstream(keyGreenProp) >> keyGreen;
	wstringstream(keyBlueProp) >> keyBlue;

	// COLOR KEY - COLOR TO BE IGNORED WHEN LOADING AN IMAGE
	// NOTE, IF YOU WISH TO USE PNG IMAGES THAT CONTAIN ALPHA
	// CHANNEL DATA, YOU DON'T NEED A COLOR KEY
	graphics->setColorKey(keyRed, keyGreen, keyBlue);
}

/*
	loadGUI - This method loads all the GUI assets described in the guiInitFile
	argument. Note that we are loading all GUI art for all GUIs when the application
	first starts. We'll learn a better technique later in the semester.
*/
void BugsDataLoader::loadGUI(Game *game, wstring guiInitFile)
{
	// WE'RE JUST GOING TO IGNORE THE GUI FILE FOR NOW.
	// FOR THE MOMENT WE ARE CALLING THIS HARD-CODED GUI LOADER
	hardCodedLoadGUIExample(game);
}

/*
	loadLevel - This method should load the data the level described by the
	levelInitFile argument in to the Game's game state manager.
*/
void BugsDataLoader::loadWorld(Game *game, wstring levelInitFile)	
{
	// LOAD THE LEVEL'S BACKGROUND TILES
	TMXMapImporter tmxMapImporter;
	tmxMapImporter.loadWorld(game, W_LEVEL_1_DIR, W_LEVEL_1_NAME);

	// SPECIFY WHO WILL DO THE PATHFINDING
	GameStateManager *gsm = game->getGSM();
	World *world = gsm->getWorld();
	OrthographicGridPathfinder *pathfinder = new OrthographicGridPathfinder(game);
	SpriteManager *spriteManager = gsm->getSpriteManager();
	spriteManager->setPathfinder(pathfinder);

	world->initBox2DTiles();
	
	world->boxWorld->SetContactListener(new Box2DContactListener());

	
	// LOAD THE LEVEL'S SPRITE IMAGES
	PoseurSpriteTypesImporter psti;
	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	// LET'S MAKE A PLAYER SPRITE
	// @TODO - LATER WE'LL LOAD ALL LEVEL DATA FROM A FILE

	Physics *physics = gsm->getPhysics();
	physics->setGravity(W_GRAVITY);
	TopDownSprite *player = spriteManager->getPlayer();
	physics->addCollidableObject(player);
	player->setRotationInRadians(0.0f);

	// NOTE THAT RED BOX MAN IS SPRITE ID 1
	AnimatedSpriteType *playerSpriteType = spriteManager->getSpriteType(0);
	player->setSpriteType(playerSpriteType);
	player->setAlpha(255);
	player->setCurrentState(IDLE);
	player->setDirection(L"RIGHT");
	player->setHealth(playerSpriteType->getTextureWidth()/spriteManager->getSpriteType(4)->getTextureWidth());
	player->setHP(100.0f);
	player->setAttack(50.0f);

	/*
	PhysicalProperties *playerProps = player->getPhysicalProperties();
	playerProps->setX(PLAYER_INIT_X);
	playerProps->setY(PLAYER_INIT_Y);
	playerProps->setVelocity(0.0f, 0.0f);
	playerProps->setAccelerationX(0);
	playerProps->setAccelerationY(0);
	*/
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(135.0f/5.0f, -150.0f/5.0f);
	// bodyDef.position.Set(135.0f/5.0f, -750.0f/5.0f);
	b2Body* body = (world->boxWorld)->CreateBody(&bodyDef);
	body->SetUserData(player);
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(player->getSpriteType()->getTextureWidth()/10.0f, player->getSpriteType()->getTextureHeight()/10.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	 fixtureDef.density = 1.0f;

	// Override the default friction.
	 fixtureDef.friction = 0.3f;
	 fixtureDef.filter.categoryBits = TANK;
	 fixtureDef.filter.maskBits = WALL|BUG;

	// Add the shape to the body.
	body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
	body->CreateFixture(&fixtureDef);
	player->setB2Body(body);

	player->setOnTileThisFrame(false);
	player->setOnTileLastFrame(false);
	player->affixTightAABBBoundingVolume();

	float viewportX=game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().x*5.0f;
	float viewportY=game->getGSM()->getSpriteManager()->getPlayer()->getB2Body()->GetPosition().y*-5.0f;
	float screenX = game->getGUI()->getViewport()->getViewportWidth()/2.0f;
	float screenY = game->getGUI()->getViewport()->getViewportHeight()/2.0f;
	game->getGUI()->getViewport()->moveViewport((int)floor(viewportX-screenX), (int)floor(viewportY-screenY), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());

	// AND LET'S ADD A BUNCH OF RANDOM JUMPING BOTS, FIRST ALONG
	// A LINE NEAR THE TOP
	/*
	AnimatedSpriteType *botSpriteType = spriteManager->getSpriteType(1);

	
	makeRandomBot(game, botSpriteType, 550, 300, true);
	makeRandomBot(game, botSpriteType, 550, 300, false);
	makeRandomBot(game, botSpriteType, 600, 170, false);
	makeRandomBot(game, botSpriteType, 650, 260, false);
	makeRandomBot(game, botSpriteType, 700, 340, false);
	makeRandomBot(game, botSpriteType, 700, 340, true);
	makeRandomBot(game, botSpriteType, 400, 320, false);
	makeRandomBot(game, botSpriteType, 500, 440, true);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, true);
	makeRandomBot(game, botSpriteType, 500, 440, true);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 550, 300, true);
	makeRandomBot(game, botSpriteType, 550, 300, false);
	makeRandomBot(game, botSpriteType, 600, 170, false);
	makeRandomBot(game, botSpriteType, 650, 260, false);
	makeRandomBot(game, botSpriteType, 700, 340, false);
	makeRandomBot(game, botSpriteType, 700, 340, true);
	makeRandomBot(game, botSpriteType, 400, 320, false);
	makeRandomBot(game, botSpriteType, 500, 440, true);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, true);
	makeRandomBot(game, botSpriteType, 500, 440, true);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	makeRandomBot(game, botSpriteType, 500, 440, false);
	*/
	FireEffect* effect = spriteManager->getFireEffect();
	AnimatedSpriteType *fireSpriteType = spriteManager->getSpriteType(6);
	effect->setSpriteType(fireSpriteType);
	effect->setAlpha(255);
	effect->setHealth(1000);
	effect->setCurrentState(IDLE);
	effect->setAttack(5.0f);
	effect->setPlayer(player);
	game->getGSM()->getSpriteManager()->addFireEffect(effect);
	
// UNCOMMENT THE FOLLOWING CODE BLOCK WHEN YOU ARE READY TO ADD SOME BOTS
/*	for (int i = 2; i <= 26; i++)
	{
		float botX = 400.0f + (i * 100.0f);
		float botY = 100.0f;
		makeRandomJumpingBot(game, botSpriteType, botX, botY);
	}

	// AND THEN STRATEGICALLY PLACED AROUND THE LEVEL
	makeRandomJumpingBot(game, botSpriteType, 400, 100);
	makeRandomJumpingBot(game, botSpriteType, 200, 400);
	makeRandomJumpingBot(game, botSpriteType, 400, 400);
	makeRandomJumpingBot(game, botSpriteType, 800, 700);
	makeRandomJumpingBot(game, botSpriteType, 900, 700);
	makeRandomJumpingBot(game, botSpriteType, 1000, 700);
	makeRandomJumpingBot(game, botSpriteType, 100, 1000);
	makeRandomJumpingBot(game, botSpriteType, 300, 1000);	
	makeRandomJumpingBot(game, botSpriteType, 500, 1000);
	makeRandomJumpingBot(game, botSpriteType, 100, 1400);
	makeRandomJumpingBot(game, botSpriteType, 400, 1400);	
	makeRandomJumpingBot(game, botSpriteType, 700, 1400);

	// AND THEN A BUNCH LINED UP NEAR THE LEVEL EXIT
	for (int i = 0; i < 14; i++)
		makeRandomJumpingBot(game, botSpriteType, 1700.0f + (i*100.0f), 1300.0f);
*/	
	game->getInput()->wKeyDisabled = false;
	game->getInput()->sKeyDisabled = false;
	game->getInput()->dKeyDisabled = false;
	game->getInput()->aKeyDisabled = false;
	game->getGSM()->goToGame();
	game->getGUI()->getViewport()->setViewportX(0.0f);
	game->getGUI()->getViewport()->setViewportY(0.0f);
}

void BugsDataLoader::makeRandomBot(Game *game, AnimatedSpriteType *randomBotType, float initX, float initY, bool initXTerm)
{
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
//	Physics *physics = game->getGSM()->getPhysics();
	RandomBot *bot = new RandomBot();
	//physics->addCollidableObject(bot);
	//PhysicalProperties *pp = bot->getPhysicalProperties();
	//pp->setPosition(initX, initY);
	bot->setSpriteType(randomBotType);
	bot->setCurrentState(L"IDLE");
	bot->setDirection(L"UP");
	bot->setAlpha(255);
	bot->setHealth((int)(randomBotType->getTextureWidth()/game->getGSM()->getSpriteManager()->getSpriteType(4)->getTextureWidth()));
	bot->setAttack(0.2);
	int playerW = game->getGSM()->getSpriteManager()->getPlayer()->getSpriteType()->getTextureWidth()/2;
	float randNum = rand()% playerW;
	if(game->getGSM()->getSpriteManager()->getBotSize() % 2 == 0)
		bot->initBot(30, 300, MAX_TANK_SPEED/1.4f, initXTerm,randNum);
	else
		bot->initBot(30, 300, MAX_TANK_SPEED/1.4f, initXTerm,-randNum);
	spriteManager->addBot(bot);
	//bot->affixTightAABBBoundingVolume();

	b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(initX/5.0f, -initY/5.0f);
		b2Body* body = (game->getGSM()->getWorld()->boxWorld)->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(randomBotType->getTextureWidth()/10.0f, randomBotType->getTextureHeight()/10.0f);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;

		// Override the default friction.
		fixtureDef.friction = 0.3f;
		fixtureDef.filter.categoryBits = BUG;
		fixtureDef.filter.maskBits = WALL|BULLET|TANK;
		// Add the shape to the body.
		body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
		body->CreateFixture(&fixtureDef);
		bot->setB2Body(body);
		body->SetUserData(bot);
}

/*
	initBugsGUI - This method builds a GUI for the Bugs Game application.
	Note that we load all the GUI components from this method, including
	the ScreenGUI with Buttons and Overlays and the Cursor.
*/
void BugsDataLoader::hardCodedLoadGUIExample(Game *game)
{
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	DirectXTextureManager *guiTextureManager = (DirectXTextureManager*)graphics->getGUITextureManager();

	// SETUP THE CURSOR VIA OUR HELPER METHOD
	initCursor(gui, guiTextureManager);
	// initSplashScreen(game, gui, guiTextureManager);
	initMainMenu(gui, guiTextureManager);
	// initCreditsMenu(gui, guiTextureManager);
	initPauseMenu(gui, guiTextureManager);
	// initInGameGUI(gui, guiTextureManager);
}

void BugsDataLoader::initCreditsMenu(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	ScreenGUI *creditsMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_CREDITS_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1366;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	creditsMenuGUI->addOverlayImage(imageToAdd);

	// AND GO BACK BUTTON
	int normalTextureID = guiTextureManager->loadTexture(W_GO_BACK_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_GO_BACK_PATH);

	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
							mouseOverTextureID,
							106,
							656,
							0,
							255,
							200,
							50,
							false,
							W_GO_TO_MM_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	creditsMenuGUI->addButton(buttonToAdd);


	// AND LET'S ADD A START BUTTON
	// buttonToAdd = new Button();

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_CREDITS_MENU, creditsMenuGUI);
}
/*
	initCursor - initializes a simple little cursor for the gui.
*/
void BugsDataLoader::initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - FIRST LOAD THE GREEN CURSOR IMAGE

	imageID = guiTextureManager->loadTexture(W_BLUE_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(	imageIDs,
						*(imageIDs->begin()),
						0,
						0,
						0,
						255,
						32,
						32);
	// cursor->setAttackCounter(0);
	gui->setCursor(cursor);
}

/*
	initSplashScreen - initializes the game's splash screen gui.
*/
void BugsDataLoader::initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW, FIRST LET'S ADD A SPLASH SCREEN GUI
	ScreenGUI *splashScreenGUI = new ScreenGUI();

	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
}

/*
	initMainMenu - initializes the game's main menu gui.
*/
void BugsDataLoader::initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_MAIN_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1366;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND CREDIT BUTTON
	int normalTextureID = guiTextureManager->loadTexture(W_START_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_START_IMAGE_PATH);

	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
							mouseOverTextureID,
							72,
							319,
							0,
							255,
							400,
							100,
							false,
							W_START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	normalTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_PATH);

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
							mouseOverTextureID,
							73,
							540,
							0,
							255,
							400,
							100,
							false,
							W_EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);
	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_MAIN_MENU,		mainMenuGUI);
}

void BugsDataLoader::initPauseMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	ScreenGUI *pauseMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_PAUSE_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1366;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	pauseMenuGUI->addOverlayImage(imageToAdd);

	// AND CREDIT BUTTON
	int normalTextureID = guiTextureManager->loadTexture(W_RESUME_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_RESUME_IMAGE_PATH);

	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
							mouseOverTextureID,
							496,
							284,
							0,
							255,
							400,
							100,
							false,
							W_RESUME_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	pauseMenuGUI->addButton(buttonToAdd);

	normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
							mouseOverTextureID,
							496,
							504,
							0,
							255,
							400,
							100,
							false,
							W_QUIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	pauseMenuGUI->addButton(buttonToAdd);
	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_PAUSED,pauseMenuGUI);
}
/*
	initInGameGUI - initializes the game's in-game gui.
*/
void BugsDataLoader::initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();

	unsigned int imageID = guiTextureManager->loadTexture(W_INGAME_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 768;
	imageToAdd->height = 120;
	imageToAdd->imageID = imageID;
	inGameGUI->addOverlayImage(imageToAdd);

	unsigned int normalTextureID = guiTextureManager->loadTexture(W_FIRE_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_FIRE_IMAGE_PATH);
	unsigned int mouseDisabledTextureID = guiTextureManager->loadTexture(W_FIRE_DISABLED_PATH);

	Button *buttonToAdd = new Button();

	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							45,
							45,
							0,
							255,
							45,
							45,
							false,
							W_FIRE_COMMAND);
	buttonToAdd->setMouseDisabledTextureID(mouseDisabledTextureID);
	buttonToAdd->setIsDisabled(false);
	inGameGUI->addButton(buttonToAdd);
	
	
	normalTextureID = guiTextureManager->loadTexture(W_FLASH_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_FLASH_IMAGE_PATH);
	mouseDisabledTextureID = guiTextureManager->loadTexture(W_FLASH_DISABLED_PATH);
	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							122,
							45,
							0,
							255,
							45,
							45,
							false,
							W_FLASH_COMMAND);
	buttonToAdd->setMouseDisabledTextureID(mouseDisabledTextureID);
	buttonToAdd->setIsDisabled(false);
	inGameGUI->addButton(buttonToAdd);


	/*
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							200,
							100,
							false,
							W_QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);
	*/
	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_GAME_IN_PROGRESS,	inGameGUI);
}

/*
	initViewport - initializes the game's viewport.
*/
void BugsDataLoader::initViewport(GameGUI *gui, map<wstring,wstring> *properties)
{
	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();

	int viewportOffsetX, viewportOffsetY, toggleOffsetY, screenWidth, screenHeight;
	wstring viewportOffsetXProp = (*properties)[W_VIEWPORT_OFFSET_X];
	wstring viewportOffsetYProp = (*properties)[W_VIEWPORT_OFFSET_Y];
	wstring toggleOffsetYProp = (*properties)[W_TOGGLE_OFFSET_Y];
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(viewportOffsetXProp) >> viewportOffsetX;
	wstringstream(viewportOffsetYProp) >> viewportOffsetY;
	wstringstream(toggleOffsetYProp) >> toggleOffsetY;
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;
	int viewportWidth = screenWidth - viewportOffsetX;
	int viewportHeight = screenHeight - viewportOffsetY;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setViewportOffsetX(viewportOffsetX);
	viewport->setViewportOffsetY(viewportOffsetY);
	viewport->setToggleOffsetY(toggleOffsetY);
}