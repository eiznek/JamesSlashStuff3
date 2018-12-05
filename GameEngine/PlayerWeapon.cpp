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

void PlayerWeapon::update(float frameTime) {

	if (isready == true && attacktimer > 0)
		attacktimer -= frameTime;                     // time remaining until fire enabled

	if (attacktimer <= 0)                           
	{
		isready = false;
		setCurrentFrame(PlayerWepNS::START_FRAME);
		setActive(false);
		setVisible(false);
		attacktimer = PlayerWepNS::ATTACK_DELAY;

	}

	Image::update(frameTime);

}

void PlayerWeapon::attack() {
	
}


