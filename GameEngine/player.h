#ifndef _PLAYER_H
#define _PLAYER_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "PlayerWeapon.h"
#include <math.h>


namespace PlayerNS
{
	const int   WIDTH = 32;                // image width (each frame)
	const int   HEIGHT = 32;               // image height
	const int   X = GAME_WIDTH / 2 - TEXTURE_SIZE; // location on screen
	const int   Y = GAME_HEIGHT / 2 - TEXTURE_SIZE;
}

class Player: public Entity {

private:
	int direction;
	int movement;
	int mana;
	int sanity;
	float xMovement;
	float yMovement;
	MOVE_STATE move_state;
	DASH_STATE dash_state;
	int oldX;
	int oldY;
	int moveTimer;
	int moveSpeed;
	int animFrame;
	float distDashedPerFrame;
	float dashTimeLeft;
	float dashCD;
	//controller
	int leftTrigger, leftTriggerUndead, rightTrigger, rightTriggerUndead;
	int leftThumbX, leftThumbXUndead, leftThumbY, leftThumbYUndead;
	int rightThumbX, rightThumbXUndead, rightThumbY, rightThumbYUndead;
	int controllerA, controllerB, controllerX, controllerY;
	int dpadUp, dpadDown, dpadLeft, dpadRight;
	//PlayerWeapon weapon;

public:
	Player();
	virtual ~Player();

	bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);

	void Attack();
	void stopMoving();
	void Dash(float frametime);

	int getPlayerX();
	int getPlayerY();
	int getDistance() { return movement; }
	int getDirection() { return direction; }
	int getMana() { return mana; }
	void setMana(int amt) { mana = amt; }
	//void obstructed(float colX, float colY);
	int getSanity() { return sanity; }
	bool getMoveState() { return move_state; }
	float getDistDashedPerFrame() { return distDashedPerFrame; }
	float getDashTimeLeft() { return dashTimeLeft; }
	void setDashTimeLeft(float dtl) { dashTimeLeft = dtl; }
	void setDashCD(float cd) { dashCD = cd; }
	//void setMoveState(MOVE_STATE state) { move_state = state; }

	void drawController(int n);

	int getcontrollerA() { return controllerA; }
	int getcontrollerB() { return controllerB; }
	int getcontrollerX() { return controllerX; }
	int getcontrollerY() { return controllerY; }
	int getDpadUp() { return dpadUp; }
	int getDpadDown() { return dpadDown; }
	int getDpadLeft() { return dpadLeft; }
	int getDpadRight() { return dpadRight; }


};

#endif // !_PLAYER_H