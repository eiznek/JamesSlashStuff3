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
	mapY = 0;
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

							// Init Tile Sheet
	if (spriteSheet.initialize(graphics, TILE_MAP_IMAGE) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading tile sheet"));


	if (tile.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SHEET_COLS, &spriteSheet) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
	}

	if (playerSprites.initialize(graphics, PLAYER_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading player sprite sheet"));
	}

	if (player.initialize(this, TEXTURE_SIZE, TEXTURE_SIZE, 4, &playerSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	}

	player.setHealth(STARTING_HEALTH);

	if (npcSprites.initialize(graphics, NPC_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading npc sprite sheet"));
	}

	if (npc.initialize(this, TEXTURE_SIZE, TEXTURE_SIZE, 4, &npcSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC"));
	}

	if (fireballSprites.initialize(graphics, FIREBALL_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading fireball sprite sheet"));
	}

	if (fireball.initialize(this, projectileNS::WIDTH, projectileNS::HEIGHT, projectileNS::TEXTURE_COLS, &fireballSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile."));
	}
	fireball.setFrames(projectileNS::START_FRAME, projectileNS::END_FRAME);
	fireball.setCurrentFrame(projectileNS::START_FRAME);

	if (swordSprites.initialize(graphics, WOODEN_SWORD_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading sword sprites."));
	}

	if (sword.initialize(this, itemNS::WIDTH, itemNS::HEIGHT, itemNS::TEXTURE_COLS, &swordSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword."));
	}

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void BobSlashStuff::update()
{
	player.update(frameTime);
	fireball.update(frameTime);
	sword.update(frameTime);
	npc.update(frameTime);

	if (input->wasKeyPressed(SPELL_KEY_1)) {
		if (player.getMana() >= FIREBALL_COST_MANA && fireball.getActive() == false) {
			fireball.fire(&player);
			player.setMana(player.getMana() - FIREBALL_COST_MANA);
		}

	}

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
	if (player.collidesWith(npc, collisionVector)) {
		if (player.getMoveState() == MOVE_STATE::Moving) {
			switch (player.getDirection()) {
			case UP:
				if (!(player.getY() > npc.getY()))
					return;
				player.stopMoving();
				break;
			case DOWN:
				if (!(player.getY() < npc.getY()))
					return;
				player.stopMoving();
				break;
			case LEFT:
				if (!(player.getX() > npc.getX()))
					return;
				player.stopMoving();
				break;
			case RIGHT:
				if (!(player.getX() < npc.getX()))
					return;
				player.stopMoving();
				break;

			default:
				break;
			}

		}
		else if (input->wasKeyPressed(INTERACT_KEY) && npc.getActive() == true) {
			sword.Drop(&npc);
			npc.setActive(false);
			npc.setVisible(false);
			return;

		}
	}

	if (player.collidesWith(sword, collisionVector) && input->wasKeyPressed(INTERACT_KEY)) {
		sword.PickUp(&player);

	}

	//if(player.weapon.collideswith(npc,collisionVector){
	//	if(input->wasKeyPressed(INTERACT_KEY)){
	//		npc.setX(999);
	//	}
	//}
}

//=============================================================================
// Render game items
//=============================================================================
void BobSlashStuff::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	for (int col = 0; col < MAP_WIDTH; col++) {
		tile.setX((col * TEXTURE_SIZE));

		for (int row = 0; row < MAP_HEIGHT; row++) {

			if (tileMap[row][col] >= 0){
				tile.setY((row * TEXTURE_SIZE));
				tile.setCurrentFrame(tileMap[row][col]);
				tile.draw();

			}
		}
	}
	player.draw();
	npc.draw();
	fireball.draw();
	sword.draw();

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


