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
	edge.bottom = HEIGHT;
	edge.left = 0;
	edge.right = WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = 0.1f;
	startFrame = 0;     // first frame of animation
	endFrame = cols - 1;     // last frame of animation
	currentFrame = startFrame;
	radius = WIDTH / 2.0;
	collisionType = entityNS::BOX;
	xMovement = 0;
	yMovement = 0;
	movement = 0; 
	direction = 0; //Last direction player was facing.
	mana = 0; //May be moved to Entity class.
	sanity = 0; //Low priority
	moveTimer = 0; //
	moveSpeed = 1; //num tiles per second
	animFrame = 0;
	move_state = MOVE_STATE::NotMoving;
}

Player::~Player() {
}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}


void Player::update(float frameTime) {

	Entity::update(frameTime);
	drawController(0);
	drawController(1);
	drawController(2);
	drawController(3);

	if (move_state == MOVE_STATE::NotMoving) {

		//Move Up
		if (input->isKeyDown(UP_KEY) || input->getGamepadDPadUp(0) || input->getGamepadThumbLY(0) > 20000) {
			if (getY() <= 0 + TEXTURE_SIZE) {
				yMovement = 0;
				return;
			}

			move_state = MOVE_STATE::Moving;
			moveTimer = moveSpeed; //in tiles per second

			yMovement = MOVE_LENGTH;
			movement = -MOVE_SPEED;
			animFrame = 12;
			direction = UP;
		}

		//Move Down
		else if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0) || input->getGamepadThumbLY(0) < -20000) {
			if (getY() >= GAME_HEIGHT - TEXTURE_SIZE) {
				yMovement = 0;
				return;
			}

			yMovement = MOVE_LENGTH;
			movement = MOVE_SPEED;
			animFrame = 0;
			direction = DOWN;

		}

		//Move Left
		else if (input->isKeyDown(LEFT_KEY) || input->getGamepadDPadLeft(0) || input->getGamepadThumbLX(0) < -20000) {
			if (getX() <= 0 + TEXTURE_SIZE) {
				xMovement = 0;
				return;
			}

			xMovement = MOVE_LENGTH;
			movement = -MOVE_SPEED;
			animFrame = 4;
			direction = LEFT;

		}

		//Move Right
		else if (input->isKeyDown(RIGHT_KEY) || input->getGamepadDPadRight(0) || input->getGamepadThumbLX(0) > 20000) {
			if (getX() >= GAME_WIDTH - TEXTURE_SIZE) {
				xMovement = 0;
				return;
			}

			xMovement = MOVE_LENGTH;
			movement = MOVE_SPEED;
			animFrame = 8;
			direction = RIGHT;

		}

		if (!xMovement == 0 || !yMovement == 0) {
			move_state = MOVE_STATE::Moving;
			oldX = getX();
			oldY = getY();

		}

		setCurrentFrame(animFrame);
		setFrames(animFrame, animFrame + cols - 1);

	}

	else if(move_state == MOVE_STATE::Moving) {

		if (xMovement != 0) {
			setX(getX() + (xMovement * movement) * 2);
			stopMoving();
		}

		if (yMovement != 0) {
			setY(getY() + (yMovement * movement) * 2);
			stopMoving();
		}

		if (xMovement == 0 && yMovement == 0) {
			setCurrentFrame(animFrame);
			setFrames(animFrame, animFrame);
		}

			 
	}

}

void Player::stopMoving() {
	//if (direction == LEFT || direction == RIGHT)
	//	setX(getX() - movement);
	//else if (direction == UP || direction == DOWN)
	//	setY(getY() - movement);

	xMovement = 0;
	yMovement = 0;

	setCurrentFrame(animFrame);
	setFrames(animFrame, animFrame);

	move_state = MOVE_STATE::NotMoving;
}

//void Player::obstructed(float colX, float colY) {
//
//}

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

	//Method 2, Collision

}

void Player::drawController(int n)
{
	//controller.draw();
	// get trigger and thumbstick positions
	leftTrigger = input->getGamepadLeftTrigger(n);
	//leftTriggerUndead = input->getGamepadLeftTriggerUndead(n);
	rightTrigger = input->getGamepadRightTrigger(n);
	//rightTriggerUndead = input->getGamepadRightTriggerUndead(n);
	leftThumbX = input->getGamepadThumbLX(n);
	//leftThumbXUndead = input->getGamepadThumbLXUndead(n);
	leftThumbY = input->getGamepadThumbLY(n);
	//leftThumbYUndead = input->getGamepadThumbLYUndead(n);
	rightThumbX = input->getGamepadThumbRX(n);
	//rightThumbXUndead = input->getGamepadThumbRXUndead(n);
	rightThumbY = input->getGamepadThumbRY(n);
	//rightThumbYUndead = input->getGamepadThumbRYUndead(n);
	input->gamePadVibrateLeft(n, leftTrigger << 8, 0.1f);   // vibrate left
	input->gamePadVibrateRight(n, rightTrigger << 8, 0.1f); // vibtate right

	// Display button states
	//if (input->getGamepadStart(n))
	//if (input->getGamepadRightShoulder(n))
	//if (input->getGamepadA(n))
	//if (input->getGamepadB(n))
	//if (input->getGamepadX(n))
	//if (input->getGamepadY(n))
	if (input->getGamepadDPadUp(n))
	{

	}
	//if (input->getGamepadDPadRight(n))
	//if (input->getGamepadDPadDown(n))
	//if (input->getGamepadDPadLeft(n))
	//if (input->getGamepadLeftShoulder(n))
	//if (input->getGamepadBack(n))

}
