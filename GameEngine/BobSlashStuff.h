#ifndef _BOBSLASHSTUFF_H             // Prevent multiple definitions if this 
#define _BOBSLASHSTUFF_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bob.h"
#include "player.h"

namespace bobSlashStuffNS {

	const char FONT[] = "Arial Bold";  // font
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const int TEXTURE_SIZE = 128;
	const int TEXTURE_COLS = 4;
	const int MAP_HEIGHT = 4;
	const int MAP_WIDTH = 16;
	const float SCROLL_RATE = 10;
	const float MAX_PLAYER_SPEED = 20;
	const int __ = -1;                  // empty tile

	const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
		__, 0,__,__, 1,__,__,__,12,13,__,__,__,__, 0,__,
		__,__,__,__,__,__,__,11,__,__,__,__,__,__,__,__,
		__,__,__, 2,__,__,__,15,__, 3,__,__,__,__, 3, 2,
		5, 4, 5, 6, 4, 4, 5,15, 4, 7, 5,__,14, 5, 7, 6
	};
}

class BobSlashStuff : public Game
{
private:
	TextureManager tileTextures;
	Image tile;
	Image menu;
	Player player;
	float mapX;
	bool menuOn;

public:
	//Constructor
	BobSlashStuff();

	//Destructor
	~BobSlashStuff();


	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();

};

#endif

