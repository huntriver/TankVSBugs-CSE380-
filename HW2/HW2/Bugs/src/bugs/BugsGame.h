#pragma once
#include "bugs_VS\stdafx.h"

/*
	BugsGame.h

	This file contains setup data for making the Bugs game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

//sounds
static const LPCWSTR TANK_ATTACK		=	L"data/sounds/attack.wav";
static const LPCWSTR BACKGROUND_MUSIC	=	L"data/sounds/background.wav";
static const LPCWSTR HITTED	=	L"data/sounds/hitted.wav";

// HERE IS THE Bugs GAME SETUP/INIT FILE. EVERYTHING WOULD START FROM HERE
static const wstring	W_LEVEL_1_DIR			= L"data/levels/level1/";
static const wstring	W_LEVEL_1_NAME			= L"level1.tmx";
static const wstring	W_LEVEL_1_PATH			= W_LEVEL_1_DIR + W_LEVEL_1_NAME;

static const wstring	W_LEVEL_2_DIR			= L"data/levels/level2/";
static const wstring	W_LEVEL_2_NAME			= L"level2.tmx";
static const wstring	W_LEVEL_2_PATH			= W_LEVEL_2_DIR + W_LEVEL_2_NAME;

static const wstring	W_INIT_FILE				= L"data/BugsInit.txt";
static const wstring	W_GUI_INIT_FILE			= L"data/BugsGUI.txt";
static const string		W_DEBUG_FILE			= "DebugOutput.txt";

// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const wstring	W_TITLE					= L"TITLE";
static const wstring	W_SCREEN_WIDTH			= L"SCREEN_WIDTH";
static const wstring	W_SCREEN_HEIGHT			= L"SCREEN_HEIGHT";
static const wstring	W_USE_FULLSCREEN_MODE	= L"USE_FULLSCREEN_MODE";
static const wstring	W_TEXT_FONT_SIZE		= L"TEXT_FONT_SIZE";
static const wstring	W_VIEWPORT_OFFSET_X		= L"VIEWPORT_OFFSET_X";
static const wstring	W_VIEWPORT_OFFSET_Y		= L"VIEWPORT_OFFSET_Y";
static const wstring	W_TOGGLE_OFFSET_Y		= L"TOGGLE_OFFSET_Y";
static const wstring	W_FONT_COLOR_RED		= L"FONT_COLOR_RED";
static const wstring	W_FONT_COLOR_GREEN		= L"FONT_COLOR_GREEN";
static const wstring	W_FONT_COLOR_BLUE		= L"FONT_COLOR_BLUE";
static const wstring	W_COLOR_KEY_RED			= L"COLOR_KEY_RED";
static const wstring	W_COLOR_KEY_GREEN		= L"COLOR_KEY_GREEN";
static const wstring	W_COLOR_KEY_BLUE		= L"COLOR_KEY_BLUE";

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	W_GO_TO_MM_COMMAND		= L"Go To Main Menu";
static const wstring	W_START_COMMAND			= L"Start";
static const wstring	W_EXIT_COMMAND			= L"Exit";
static const wstring    W_CREDITS_COMMAND       = L"Credits";
static const wstring	W_QUIT_COMMAND			= L"Quit";
static const wstring	W_STATS_COMMAND         = L"Stats";
static const wstring    W_FIRE_COMMAND          = L"Fire";
static const wstring    W_FLASH_COMMAND         = L"Flash";
static const wstring	W_GREEN_CURSOR_PATH		= L"data/gui/cursor/green_cursor.png";
static const wstring	W_RED_CURSOR_PATH		= L"data/gui/cursor/red_cursor.png";
static const wstring    W_RED_CURSOR2_PATH		=L"data/gui/cursor/red_cursor2.png";
static const wstring    W_HAND_CURSOR_PATH		=L"data/gui/cursor/hand_cursor.png";
static const wstring	W_SPLASH_SCREEN_PATH	= L"data/gui/overlays/spiked_acid_splash_screen_overlay.png";
static const wstring	W_MAIN_MENU_PATH		= L"data/gui/overlays/spiked_acid_main_menu_overlay.png";
static const wstring	W_CREDITS_MENU_PATH     = L"data/gui/overlays/spiked_acid_credits_menu_overlay.png";
static const wstring    W_INGAME_MENU_PATH		= L"data/gui/overlays/tank_ingame_menu_overlay.png";
static const wstring	W_START_IMAGE_PATH		= L"data/gui/buttons/new_game_button.png";
static const wstring	W_EXIT_IMAGE_PATH		= L"data/gui/buttons/exit_button.png";
static const wstring    W_STATS_IMAGE_PATH      = L"data/gui/buttons/stats_button.png";
static const wstring	W_CREDITS_IMAGE_PATH    = L"data/gui/buttons/credit_button.png";
static const wstring    W_GO_BACK_PATH          = L"data/gui/buttons/go_back_button.png";
static const wstring	W_EXIT_IMAGE_MO_PATH	= L"data/gui/buttons/exit_game_mo.png";
static const wstring	W_QUIT_IMAGE_PATH		= L"data/gui/buttons/quit.png";
static const wstring	W_QUIT_IMAGE_MO_PATH	= L"data/gui/buttons/quit_mo.png";
static const wstring	W_GRID_CELL_SELECTOR_PATH = L"data/gui/overlays/GridCellSelector.png";
static const wstring    W_FLASH_IMAGE_PATH        = L"data/gui/buttons/flash.png";
static const wstring    W_FIRE_IMAGE_PATH        = L"data/gui/buttons/fire.png";
static const wstring    W_FIRE_DISABLED_PATH     = L"data/gui/buttons/fire_disabled.png";
static const wstring    W_FLASH_DISABLED_PATH    = L"data/gui/buttons/flash_disabled.png";
static const wstring	W_HEALTH_BAR_PATH		= L"data/gui/buttons/health_bar.png";
static const wstring    W_CONTROL_IMAGE_PATH    = L"data/gui/buttons/control_button.png";
static const wstring    W_CONTROL_MENU_PATH     = L"data/gui/overlays/spiked_acid_control_menu_overlay.png";
static const wstring    W_CONTROL_COMMAND       = L"Control";
// FOR OUR SPRITE
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";
static const wstring	WALKING = L"WALKING";

// FOR THE GAME WORLD
static const float		MAX_VIEWPORT_AXIS_VELOCITY = 20.0f;
static const float		W_GRAVITY = 0.0f;
static const float		JUMPING_BOT_MIN_CYCLES = 30;
static const float		JUMPING_BOT_MAX_CYCLES = 120;
static const float		JUMPING_BOT_MAX_VELOCITY = 40;
static const float		PLAYER_INIT_X = 80.0f;
static const float		PLAYER_INIT_Y = 105.0f;
static const float		JUMP_SPEED = -24.0f;
static const float		PLAYER_SPEED = 6.0f;
static const float      MAX_TANK_SPEED = 60.0f;
static const int		MIN_FPS = 5;
static const int		MAX_FPS = 100;
static const int		FPS_INC = 1;
static const wstring    ATTACK_UP(L"ATTACK UP");
static const wstring	ATTACK_DOWN(L"ATTACK DOWN");
static const wstring    ATTACK_LEFT(L"ATTACK LEFT");
static const wstring    ATTACK_RIGHT(L"ATTACK RIGHT");
static const wstring	IDLE(L"IDLE");
static const wstring    IDLE_UP(L"IDLE UP");
static const wstring    IDLE_DOWN(L"IDLE DOWN");
static const wstring    IDLE_LEFT(L"IDLE LEFT");
static const wstring    IDLE_RIGHT(L"IDLE RIGHT");
static const wstring    MOVE_UP(L"MOVE UP");
static const wstring    MOVE_DOWN(L"MOVE DOWN");
static const wstring    MOVE_LEFT(L"MOVE LEFT");
static const wstring    MOVE_RIGHT(L"MOVE RIGHT");

// USED FOR MOVEMENT
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';
const unsigned int P_KEY = (unsigned int)'P';
const unsigned int T_KEY = (unsigned int)'T';
const unsigned int L_KEY = (unsigned int)'L';
const unsigned int F_KEY = (unsigned int)'F';

const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int LEFT_KEY = VK_LEFT;
const unsigned int RIGHT_KEY = VK_RIGHT;
const unsigned int SPACE_KEY = VK_SPACE;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';

const int RADII = 10;