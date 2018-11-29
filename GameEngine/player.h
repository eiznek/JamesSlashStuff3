#ifndef _PLAYER_H
#define _PLAYER_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <math.h>

namespace PlayerNS
{
	const int   WIDTH = 128;                // image width (each frame)
	const int   HEIGHT = 128;               // image height
	const int   X = GAME_WIDTH / 2 - TEXTURE_SIZE; // location on screen
	const int   Y = GAME_HEIGHT / 2 - TEXTURE_SIZE;
	enum MOVE_STATE {
		Moving = 0, NotMoving
	};
}

class Player: public Entity {



private:
	int direction;
	int movement;
	int mana;
	int sanity;
	int xMovement;
	int yMovement;
	PlayerNS::MOVE_STATE move_state;
	int moveTimer;
	int moveSpeed;

public:
	Player();
	virtual ~Player();

	bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void Attack();
	void update(float frameTime);

	void setVelocityX(float v) { velocity.x = v; }

	int worldX;
	int worldY;

	int getPlayerX() { return(worldX / 32 * -1); }
	int getPlayerY() { return(worldY / 32 * -1); }
	void setPlayerX(int x) { worldX = x * 32 * -1; }
	void setPlayerY(int y) { worldY = y * 32 * -1; }
	void Move(int dir) {};
	void damage(int weapon) {};
	int getDistance() { return movement; }
	int getDirection() { return direction; }
	int getMana() { return mana; }
	int getSanity() { return sanity; }
	bool getMoveState() { return move_state; }
	//void setMoveState(MOVE_STATE state) { move_state = state; }
};

#endif // !_PLAYER_H