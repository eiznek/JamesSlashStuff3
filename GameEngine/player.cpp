#include "player.h"
#include <iostream>
#include <string>
using namespace std;
using namespace PlayerNS;

Player::Player() : Entity() {
	spriteData.width = WIDTH;           // size of EntityPlayer
	spriteData.height = HEIGHT;
	spriteData.x = X;                   // location on screen
	spriteData.y = Y;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
	edge.top = 0;             // ROTATED_BOX collision edges
	edge.bottom = 32;
	edge.left = 0;
	edge.right = 32;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = 0.1f;
	startFrame = 0;     // first frame of animation
	endFrame = 3;     // last frame of animation
	currentFrame = startFrame;
	radius = WIDTH / 2.0;
	collisionType = entityNS::BOX;
	worldX = 0;
	worldY = 0;
	movement = 0; //Distance to travel. May be replaced by grid based movement in the future (after tile system is working)
	direction = 0; //Last direction player was facing.
	mana = 0; //May be moved to Entity class.
	sanity = 0; //Low priority
	moveTimer = 0; //
	moveSpeed = 1; //num tiles per second
	move_state = MOVE_STATE::NotMoving;

	//WORD gamepadbtn = input->getGamepadButtons(0);
	//WORD gamepadUP = input->getGamepadDPadUp(0);
}

Player::~Player() {
}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) 
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
	//input->checkControllers(); //this is already called in init input
}


void Player::update(float frameTime) {

	Entity::update(frameTime);
	yMovement = 0;
	xMovement = 0;

	input->vibrateControllers(frameTime);
	std::cout << input->getControllerState(0);
	std::cout << input->getControllerState(1);
	std::cout << "hi";
	std::cout << input->getControllerState(2);
	std::cout << input->getControllerState(3);
		//Move Up
		if (input->isKeyDown(UP_KEY) || input->isKeyDown(VK_GAMEPAD_DPAD_UP)) {
			if (spriteData.y <= 0) {
				xMovement = 0;
				return;
			}

			//move_state = MOVE_STATE::Moving;
			//if (move_state == MOVE_STATE::NotMoving) {
			//	moveTimer = moveSpeed; //in tiles per second
			//	//old_pos = new_pos
			//}
			move_state = MOVE_STATE::Moving;
			direction = UP;

			yMovement = MOVE_LENGTH;
			movement = -MOVE_SPEED;
		}
		//Move Down
		else if (input->isKeyDown(DOWN_KEY)) {
			if (spriteData.y >= GAME_HEIGHT - SCREEN_HEIGHT - PLAYER_Y_OFFSET) {
				xMovement = 0;
				return;
			}
			yMovement = MOVE_LENGTH;
			movement = MOVE_SPEED;
			direction = DOWN;

		}
		//Move Left
		if (input->isKeyDown(LEFT_KEY)) {
			if (spriteData.x <= 0) {
				xMovement = 0;
				return;
			}

			xMovement = MOVE_LENGTH;
			movement = -MOVE_SPEED;
			direction = LEFT;

		}
		//Move Right
		else if (input->isKeyDown(RIGHT_KEY)) {
			if (spriteData.x >= GAME_WIDTH - SCREEN_WIDTH - PLAYER_X_OFFSET) {
				xMovement = 0;
				return;
			}
			xMovement = MOVE_LENGTH;
			movement = MOVE_SPEED;
			direction = RIGHT;

		}
		spriteData.x += (xMovement * movement) * frameTime * 10;
		spriteData.y += ( yMovement * movement) * frameTime * 10;
		setCurrentFrame(0);
		setFrames(0, 0);
	//}
}


//Player Attacking
//Could be unnecessary and most suitably implemented elsewhere instead. i.e. "BobSlashStuff.cpp"
void Player::Attack() { 
	//Method 1, check for entity in tile

	/* pseudo code
	tile = getTile(direction); //get tile in the direction that player is facing
	setFrames(FRAME_START_ATTACK, FRAME_END_ATTACK); //set animation frames for attacking
	setCurrentFrame(FRAME_START_ATTACK); 

	if (tile.containsEntity()){
		Entity target = tile.getEntity();
		if (target.isHostile()) //checks if entity is hostile
			target.damage(weapon); //damage Enemy.
		else
			target.talk(); //interact with NPC
	}
	else
		return;

	*/

}