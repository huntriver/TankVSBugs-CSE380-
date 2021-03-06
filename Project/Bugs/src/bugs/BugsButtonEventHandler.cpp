/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugsButtonEventHandler.cpp

	See BugsButtonEventHandler.h for a class description.
*/

#include "bugs_VS\stdafx.h"
#include "bugs\BugsGame.h"
#include "bugs\BugsButtonEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"

void BugsButtonEventHandler::handleButtonEvents(	Game *game, 
													wstring command
											    )
{
	// THE USER PRESSED THE Exit BUTTON ON THE MAIN MENU,
	// SO LET'S SHUTDOWN THE ENTIRE APPLICATION
	if (command.compare(W_EXIT_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		game->shutdown();
	}
	// THE USER PRESSED THE MOUSE BUTTON ON THE SPLASH
	// SCREEN, SO LET'S GO TO THE MAIN MENU
	else if (command.compare(W_GO_TO_MM_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		GameStateManager *gsm = game->getGSM();
		gsm->goToMainMenu();
	}
	// THE USER PRESSED THE Start BUTTON ON THE MAIN MENU,
	// SO LET'S START THE GAME FROM THE FIRST LEVEL
	else if (command.compare(W_START_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		game->setCurrentLevelFileName(W_LEVEL_1_NAME);
		game->getGSM()->loadLevel(game, L"Level 1");
		game->startGame();
	}
	// THE USER PRESSED THE Quit BUTTON ON THE IN-GAME MENU,
	// SO LET'S UNLOAD THE LEVEL AND RETURN TO THE MAIN MENU
	else if (command.compare(W_QUIT_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		game->quitGame();
	}else if(command.compare(W_CREDITS_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		GameStateManager *gsm = game->getGSM();
		gsm->goToCreditMenu();
	}else if(command.compare(W_RESUME_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		GameStateManager *gsm = game->getGSM();
		gsm->goToGame();
	}else if(command.compare(W_CONTROL_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		GameStateManager *gsm = game->getGSM();
		gsm->goToControlMenu();
	}else if(command.compare(W_BACK_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		GameStateManager *gsm = game->getGSM();
		gsm->pauseGame();
	}else if(command.compare(W_STORY_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		GameStateManager *gsm = game->getGSM();
		gsm->goToStoryMenu();
	}else if(command.compare(W_REPLAY_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		game->getGSM()->goToLevel(game, game->getGSM()->getCurrentLevelName());
		game->startGame();
	}else if(command.compare(W_NEXT_COMMAND) == 0)
	{
		PlaySound(SHOOT, NULL, SND_ASYNC);
		int nextLevel = game->getGSM()->getCurrentLevel() + 1;
		wstring levelNameToLoad;
		if(nextLevel == 2)
		{
			levelNameToLoad = L"Level 2";
		}else
			levelNameToLoad = L"Level 3";
		game->getGSM()->goToLevel(game, levelNameToLoad);
		game->startGame();
	}
}