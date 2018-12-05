#include "Projectile.h"


Projectile::Projectile() : Entity()
{
	active = false;                                 // torpedo starts inactive
	spriteData.width = projectileNS::WIDTH;     // size of 1 image
	spriteData.height = projectileNS::HEIGHT;
	spriteData.rect.bottom = projectileNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = projectileNS::WIDTH;
	cols = projectileNS::TEXTURE_COLS;
	frameDelay = projectileNS::ANIMATION_DELAY;
	startFrame = projectileNS::START_FRAME;       // first frame of ship animation
	endFrame = projectileNS::END_FRAME;         // last frame of ship animation
	currentFrame = startFrame;
	radius = projectileNS::COLLISION_RADIUS;  // for circular collision
	visible = false;
	fireTimer = 0.0f;
	mass = projectileNS::MASS;
	collisionType = entityNS::CIRCLE;
	isHoming = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Projectile::update(float frameTime, std::vector<Enemy> vec, Player *player)
{
	fireTimer -= frameTime;                     // time remaining until fire enabled

	if (visible == false)
		return;

	if (fireTimer < 0)                           // if ready to fire
	{
		visible = false;                        // old fire off
		active = false;
	}

	Image::update(frameTime);
	//if (isHoming == false && EnemyListAlive(vec) > 0) {
	if (isHoming == false ) {
		spriteData.x += frameTime * velocity.x;     // move along X 
		spriteData.y += frameTime * velocity.y;     // move along Y
	}
	else { //homing
		Enemy closest = GetClosestEnemy(vec);
		float angle = CALC_ANGLE_TO_ENEMY(closest.getY(), getY(), closest.getX(), getX());

		float angle2 = (float)atan2((closest.getX()- spriteData.y), (closest.getY() - spriteData.x));
		float a3 = (float)atan2((closest.getY() - spriteData.y), (closest.getX() - spriteData.x));

		setX( getX() + (float)cos(a3) * projectileNS::SPEED * frameTime);
		setY(getY() + (float)sin(a3) * projectileNS::SPEED * frameTime);

	}
	//											// Wrap around screen edge
	//if (spriteData.x > GAME_WIDTH)              // if off right screen edge
	//	spriteData.x = -projectileNS::WIDTH;       // position off left screen edge
	//else if (spriteData.x < -projectileNS::WIDTH)  // else if off left screen edge
	//	spriteData.x = GAME_WIDTH;              // position off right screen edge
	//if (spriteData.y > GAME_HEIGHT)             // if off bottom screen edge
	//	spriteData.y = -projectileNS::HEIGHT;      // position off top screen edge
	//else if (spriteData.y < -projectileNS::HEIGHT) // else if off top screen edge
	//	spriteData.y = GAME_HEIGHT;             // position off bottom screen edge
}


//=============================================================================
// fireball
// Fires a torpedo from ship
//=============================================================================
void Projectile::fire(Player *player, std::vector<Enemy> vec)
{
	//EnemyListAlive(vec);
	if (fireTimer <= 0.0f)                      // if ready to fire
	{
		if (player->getDirection() == LEFT || player->getDirection() == RIGHT)
			velocity.x = player->getDirection();
		else
			velocity.x = 0;
		if (player->getDirection() == UP || player->getDirection() == DOWN)
			velocity.y = player->getDirection();
		else
			velocity.y = 0;

		D3DXVec2Normalize(&velocity, &velocity);
		velocity = velocity * projectileNS::SPEED;
		
		spriteData.x = player->getCenterX() - spriteData.width / 2;
		spriteData.y = player->getCenterY() - spriteData.height / 2;
		visible = true;                         // make fireball visible
		active = true;                          // enable collisions
		fireTimer = projectileNS::FIRE_DELAY;      // delay firing

		player->setMana(player->getMana() - FIREBALL_COST_MANA);
	}
}

/*
Enemy Projectile::GetClosestEnemy(std::vector<Enemy> vec) {
	for (std::vector<Enemy>::iterator it = vec.begin(); it != vec.end(); it++) {
		if (it == vec.begin()) {
			closestEnemy = *it;
		}
		else {
			if (EnemyListAlive(vec) > 0) { //if number of enemies > 0 this line shd be settled in update with if(ishoming)
				isHoming = true;
				//compare magnitude between it and player
				if (CALC_MAGNITUDE_SQUARED(it->getX(), getX(), it->getY(), getY()) >
					CALC_MAGNITUDE_SQUARED(closestEnemy.getX(), getX(), closestEnemy.getY(), getY())) {
					closestEnemy = *it;
				}
				
			}
		}
	}
	return closestEnemy;
}

int Projectile::EnemyListAlive(std::vector<Enemy> vec) {
	int count = 0;
	for (std::vector<Enemy>::iterator it = vec.begin(); it != vec.end(); it++) {
		//if it is alive, count++ 
		if (it->getHealth() > 0) {
			count++;
		}
	}
	return count;
}
*/
Projectile::~Projectile()
{
}
