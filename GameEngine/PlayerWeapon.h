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
	const float ATTACK_DELAY = 1.0f;
	const int   TEXTURE_COLS = 4;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;
	const float ANIMATION_DELAY = 0.1f; // time between frames
}

class PlayerWeapon :
	public Entity
{
private:
	NPC npc;
	bool isready;
	float attacktimer;

public:
	PlayerWeapon();
	~PlayerWeapon();

	void update(float frameTime);
	float getTimer() { return attacktimer; }
	bool getReady() { return isready; }
	void setReady(bool isr) { isready = isr; }
	void attack();
	//void damage(Player *player);

};

