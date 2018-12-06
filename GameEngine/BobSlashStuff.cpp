//BobSlashStuff
// This class is the core of the game

#include "BobSlashStuff.h"
using namespace bobSlashStuffNS;

//=============================================================================
// Constructor
//=============================================================================
BobSlashStuff::BobSlashStuff()
{
	mapX = 0; //for scrolling
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

	countdownText.initialize(graphics, bobSlashStuffNS::FONT_SIZE, false, false, bobSlashStuffNS::FONT);
	countdownText.setFontColor(SETCOLOR_ARGB(0, 255, 255, 255));

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

	sword.setID(ITEM_SWORD);

	if (healthpotSprites.initialize(graphics, HEALTHPOT_IMAGE) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading Health Pot sprite sheet"));
	}

	if (healthpot.initialize(this, itemNS::WIDTH, itemNS::HEIGHT, itemNS::TEXTURE_COLS, &healthpotSprites) == false) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthpot."));
	}

	healthpot.setID(HP_POTION);

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

	waveCountdown = WAVE_DELAY;

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void BobSlashStuff::update()
{
	player.update(frameTime);
	fireball.update(frameTime, EnemyList, &player);
	//sword.update(frameTime);
	//npc.update(frameTime);
	enemy.update(frameTime);
	playerWeapon.update(frameTime);

	waveCleared = true;

	
	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
		//chase
		float xDistance = player.getX() - enemy.getX();
		float yDistance = player.getY() - enemy.getY();
		float hypSqr = (xDistance * xDistance) + (yDistance * yDistance);
		hypSqr = hypSqr * hypSqr;

		if (hypSqr < GAME_WIDTH) {

			YPos += frameTime * ENEMY_SPEED * (yDistance / hypSqr);
			XPos += frameTime * ENEMY_SPEED * (xDistance / hypSqr);
			enemy.chase(XPos, YPos);
		}

		it->update(frameTime);
		if (it->getActive())
			waveCleared = false;
	}

	if (waveCleared) {
		countdownText.setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		waveCountdown -= frameTime;
	}

	if (waveCountdown <= 0 && waveCleared) {
		NextWave();
	}

	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {
		it->update(frameTime);
	}

	for (std::vector<Item>::iterator it = sword.ItemList.begin(); it != sword.ItemList.end(); it++) {
		it->update(frameTime);
	}

	for (std::vector<Item>::iterator it = healthpot.ItemList.begin(); it != healthpot.ItemList.end(); it++) {
		it->update(frameTime);
	}

	for (std::vector<Item>::iterator it = LootList.begin(); it != LootList.end(); it++) {
		it->update(frameTime);
	}

	if (player.getActive()) {
		if (player.getHealth() <= 0)
		{
			player.setActive(false);
			player.setVisible(false);
			gameOverText.setFontColor(SETCOLOR_ARGB(255, 255, 0, 0)); //RED
		}

		if (player.getMana() < STARTING_MANA) {
			player.setMana(player.getMana() + frameTime * MANA_REGEN_RATE);

			if (player.getMana() > STARTING_MANA)
				player.setMana(STARTING_MANA);

		}

		if (input->wasKeyPressed(SPELL_KEY_1) || input->getGamepadX(0))
		{
			if (player.getMana() >= FIREBALL_COST_MANA && !fireball.getActive()) {
				fireball.fire(&player, EnemyList);

			}

		}

		if (input->wasKeyPressed(SPELL_KEY_2) )
		{
			//second spell
		}

		if ((input->wasKeyPressed(ATTACK_KEY) || input->getGamepadA(0)) && !playerWeapon.getReady())
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

		if (input->wasKeyPressed(ITEM_KEY_1) || input->getGamepadB(0)) {

			for (std::vector<Item>::iterator it = PlayerInventory.begin(); it != PlayerInventory.end(); it++) {
				if (it->getID() == ITEM_SLOT_1) {
					player.setHealth(STARTING_HEALTH);
					PlayerInventory.erase(it);
					break;
				}

			}
		}

		if (input->wasKeyPressed(DASH_KEY) || input->wasKeyPressed(0x0200)) {
			if (player.getDashState() == NotDashing) {
				player.Dash(frameTime);
			}
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
	//for (std::vector<NPC*>::iterator it = NPCList.begin(); it != NPCList.end(); it++) {
	//	NPC npc = *(*it);

	//}
	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
		if (it->collidesWith(player, collisionVector)) {
			if (!waveCleared)
				player.damage(ENEMY_BASE_DAMAGE);
			//knockback
			if (player.getDirection() == LEFT || player.getDirection() == RIGHT) {
				player.stopMoving();
				player.setX(player.getX() + TEXTURE_SIZE * -player.getDirection());
			}
			else if (player.getDirection() == UP || player.getDirection() == DOWN) {
				player.stopMoving();
				player.setY(player.getY() + TEXTURE_SIZE * -player.getDirection()/2);
			}
		}

		if (it->collidesWith(fireball, collisionVector)) {
			it->setVisible(false);
			it->setActive(false);
			//EnemyList.erase(it);
			fireball.setActive(false);
			fireball.setVisible(false);
			sword.ItemList.back().Drop(&(*it));
			LootList.push_back(sword.ItemList.back());
			sword.ItemList.pop_back();

		}

		if (it->collidesWith(playerWeapon, collisionVector)) {
			it->setVisible(false);
			it->setActive(false);
			sword.ItemList.back().Drop(&(*it));
			LootList.push_back(sword.ItemList.back());
			sword.ItemList.pop_back();
			//EnemyList.erase(it);

		}

	}

	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {

		if (it->collidesWith(fireball, collisionVector)) {
			fireball.setActive(false);
			fireball.setVisible(false);
			it->setActive(false);
			it->setVisible(false);
			healthpot.ItemList.back().Drop(&(*it));
			LootList.push_back(healthpot.ItemList.back());
			healthpot.ItemList.pop_back();

		}

		if (it->collidesWith(player, collisionVector)) {
			npcText.setFontColor(SETCOLOR_ARGB(255, 255, 255, 255)); //WHITE

			if (player.getMoveState() == MOVE_STATE::Moving) {

				switch (player.getDirection()) {

				case UP:
					if (player.getY() > it->getY())
						player.stopMoving();
					break;

				case DOWN:
					if (player.getY() < it->getY())
						player.stopMoving();
					break;

				case LEFT:
					if (player.getX() > it->getX())
						player.stopMoving();
					break;

				case RIGHT:
					if (player.getX() < it->getX())
						player.stopMoving();
					break;

				default:
					break;

				}

			}
			else if ((input->wasKeyPressed(INTERACT_KEY) || input->wasKeyPressed(0x2000)) && it->getActive() == true) {
				//sword.Drop(&npc);
				healthpot.ItemList.back().Drop(&*it);
				LootList.push_back(healthpot.ItemList.back());
				healthpot.ItemList.pop_back();

				it->setActive(false);
				it->setVisible(false);
				return;

			}

			if (it->collidesWith(playerWeapon, collisionVector)) {
				it->setVisible(false);
				it->setActive(false);
				healthpot.ItemList.back().Drop(&(*it));
				LootList.push_back(healthpot.ItemList.back());
				healthpot.ItemList.pop_back();

			}

		}
		else {
			npcText.setFontColor(SETCOLOR_ARGB(0, 255, 255, 255));
		}
	}

	for (std::vector<Item>::iterator it = LootList.begin(); it != LootList.end(); it++) {
		if (input->wasKeyPressed(INTERACT_KEY)) {
			if (it->collidesWith(player, collisionVector)) {
				PlayerInventory.push_back(*it);
				//SAFE_DELETE(*it);
				LootList.erase(it);
				break;
			}

		}
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
	playerWeapon.draw(SETCOLOR_ARGB(255, 0, 0, 0));
	//enemy.draw();

	for (std::vector<Item>::iterator it = sword.ItemList.begin(); it != sword.ItemList.end(); it++) {
		it->draw();
	}

	for (std::vector<Item>::iterator it = healthpot.ItemList.begin(); it != healthpot.ItemList.end(); it++) {
		it->draw();
	}

	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
		it->draw();
	}

	for (std::vector<Item>::iterator it = LootList.begin(); it != LootList.end(); it++) {
		it->draw();
	}

	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {
		it->draw();
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

	snprintf(buffer, sizeof(buffer), "%d", (int)ceil(waveCountdown));
	countdownText.print(buffer, GAME_WIDTH / 2 - bobSlashStuffNS::FONT_SIZE/2, GAME_HEIGHT * 1/8);
	memset(buffer, 0, sizeof(buffer));

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

void BobSlashStuff::NextWave() {
	srand(time(0));
	int x = 0;

	//if (!sword.ItemList.empty()){
	//	for (std::vector<Item>::iterator it = sword.ItemList.begin(); it != sword.ItemList.end(); it++) {
	//		//SAFE_DELETE(*it);
	//		delete(&*it);
	//	}
	//}

	//if (!healthpot.ItemList.empty()){
	//	for (std::vector<Item>::iterator it = healthpot.ItemList.begin(); it != healthpot.ItemList.end(); it++) {
	//		delete(&*it);
	//	}
	//}

	//if (!EnemyList.empty()){
	//	for (std::vector<Enemy>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++) {
	//		delete(&*it);
	//	}
	//}

	//if (!npc.NpcList.empty()){
	//	for (std::vector<NPC>::iterator it = npc.NpcList.begin(); it != npc.NpcList.end(); it++) {
	//		delete(&*it);
	//	}
	//}

	EnemyList.clear();
	npc.NpcList.clear();
	sword.ItemList.clear();
	healthpot.ItemList.clear();

	for (int col = 0; col < MAP_WIDTH; col++) {

		for (int row = 0; row < MAP_HEIGHT; row++) {

			int spawn = 0;
			if (x < MAX_SPAWNS) {
				if ((rand() % 100) < SPAWN_PERCENT && tileMap[row][col] != 0) {
					spawn = rand() % sizeof(ENTITY);
					x++;
				}
			}

			entityMap[row][col] = spawn;

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
				healthpot.ItemList.push_back(healthpot);
				break;

			default:
				continue;

			}

		}

		countdownText.setFontColor(SETCOLOR_ARGB(0, 255, 255, 255));
		waveCleared = false;
		waveCountdown = WAVE_DELAY;

	}
}
