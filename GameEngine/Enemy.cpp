#include "Enemy.h";
using namespace EnemyNS;

Enemy::Enemy() : Entity() {
	spriteData.width = WIDTH;           // size of EntityPlayer
	spriteData.height = HEIGHT;
	spriteData.x = X;                   // location on screen
	spriteData.y = Y;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
	edge.top = 0;             // ROTATED_BOX collision edges
	edge.bottom = 32;
	edge.left = 0;
	edge.right = 32;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = 0.3f;
	startFrame = 0;     // first frame of animation
	endFrame = cols - 1;     // last frame of animation
	currentFrame = startFrame;
	radius = WIDTH / 2.0;
	collisionType = entityNS::BOX;
	QueryPerformanceCounter(&lastAttack);
	QueryPerformanceFrequency(&tmrFreq);
	yOffset = 0;
	xOffset = 0;
	xMoving = 0;
	yMoving = 0;
	movement = 0;
	health = 100;
}
Enemy::~Enemy() {
}

//Initialize 
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//Update
void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
	//write vector code in here

	/*
	//get vector in direction of player
	int dirx = playerX - enemyX;
	int diry = playerX - enemyX;

	//normalize vector
	hyp*hyp =

	//if player up
	animframe = 0;
	//if player down
	animframe = 26;
	//if player left
	animframe = 13;
	//if player right
	animframe = 39;

	*/
}

//X and Y coordinates
int Enemy::getEnemyX() { return spriteData.x; }
int Enemy::getEnemyY() { return spriteData.y; }

//attack player
void Enemy::attackPlayer(Player& thePlayer, int level) {
	int temp = 1 + level;
	thePlayer.setHealth(thePlayer.getHealth() - temp);
}
