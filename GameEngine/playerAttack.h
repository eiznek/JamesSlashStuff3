#pragma once
#include "entity.h"
class playerAttack :
	public Entity
{
private:


public:
	playerAttack();
	~playerAttack();

	 void damage(int weapon);
};

