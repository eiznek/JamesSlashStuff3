#include "NPC.h"

using namespace NpcNS;

NPC::NPC() : Entity()
{
	spriteData.width = WIDTH;           // size of Entity
	spriteData.height = HEIGHT;
	spriteData.x = X;                   // location on screen
	spriteData.y = Y;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
	edge.top = 0;             // ROTATED_BOX collision edges
	edge.bottom = HEIGHT;
	edge.left = 0;
	edge.right = WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = 0.1f;
	startFrame = 0;     // first frame of animation
	endFrame = cols - 1;     // last frame of animation
	currentFrame = startFrame;
	radius = WIDTH / 2.0;
	collisionType = entityNS::BOX;
}

NPC::~NPC()
{
}

bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//NpcList.push_back(*this);
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void NPC::AddNPC(NPC npc) {
	NpcList.push_back(npc);
}

void NPC::update(float frameTime) {
	Entity::update(frameTime);

}

void NPC::interact() {

}


