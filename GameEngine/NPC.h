#pragma once
#include "entity.h"
#include "constants.h"
#include <vector>

namespace NpcNS
{
	const int   WIDTH = 32;                // image width (each frame)
	const int   HEIGHT = 32;               // image height
	const int   X = GAME_WIDTH * 3/4; // location on screen
	const int   Y = GAME_HEIGHT * 3/4;

}


class NPC :
	public Entity
{
public:
	NPC();
	~NPC();

	std::vector<NPC> NpcList;
	bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void interact();
	void AddNPC(NPC npc);

};

