#include "player.h"

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
	distance = 0; //Distance to travel. May be replaced by grid based movement in the future (after tile system is working)
	direction = 0; //Last direction player was facing.
	mana = 0; //May be moved to Entity class.
	sanity = 0; //Low priority

}

Player::~Player() {
}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) 
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}


void Player::update(float frameTime) {

	Entity::update(frameTime);
	if (xMovement == 0 && yMovement == 0) {
		//Move Up
		if (input->isKeyDown(UP_KEY || UP_KEY_2)) {
			yMovement = MOVE_LENGTH;
			distance = MOVE_SPEED;
			direction = UP;

		}
		//Move Down
		else if (input->isKeyDown(DOWN_KEY || DOWN_KEY_2)) {
			yMovement = MOVE_LENGTH;
			distance = -MOVE_SPEED;
			direction = DOWN;

		}
		//Move Left
		else if (input->isKeyDown(LEFT_KEY || LEFT_KEY_2)) {
			xMovement = MOVE_LENGTH;
			distance = MOVE_SPEED;
			direction = LEFT;

		}
		//Move Right
		else if (input->isKeyDown(RIGHT_KEY || RIGHT_KEY_2)) {
			xMovement = MOVE_LENGTH;
			distance = -MOVE_SPEED;
			direction = RIGHT;

		}
		setCurrentFrame(0);
		setFrames(0, 0);

	}
	else {
		if (xMovement != 0) {
			xMovement -= 1;
			worldX += distance;
		}
		if (yMovement != 0) {
			yMovement -= 1;
			worldY += distance;
		}
		if (xMovement == 0 && yMovement == 0) {
			setFrames(0, 0);
			setCurrentFrame(0);

		}

	}

}

//take damage
void Player::damage(int weapon) {
	setHealth(health -= weapon);
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