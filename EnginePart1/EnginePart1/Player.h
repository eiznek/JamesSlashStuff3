#pragma once

class Player {

private:
	bool Direction_North;
	bool Direction_South;
	bool Direction_East;
	bool Direction_West;

	int HealthPoints;

public:
	Player();
	virtual ~Player();

	void Move();
	void Attack();

};