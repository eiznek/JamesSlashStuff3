//BobSlashStuff
// This class is the core of the game

#include "BobSlashStuff.h"
using namespace bobSlashStuffNS;

//=============================================================================
// Constructor
//=============================================================================
BobSlashStuff::BobSlashStuff()
{
	mapX = 0;
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

	// tile image
	if (!tile.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, &tileTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
	tile.setFrames(0, 0);
	tile.setCurrentFrame(0);


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

	for (int row = 0; row<MAP_HEIGHT; row++)       // for each row of map
	{
		tile.setY((float)(row*TEXTURE_SIZE)); // set tile Y
		for (int col = 0; col<MAP_WIDTH; col++)    // for each column of map
		{
			if (tileMap[row][col] >= 0)          // if tile present
			{
				tile.setCurrentFrame(tileMap[row][col]);    // set tile texture
				tile.setX((float)(col*TEXTURE_SIZE) + mapX);   // set tile X
															   // if tile on screen
				if (tile.getX() > -TEXTURE_SIZE && tile.getX() < GAME_WIDTH)
					tile.draw();                // draw tile
			}
		}
	}

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
