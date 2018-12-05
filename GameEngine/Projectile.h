#ifndef _TORPEDO_H              // Prevent multiple definitions if this 
#define _TORPEDO_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "player.h"
#include "d3dx9math.h"
#include "Enemy.h"

namespace projectileNS
{
	const int   WIDTH = 32;             // image width
	const int   HEIGHT = 32;           // image height
	const int   COLLISION_RADIUS = 3;   // for circular collision
	const float SPEED = TEXTURE_SIZE * PROJECTILE_SPEED;            // tiles per second
	const float MASS = 100.0f;          // mass
	const float FIRE_DELAY = 1.0f;     
	const int   TEXTURE_COLS = 4;
	const int   START_FRAME = 0;
	const int   END_FRAME = 3;
	const float ANIMATION_DELAY = 0.1f; // time between frames
}

class Projectile : public Entity
{
private:
	float fireTimer;
	Enemy closestEnemy;

public:
	Projectile();
	~Projectile();

	void update(float frameTime);
	float getMass()    const { return projectileNS::MASS; }

	// new member functions
	void fire(Player *player);                // fire torpedo from ship

	Enemy GetClosestEnemy(std::vector<Enemy> vec);
};
#endif
