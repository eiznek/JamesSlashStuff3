#pragma once
#include "entity.h"
#include "player.h"

namespace itemNS
{
	const int   WIDTH = 32;             // image width
	const int   HEIGHT = 32;           // image height
	const int   TEXTURE_COLS = 1;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;
}

class Item :
	public Entity
{
public:
	Item();
	~Item();

	void update(float frameTime);
	void PickUp(Player *player);
	void Drop(Entity *entity);

};

