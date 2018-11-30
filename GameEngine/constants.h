// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "BobSlashStuff";
const char GAME_TITLE[] = "BobSlashStuff";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
const int TEXTURE_SIZE = 32;
const int SCREEN_WIDTH = GAME_WIDTH / TEXTURE_SIZE + 2;
const int SCREEN_HEIGHT = GAME_HEIGHT / TEXTURE_SIZE + 2;
const int PLAYER_X_OFFSET = (GAME_WIDTH / 2 - TEXTURE_SIZE) / TEXTURE_SIZE;
const int PLAYER_Y_OFFSET = (GAME_HEIGHT / 2 - TEXTURE_SIZE) / (TEXTURE_SIZE / 2);

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const int MOVE_SPEED = 3; //tiles per second
const float MOVE_LENGTH = TEXTURE_SIZE/FRAME_RATE;
const int STARTING_HEALTH = 100;
const int STARTING_MANA = 100;
const int STARTING_SANITY = 100;
const int PLAYER_BASE_ATTACK = 20;

//spacewar
const float GRAVITY = 6.67428e-11f;             // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;

// graphic images
//spacewar
const char NEBULA_IMAGE[] =   "pictures\\orion.jpg";     // photo source NASA/courtesy of nasaimages.org 
const char TEXTURES_IMAGE[] = "pictures\\textures.png";  // game textures
//bobslashstuff
const char TILE_MAP_IMAGE[] = "pictures\\maintiles\\tileSheet.png";
const char PLAYER_IMAGE[] = "pictures\\playerSprites.png";
const char NPC_IMAGE[] = "pictures\\npcSprites.png";

const int TEXTURE_SHEET_COLS = 30;

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR INTERACT_KEY = 'F';
//movement
const UCHAR UP_KEY = VK_UP; //UP ARROW
const UCHAR LEFT_KEY = VK_LEFT; //LEFT ARROW
const UCHAR DOWN_KEY = VK_DOWN; //DOWN ARROW
const UCHAR RIGHT_KEY = VK_RIGHT; //RIGHT ARROW
const UCHAR UP_KEY_2 = 0x57; //W
const UCHAR LEFT_KEY_2 = 0x41; //A
const UCHAR DOWN_KEY_2 = 0x53; //S
const UCHAR RIGHT_KEY_2 = 0x44; //D
//combat
const UCHAR ATTACK_KEY = 0x43; // C; //may also be used to interact
const UCHAR SPELL_KEY_1 = 0x5A; //Z
const UCHAR SPELL_KEY_2 = 0x58; //X
//const UCHAR SPELL_KEY_3 = 
const UCHAR ITEM_KEY_1 = VK_LCONTROL; //Left CTRL
const UCHAR ITEM_KEY_2 = VK_LSHIFT; //Left SHIFT
const UCHAR SPELL_KEY_1_ALT = 0x31; //1
const UCHAR SPELL_KEY_2_ALT = 0x32; //2
const UCHAR SPELL_KEY_3_ALT = 0x33; //3
const UCHAR ITEM_KEY_1_ALT = 0x45; //E
const UCHAR ITEM_KEY_2_ALT = 0x52; //R
const UCHAR SWAP_SPELLBAR_KEY = VK_LMENU; //Left ALT
const UCHAR SWAP_SPELLBAR_KEY_2 = VK_TAB; //TAB

//spacewar
// weapon types
enum WEAPON {TORPEDO, SHIP, PLANET};
enum DIRECTION { UP, DOWN, LEFT, RIGHT };
enum MOVE_STATE {
	Moving = 0, NotMoving
};

#endif
