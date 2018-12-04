#include "Item.h"



Item::Item() : Entity()
{
	active = false;                                
	spriteData.width = itemNS::WIDTH;    
	spriteData.height = itemNS::HEIGHT;
	spriteData.rect.bottom = itemNS::HEIGHT;    
	spriteData.rect.right = itemNS::WIDTH;
	cols = itemNS::TEXTURE_COLS;
	startFrame = itemNS::START_FRAME;      
	endFrame = itemNS::END_FRAME;        
	currentFrame = startFrame;
	visible = false;
	edge.top = 0;             // ROTATED_BOX collision edges
	edge.bottom = itemNS::HEIGHT;
	edge.left = 0;
	edge.right = itemNS:: WIDTH;
	collisionType = entityNS::BOX;
}

bool Item::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Item::ItemAdd(Item item) {
	ItemList.push_back(item);
}

void Item::update(float frameTime) {
	Image::update(frameTime);

}

void Item::Drop(Entity *entity) {
	spriteData.x = entity->getCenterX();
	spriteData.y = entity->getCenterY();
	setActive(true);
	setVisible(true);

}

//void Item::PickUp(Player *player) {
//	setActive(false);
//	setVisible(false);
//
//}

Item::~Item()
{
}
