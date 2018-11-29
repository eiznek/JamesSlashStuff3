#include "Projectile.h"



Projectile::Projectile(VECTOR2 dir, int spd)
{
	direction = dir;
	speed = spd;

	setVelocity(direction * speed);
	
}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Projectile::update(float frameTime) {

}


Projectile::~Projectile()
{
}
