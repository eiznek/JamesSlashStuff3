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
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Projectile::update(float frameTime)
{
	fireTimer -= frameTime;                     // time remaining until fire enabled

	if (visible == false)
		return;

	if (fireTimer < 0)                           // if ready to fire
	{
		visible = false;                        // old torpedo off
		active = false;
	}

	Image::update(frameTime);

	spriteData.x += frameTime * velocity.x;     // move along X 
	spriteData.y += frameTime * velocity.y;     // move along Y

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
// fire
// Fires a torpedo from ship
//=============================================================================
void Projectile::fire(Player *player)
{
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

Projectile::~Projectile()
{
}
