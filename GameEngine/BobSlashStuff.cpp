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

	npcText.initialize(graphics, bobSlashStuffNS::FONT_SIZE, false, false, bobSlashStuffNS::FONT);
	npcText.setFontColor(SETCOLOR_ARGB(0, 255, 255, 255)); //Disable Text Visibility

	gameOverText.initialize(graphics, bobSlashStuffNS::FONT_SIZE, false, false, bobSlashStuffNS::FONT);
	gameOverText.setFontColor(SETCOLOR_ARGB(0, 255, 255, 255));

	if (spriteSheet.initialize(graphics, TILE_MAP_IMAGE) == false) // Init Tile Sheet
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

	if (enemySprites.initialize(graphics, ENEMY_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading enemy sprite sheet"));
	}

	if (mageSprites.initialize(graphics, MAGE_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading enemy sprite sheet"));
	}

	if (enemy.initialize(this, EnemyNS::WIDTH, EnemyNS::HEIGHT, 13, &enemySprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	}

	if (enemy2.initialize(this, EnemyNS::WIDTH, EnemyNS::HEIGHT, 13, &mageSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	}

	//enemy2.setX(GAME_WIDTH * 3 / 4);
	//enemy2.setY(GAME_HEIGHT / 2);

	//EnemyList.push_back(enemy);
	//EnemyList.push_back(enemy2);

	//enemy.setHealth(STARTING_HEALTH);

	player.setHealth(STARTING_HEALTH);
	player.setMana(STARTING_MANA);


	if (npcSprites.initialize(graphics, NPC_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading npc sprite sheet"));
	}

	if (npc.initialize(this, TEXTURE_SIZE, TEXTURE_SIZE, 4, &npcSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC"));
	}

	//npc.AddNPC(npc);


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

	if (healthpotSprites.initialize(graphics, HEALTHPOT_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading Health Pot sprite sheet"));
	}

	if (healthpot.initialize(this, itemNS::WIDTH, itemNS::HEIGHT, itemNS::TEXTURE_COLS, &healthpotSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthpot."));
	}

	//sword.setVisible(true);
	//sword.ItemAdd(sword);
	//sword.setX(GAME_WIDTH * 3 / 4);
	//sword.setY(GAME_HEIGHT / 2);
	//sword.ItemAdd(sword);

	if (playerWeapon.initialize(this, 32, 32, 1, &swordSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing weapon collider."));
	}
	//healthBar.initialize(graphics, &spriteSheet, 0, bobSlashStuffNS::HEALTHBAR_Y, 2.0f, graphicsNS::WHITE);

	healthBar.initialize(graphics, &spriteSheet, 0, bobSlashStuffNS::HEALTHBAR_Y, 4.0f, graphicsNS::RED);
	healthBarBg.initialize(graphics, &spriteSheet, 0, bobSlashStuffNS::HEALTHBAR_Y, 4.0f, graphicsNS::BLACK);
	manaBar.initialize(graphics, &spriteSheet, 0, bobSlashStuffNS::HEALTHBAR_Y + TEXTURE_SIZE, 4.0f, graphicsNS::BLUE);
	manaBarBg.initialize(graphics, &spriteSheet, 0, bobSlashStuffNS::HEALTHBAR_Y + TEXTURE_SIZE, 4.0f, graphicsNS::BLACK);

	for (int col = 0; col < MAP_WIDTH; col++) {

		for (int row = 0; row < MAP_HEIGHT; row++) {
			//if (entityMap[row][col] > 0) {
			//}
			switch (entityMap[row][col]) {
			case ENEMY_BADGUY:
				enemy.setX(col * TEXTURE_SIZE);
				enemy.setY(row * TEXTURE_SIZE);
				EnemyList.push_back(enemy);
				sword.ItemList.push_back(sword);
				break;

			case ENEMY_MAGE:
				enemy2.setX(col * TEXTURE_SIZE);
				enemy2.setY(row * TEXTURE_SIZE);
				EnemyList.push_back(enemy2);
				sword.ItemList.push_back(sword);
				break;

			case NPC_JAMES:
				npc.setX(col * TEXTURE_SIZE);
				npc.setY(row * TEXTURE_SIZE);
				npc.NpcList.push_back(npc);
				sword.ItemList.push_back(sword);
				break;

			default:
				continue;

			}

		}
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
	//sword.update(frameTime);
	//npc.update(frameTime);
	//enemy.update(frameTime);
	playerWeapon.update(frameTime);

	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
		(*it).update(frameTime);
	}

	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {
		(*it).update(frameTime);
	}

	for (std::vector<Item>::iterator it = sword.ItemList.begin(); it != sword.ItemList.end(); it++) {
		(*it).update(frameTime);
	}

	for (std::vector<Item>::iterator it = LootList.begin(); it != LootList.end(); it++) {
		(*it).update(frameTime);
	}


	if (player.getHealth() <= 0)
	{
		player.setActive(false);
		player.setVisible(false);
		gameOverText.setFontColor(SETCOLOR_ARGB(255, 255, 0, 0)); //RED

	}

	if (player.getActive()) {
		if (input->wasKeyPressed(SPELL_KEY_1) || input->wasKeyPressed(player.getDpadDown()))
		{
			if (player.getMana() >= FIREBALL_COST_MANA && !fireball.getActive()) {
				fireball.fire(&player);

			}

		}

		if (input->wasKeyPressed(SPELL_KEY_2) || input->wasKeyPressed(player.getDpadLeft()))
		{
			//second spell
		}

		if ((input->wasKeyPressed(ATTACK_KEY) || input->wasKeyPressed(player.getcontrollerA())) && !playerWeapon.getReady())
		{

			if (player.getDirection() == LEFT || player.getDirection() == RIGHT)
			{
				playerWeapon.setX(player.getX() + (TEXTURE_SIZE)* player.getDirection());
				playerWeapon.setY(player.getY());

			}

			if (player.getDirection() == UP || player.getDirection() == DOWN)
			{
				playerWeapon.setX(player.getX());
				playerWeapon.setY(player.getY() + (TEXTURE_SIZE)* player.getDirection() / 2);

			}

			playerWeapon.setReady(true);
			playerWeapon.setActive(true);
			playerWeapon.setVisible(true);

		}

		if (input->wasKeyPressed(DASH_KEY) || player.getcontrollerB())
		{
		//	if (player.getDirection() == UP || player.getDirection() == DOWN) { //move player toward direction faced in a fixed frame of time
		//		playerWeapon.setX(player.getX());
		//		player.setY(player.getY() + ((TEXTURE_SIZE)* player.getDirection() / 2) - DASH_DIST);
		//	}
		//	else if (player.getDirection() == LEFT || player.getDirection() == RIGHT) {
		//		player.setX(player.getX() + ((TEXTURE_SIZE)* player.getDirection()) + DASH_DIST);
		//		playerWeapon.setY(player.getY());
		//	}
		}

	}
	/*
	float dirx = enemy.getX() - player.getX();
	float diry = enemy.getY() - player.getY();
	float hyp = sqrt(dirx * dirx + diry * diry);
	dirx /= hyp;
	diry /= hyp;

	enemy.setX(dirx * MOVE_SPEED);
	enemy.setY(diry * MOVE_SPEED);
	*/
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
	//for (std::vector<NPC*>::iterator it = NPCList.begin(); it != NPCList.end(); it++) {
	//	NPC npc = *(*it);

	//}
	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
		if ((*it).collidesWith(player, collisionVector)) {
			(*it).setVisible(false);
			(*it).setActive(false);
			player.damage(ENEMY_BASE_DAMAGE);
			if (player.getDirection() == LEFT || player.getDirection() == RIGHT) {
				player.stopMoving();
				player.setX(player.getX() + TEXTURE_SIZE * -player.getDirection());
			}
			else if (player.getDirection() == UP || player.getDirection() == DOWN) {
				player.stopMoving();
				player.setY(player.getY() + TEXTURE_SIZE * -player.getDirection()/2);
			}

		}

		if ((*it).collidesWith(fireball, collisionVector)) {
			(*it).setVisible(false);
			(*it).setActive(false);
			fireball.setActive(false);
			fireball.setVisible(false);
			sword.ItemList.back().Drop(&(*it));
			LootList.push_back(sword.ItemList.back());
			sword.ItemList.pop_back();

		}
	}
	if (enemy.collidesWith(player, collisionVector)) {

	}

	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {

		if ((*it).collidesWith(fireball, collisionVector)) {
			fireball.setActive(false);
			fireball.setVisible(false);
			(*it).setActive(false);
			(*it).setVisible(false);
			sword.ItemList.back().Drop(&(*it));
			LootList.push_back(sword.ItemList.back());
			sword.ItemList.pop_back();

		}

		if ((*it).collidesWith(player, collisionVector)) {
			npcText.setFontColor(SETCOLOR_ARGB(255, 255, 255, 255)); //WHITE

			if (player.getMoveState() == MOVE_STATE::Moving) {

				switch (player.getDirection()) {

				case UP:
					if (player.getY() > (*it).getY())
						player.stopMoving();
					break;

				case DOWN:
					if (player.getY() < (*it).getY())
						player.stopMoving();
					break;

				case LEFT:
					if (player.getX() > (*it).getX())
						player.stopMoving();
					break;

				case RIGHT:
					if (player.getX() < (*it).getX())
						player.stopMoving();
					break;

				default:
					break;

				}

			}
			else if (input->wasKeyPressed(INTERACT_KEY) && (*it).getActive() == true) {
				//sword.Drop(&npc);
				sword.ItemList.back().Drop(&(*it));
				LootList.push_back(sword.ItemList.back());
				sword.ItemList.pop_back();

				(*it).setActive(false);
				(*it).setVisible(false);
				return;

			}
		}
		else {
			npcText.setFontColor(SETCOLOR_ARGB(0, 255, 255, 255));
		}
	}

	for (std::vector<Item>::iterator it = LootList.begin(); it != LootList.end(); it++) {
		if (input->wasKeyPressed(INTERACT_KEY)) {
			if ((*it).collidesWith(player, collisionVector)) {
				PlayerInventory.push_back(*it);
				LootList.erase(it);
				LootList.shrink_to_fit();
				break;
			}

		}
	}

	if (playerWeapon.collidesWith(npc, collisionVector)) {
		npc.setActive(false);
		npc.setVisible(false);
		return;

	}

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
	//npc.draw();
	fireball.draw();
	//sword.draw();
	playerWeapon.draw();
	//enemy.draw();

	for (std::vector<Item>::iterator it = sword.ItemList.begin(); it != sword.ItemList.end(); it++) {
		(*it).draw();
	}

	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
		(*it).draw();
	}

	for (std::vector<Item>::iterator it = LootList.begin(); it != LootList.end(); it++) {
		(*it).draw();
	}

	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {
		(*it).draw();
	}

	//bar backgrounds
	healthBarBg.setX((float)bobSlashStuffNS::PLAYER_HEALTH_BAR_X);
	healthBarBg.draw(graphicsNS::BLACK);

	manaBarBg.setX((float)bobSlashStuffNS::PLAYER_HEALTH_BAR_X);
	manaBarBg.draw(graphicsNS::BLACK);

	//hp and mp bars
	healthBar.setX((float)bobSlashStuffNS::PLAYER_HEALTH_BAR_X);
	healthBar.set(player.getHealth());
	healthBar.draw(graphicsNS::RED);

	manaBar.setX((float)bobSlashStuffNS::PLAYER_HEALTH_BAR_X);
	manaBar.set(player.getMana());
	manaBar.draw(graphicsNS::BLUE);

	//npcText.print(buffer, npc.getX() - TEXTURE_SIZE, npc.getY() - TEXTURE_SIZE * 2);
	npcText.print("herro" , npc.getX() - TEXTURE_SIZE, npc.getY() - TEXTURE_SIZE * 2);
	//gameOverText.print("YOU DIED", GAME_WIDTH/2, GAME_HEIGHT/2);
	gameOverText.print("YOU DIED", player.getX(), player.getY());

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void BobSlashStuff::releaseAll()
{
	playerSprites.onLostDevice();
	spriteSheet.onLostDevice();
	npcSprites.onLostDevice();
	fireballSprites.onLostDevice();
	swordSprites.onLostDevice();
	npcText.onLostDevice();
	enemySprites.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void BobSlashStuff::resetAll()
{
	playerSprites.onResetDevice();
	spriteSheet.onResetDevice();
	npcSprites.onResetDevice();
	fireballSprites.onResetDevice();
	swordSprites.onResetDevice();
	npcText.onResetDevice();
	enemySprites.onLostDevice();

	Game::resetAll();
	return;
}
