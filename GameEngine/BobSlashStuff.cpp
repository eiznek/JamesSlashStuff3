//BobSlashStuff
// This class is the core of the game

#include "BobSlashStuff.h"
using namespace bobSlashStuffNS;

//=============================================================================
// Constructor
//=============================================================================
BobSlashStuff::BobSlashStuff()
{

}

//=============================================================================
// Destructor
//=============================================================================
BobSlashStuff::~BobSlashStuff()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void BobSlashStuff::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	if (playerSprites.initialize(graphics, PLAYER_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading player sprite sheet"));
	}

	if (player.initialize(this, TEXTURE_SIZE, TEXTURE_SIZE, 4, &playerSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	}

	player.setHealth = STARTING_HEALTH;

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void BobSlashStuff::update()
{
	player.update(frameTime);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void BobSlashStuff::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void BobSlashStuff::collisions()
{
	VECTOR2 collisionVector;


}

//=============================================================================
// Render game items
//=============================================================================
void BobSlashStuff::render()
{
	graphics->spriteBegin();                // begin drawing sprites


	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void BobSlashStuff::releaseAll()
{
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void BobSlashStuff::resetAll()
{

	Game::resetAll();
	return;
}
