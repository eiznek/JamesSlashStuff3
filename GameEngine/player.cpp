#include "player.h"

Player::Player() : Entity() {

}

Player::~Player() {

}

void Player::update(float frameTime) {
	Entity:update(frameTime);
}

void Player::Move(int dir) {
	direction = dir;
	switch (dir)
	{
		case UP:
			
		case DOWN:

		case LEFT:

		case RIGHT:

		default:
			break;

	}
	/*
	if(press up)[
	direction_north = true;
	all others = false;
	}
	repeat for left, right, down

	*/
}

void Player::Attack() {
	/*
	
	*/
}