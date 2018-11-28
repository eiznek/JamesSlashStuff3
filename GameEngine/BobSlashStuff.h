#ifndef _BOBSLASHSTUFF_H             // Prevent multiple definitions if this 
#define _BOBSLASHSTUFF_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bob.h"
#include "player.h"
#include "constants.h"

namespace bobSlashStuffNS {

};

class BobSlashStuff : public Game
{
private:
	TextureManager spriteSheet;
	Image tile;
	Image menu;
	TextureManager playerSprites;
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

