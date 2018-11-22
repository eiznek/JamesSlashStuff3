#pragma once
#include <string>

namespace EntityNS
{
	int WIDTH;								//image width
	int HEIGHT;								//image height
	int COLLISION_RADIUS = HEIGHT / 2;		//radius if circle
	int X = GAME_WIDTH / 2 - WIDTH / 2;		//location on screen
	int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

class Entity
{
protected:
	std::string Tag;


public:
	Entity();
	~Entity();
};

