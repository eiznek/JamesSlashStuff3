//BobSlashStuff
// This class is the core of the game

#include "BobSlashStuff.h"

//=============================================================================
// Constructor
//=============================================================================
BobSlashStuff::BobSlashStuff()
{}

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

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void BobSlashStuff::update()
{
	if (input->isKeyDown(PLAYER_UP_KEY)) {
		player.Move(UP);
	}

	else if (input->isKeyDown(PLAYER_DOWN_KEY)) {
		player.Move(DOWN);
	}

	if (input->isKeyDown(PLAYER_LEFT_KEY)) {
		player.Move(LEFT);
	}

	else if (input->isKeyDown(PLAYER_RIGHT_KEY)) {
		player.Move(RIGHT);
	}

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
