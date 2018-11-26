#pragma once
#include "entity.h"

class Player: public Entity {

private:
	int direction;
	int HealthPoints;

public:
	Player();
	virtual ~Player();

	void Move(int direction);
	void Attack();
	void update(float frameTime);

};