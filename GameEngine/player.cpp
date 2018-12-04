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
	direction = DOWN; //Last direction player was facing.
	mana = STARTING_MANA; //May be moved to Entity class.
	sanity = STARTING_SANITY; //Low priority
	moveTimer = 0; //
	moveSpeed = 1; //num tiles per second
	animFrame = 0;
	move_state = MOVE_STATE::NotMoving;
	dash_state = DASH_STATE::NotDashing;
	distDashedPerFrame = (TEXTURE_SIZE * DASH_DIST) / (DASH_TIME * FRAME_RATE);
}

Player::~Player() {
}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

int Player::getPlayerX() { return spriteData.x; }
int Player::getPlayerY() { return spriteData.y; }

void Player::update(float frameTime) {

	Entity::update(frameTime);
	drawController(0);
	drawController(1);
	drawController(2);
	drawController(3);

	if (move_state == MOVE_STATE::NotMoving) {

		//Move Up
		if (input->isKeyDown(UP_KEY) || input->getGamepadThumbLY(0) > THUMBSTICK_TILT) {
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
		else if (input->isKeyDown(DOWN_KEY) || input->getGamepadThumbLY(0) < -THUMBSTICK_TILT) {
			if (getY() >= GAME_HEIGHT - TEXTURE_SIZE * 2) {
				yMovement = 0;
				return;
			}

			yMovement = MOVE_LENGTH;
			movement = MOVE_SPEED;
			animFrame = 0;
			direction = DOWN;

		}

		//Move Left
		else if (input->isKeyDown(LEFT_KEY) || input->getGamepadThumbLX(0) < -THUMBSTICK_TILT) {
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
		else if (input->isKeyDown(RIGHT_KEY) || input->getGamepadThumbLX(0) > THUMBSTICK_TILT) {
			if (getX() >= GAME_WIDTH - TEXTURE_SIZE * 2) {
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
			setX(getX() + (xMovement * movement) * 2); //multiplied by 2 because it takes 2 frames to update movement once.
			//xMovement -= (1 /FRAME_RATE);

		}

		if (yMovement != 0) {
			setY(getY() + (yMovement * movement) * 2);
			//yMovement -= (1 /FRAME_RATE);

		}

		stopMoving();
 
	}

	if (input->wasKeyPressed(ATTACK_KEY)) {
		Attack();
	}

	if (input->wasKeyPressed(DASH_KEY)) {
		//if (dash_state == DASH_STATE::Dashing) {
		//	this->setActive(false); //disable collision
		//}
		Dash(frameTime);
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


//Player Attacking
//Could be unnecessary and most suitably implemented elsewhere instead. i.e. "BobSlashStuff.cpp"
void Player::Attack() {

}

void Player::Dash(float frametime) {
	if (dash_state == NotDashing || (getDashTimeLeft() <= DASH_TIME && getDashTimeLeft() > 0)) {
		setDashTimeLeft(getDashTimeLeft() - frametime);
		if (direction == LEFT || direction == RIGHT) {
			setX(getX() + getDistDashedPerFrame());
			setY(getY());
		}
		else if (direction == UP || direction == DOWN) {
			setX(getX());
			setY(getY() + getDistDashedPerFrame());
		}
	}
	if (dash_state = Dashing) {
		setActive(false);
		if (getDashTimeLeft() <= 0) {
			dash_state = NotDashing;
		}
	}

	else if (getDashTimeLeft() <= 0) {
		setDashTimeLeft(DASH_TIME);
	}
}

void Player::drawController(int n)
{
	//controller.draw();
	// get trigger and thumbstick positions
	leftTrigger = input->getGamepadLeftTrigger(n);
	rightTrigger = input->getGamepadRightTrigger(n);
	leftThumbX = input->getGamepadThumbLX(n);
	leftThumbY = input->getGamepadThumbLY(n);
	rightThumbX = input->getGamepadThumbRX(n);
	rightThumbY = input->getGamepadThumbRY(n);
	input->gamePadVibrateLeft(n, leftTrigger << 8, 0.1f);   // vibrate left
	input->gamePadVibrateRight(n, rightTrigger << 8, 0.1f); // vibtate right
	controllerA = input->getGamepadA(n);
	controllerB = input->getGamepadB(n);
	controllerX = input->getGamepadX(n);
	controllerY = input->getGamepadY(n);
	dpadUp = input->getGamepadDPadUp(n);
	dpadDown = input->getGamepadDPadDown(n);
	dpadLeft = input->getGamepadDPadLeft(n);
	dpadRight = input->getGamepadDPadRight(n);

}
