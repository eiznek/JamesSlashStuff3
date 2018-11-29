#pragma once
#define VECTOR2 D3DXVECTOR2

#include <d3dx9math.h>
#include "entity.h"
#include "constants.h"

class Projectile : public Entity
{
private:
	VECTOR2 direction;
	int speed;

public:
	Projectile(VECTOR2 direction, int speed);
	~Projectile();

	bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);

};

