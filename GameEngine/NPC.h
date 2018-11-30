#pragma once
#include "entity.h"

namespace NpcNS
{
	const int   WIDTH = 32;                // image width (each frame)
	const int   HEIGHT = 32;               // image height
	const int   X = TEXTURE_SIZE * 10; // location on screen
	const int   Y = TEXTURE_SIZE * 10;

}


class NPC :
	public Entity
{
public:
	NPC();
	~NPC();

	bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void interact();

};

