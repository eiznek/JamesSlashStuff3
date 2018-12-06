#ifndef _ENEMY_H
#define _ENEMY_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <math.h>

namespace EnemyNS
{
	const int   WIDTH = 64;                // image width (each frame)
	const int   HEIGHT = 64;               // image height
	const int   X = GAME_WIDTH * 1 / 4 - TEXTURE_SIZE; // location on screen
	const int   Y = GAME_WIDTH * 1 / 4 - TEXTURE_SIZE;
	const float SPEED = TEXTURE_SIZE * ENEMY_SPEED;
	const float Enemy_DELAY = 1.0f;
}

class Enemy : public Entity 
{
private:
	int direction;
	float			oldX, oldY, oldAngle;
	float			rotation;  // current rotation rate (radians/second)
	LARGE_INTEGER	lastAttack;
	LARGE_INTEGER	tmrFreq;

public:
	Enemy();
	virtual ~Enemy();

	// inherited member functions
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	bool Enemy::isMoving();
	void chase(float XPos, float YPos);
	// new functions
	void setVelocityX(float v) { velocity.x = v; }

	void setName(std::string name) { mobName = name; }
	std::string getName() { return mobName; }

	int		movement;
	int		xMoving;
	int		yMoving;
	int		xOffset;
	int		yOffset;
	byte	standingFrame;
	int		animFrame;
	std::string mobName;

};

#endif
