#include "PlayerWeapon.h"



PlayerWeapon::PlayerWeapon()
{
	active = false;                                 // torpedo starts inactive
	spriteData.width = PlayerWepNS::WIDTH;     // size of 1 image
	spriteData.height = PlayerWepNS::HEIGHT;
	spriteData.rect.bottom = PlayerWepNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = PlayerWepNS::WIDTH;
	cols = PlayerWepNS::TEXTURE_COLS;
	frameDelay = PlayerWepNS::ANIMATION_DELAY;
	startFrame = PlayerWepNS::START_FRAME;       // first frame of ship animation
	endFrame = PlayerWepNS::END_FRAME;         // last frame of ship animation
	currentFrame = startFrame;
	//radius = PlayerWepNS::COLLISION_RADIUS;  // for circular collision
	visible = false;
	attackTimer = 0.0f;
	//mass = PlayerWepNS::MASS;
	collisionType = entityNS::BOX;

}


PlayerWeapon::~PlayerWeapon()
{
}

void PlayerWeapon::update(float frameTime)
{
	attackTimer -= frameTime;                     // time remaining until fire enabled

	if (visible == false)
		return;

	if (attackTimer < 0)                           // if ready to fire
	{
		visible = false;                        // old torpedo off
		active = false;
	}

	Image::update(frameTime);

	//spriteData.x += frameTime * velocity.x;     // move along X 
	//spriteData.y += frameTime * velocity.y;     // move along Y
	//
	//											// Wrap around screen edge
	//if (spriteData.x > GAME_WIDTH)              // if off right screen edge
	//	spriteData.x = -PlayerWepNS::WIDTH;       // position off left screen edge
	//else if (spriteData.x < -PlayerWepNS::WIDTH)  // else if off left screen edge
	//	spriteData.x = GAME_WIDTH;              // position off right screen edge
	//if (spriteData.y > GAME_HEIGHT)             // if off bottom screen edge
	//	spriteData.y = -PlayerWepNS::HEIGHT;      // position off top screen edge
	//else if (spriteData.y < -PlayerWepNS::HEIGHT) // else if off top screen edge
	//	spriteData.y = GAME_HEIGHT;             // position off bottom screen edge
}


