#pragma once
#include "entity.h"
#include "NPC.h" //change this to enemy

namespace PlayerWepNS
{
	const int   WIDTH = 32;                // image width (each frame)
	const int   HEIGHT = 32;               // image height
	const int   X = TEXTURE_SIZE * 10; // location on screen
	const int   Y = TEXTURE_SIZE * 10;

}

class PlayerWeapon :
	public Entity
{
private:
	NPC npc;

public:
	PlayerWeapon();
	~PlayerWeapon();

	void damage();

};

