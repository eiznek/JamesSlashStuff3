#include "PlayerWeapon.h"



PlayerWeapon::PlayerWeapon()
{
}


PlayerWeapon::~PlayerWeapon()
{
}

void PlayerWeapon::damage()
{
	VECTOR2 collisionvector;
	if (this->collidesWith(npc, collisionvector)){
		npc.setX(999);
	}
}

