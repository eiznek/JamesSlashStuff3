#pragma once
#include "entity.h"
#include "player.h"
#include <vector>

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
private:
	int id;
public:
	Item();
	~Item();
	std::vector<Item> ItemList;

	void update(float frameTime);
	//void PickUp(Player *player);
	void Drop(Entity *entity);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void ItemAdd(Item item);
	void setID(int id) { this->id = id; }
	int getID() { return id; }

};

