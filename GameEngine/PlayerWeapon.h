#pragma once
#include "entity.h"
#include "NPC.h" //change this to enemy
#include "player.h"

namespace PlayerWepNS
{
	const int   WIDTH = 32;                // image width (each frame)
	const int   HEIGHT = 32;               // image height
	const int   X = TEXTURE_SIZE * 10; // location on screen
	const int   Y = TEXTURE_SIZE * 10;
	const float ATTACK_DELAY = 2.0f;
	const int   TEXTURE_COLS = 4;
	const int   START_FRAME = 0;
	const int   END_FRAME = 3;
	const float ANIMATION_DELAY = 0.1f; // time between frames
}

class PlayerWeapon :
	public Entity
{
private:
	NPC npc;
	float attackTimer;

public:
	PlayerWeapon();
	~PlayerWeapon();

	void update(float frameTime);
	//void damage(Player *player);

};

