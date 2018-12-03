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
	attacktimer = PlayerWepNS::ATTACK_DELAY;
	//mass = PlayerWepNS::MASS;
	collisionType = entityNS::BOX;
	isready = true;
}


PlayerWeapon::~PlayerWeapon()
{
}

void PlayerWeapon::update(float frameTime)
{
	if (isready == false) {
		attacktimer -= frameTime;                     // time remaining until fire enabled

		if (attacktimer <= 0)                           // if ready to fire
		{
			setReady(true);
			visible = false;                        // old torpedo off
			active = false;
		}

<<<<<<< HEAD
=======
	if (attackTimer <= 0)                           // if ready to fire
	{
		visible = false;                        // old torpedo off
		active = false;
>>>>>>> bfa2c45512260250461d23e9393f6a7f0af7f7b9
	}
	Image::update(frameTime);

}
