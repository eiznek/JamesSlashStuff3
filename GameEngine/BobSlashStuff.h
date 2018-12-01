#ifndef _BOBSLASHSTUFF_H             // Prevent multiple definitions if this 
#define _BOBSLASHSTUFF_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bob.h"
#include "player.h"
#include "NPC.h"
#include "constants.h"
#include "Projectile.h"

namespace bobSlashStuffNS {
	const int MAP_WIDTH = GAME_WIDTH/TEXTURE_SIZE;
	const int MAP_HEIGHT = GAME_HEIGHT/TEXTURE_SIZE;
	const float SCROLL_RATE = 10;
	const int g = 13; //GRASS
	const int g2 = 12; //GRASS 2
	const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, g, g2, g, g, g, g, g, g, g, g, g, g, g2, g, g, g, g, g, 0,
		0, g, g2, g, g, g, g2, g2, g, g, g, g2, g, g, g2, g, g, g, g, 0,
		0, g, g, g, g, g, g, g2, g, g, g, g, g, g, g, g, g, g, g, 0,
		0, g2, g, g2, g, g, g, g, g, g, g2, g, g2, g2, g, g, g2, g, g, 0,
		0, g, g2, g, g, g, g, g2, g, g, g2, g, g, g, g, g2, g, g, g, 0,
		0, g, g, g, g, g2, g, g, g, g2, g, g, g, g, g, g, g, g, g, 0,
		0, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g2, g, g, g, 0,
		0, g2, g2, g, g, g2, g, g2, g, g, g, g, g2, g, g, g, g, g, g, 0,
		0, g2, g2, g, g, g, g, g, g, g, g2, g, g, g, g, g, g, g, g, 0,
		0, g2, g, g, g2, g2, g, g, g2, g, g, g2, g, g, g, g2, g, g, g, 0,
		0, g, g, g, g, g, g, g, g, g2, g, g, g, g, g2, g, g, g, g, 0,
		0, g, g, g, g2, g, g, g, g, g, g, g, g, g, g, g, g, g, g, 0,
		0, g, g, g, g, g, g, g, g, g, g, g, g, g2, g, g, g, g, g, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
};

class BobSlashStuff : public Game
{
private:
	TextureManager spriteSheet;
	Image tile;
	Image menu;
	TextureManager playerSprites;
	TextureManager npcSprites;
	TextureManager fireballSprites;
	Projectile fireball;
	Player player;
	NPC npc;
	float mapX;
	float mapY;
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

