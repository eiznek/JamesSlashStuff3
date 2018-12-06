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
	velocity.x = 1;
	velocity.y = 1;
	frameDelay = 0.3f;
	startFrame = 26;     // first frame of animation
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

	spriteData.x += frameTime * velocity.x;     // move along X 
	spriteData.y += frameTime * velocity.y;		// move along Y
	
	if (spriteData.x > GAME_WIDTH - EnemyNS::WIDTH)              // if off right screen edge
	{
		spriteData.x = GAME_WIDTH - EnemyNS::WIDTH;
		velocity.x = -velocity.x;
	}
	else if (spriteData.x < 0)     // else if off left screen edge
	{
		spriteData.x = 0;
		velocity.x = -velocity.x;
	}
	else if (spriteData.y > GAME_HEIGHT - EnemyNS::HEIGHT)             // if off bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - EnemyNS::HEIGHT;
		velocity.x = -velocity.x;
	}
    else if (spriteData.y < 0)    // else if off top screen edge
	{
        spriteData.y = 0;             // position off bottom screen edge
		velocity.y = -velocity.y;
	}
	//write vector code in here

	//chasing
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

	//tracking to shoot player
	if (isFollow) {
	spriteData.angle = (float)atan2((EnemyY-spriteData.y), (EnemyX - spriteData.x));
	}

	else {
			spriteData.angle += angleRate * frameTime;
	}

	*/
}

void Enemy::chase(float XPos, float YPos)
{
	velocity.x = XPos;		//directional points - vectors
	velocity.y = YPos;		
	/*
	float xDistance = player.getX() - enemy.getX();
	float yDistance = player.getY() - enemy.getY();
	float hypSqr = (xDistance * xDistance) + (yDistance * yDistance);
	hypSqr = hypSqr * hypSqr;

	if (hypSqr < GAME_WIDTH) {

			YPos += frameTime * ENEMY_SPEED * (yDistance / hypSqr);
			XPos += frameTime * ENEMY_SPEED * (xDistance / hypSqr);
	}*/
}
