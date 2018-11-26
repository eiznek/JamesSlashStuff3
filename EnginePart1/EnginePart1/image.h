#ifndef _IMAGE_H                // Prevent multiple definitions if this 
#define _IMAGE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "textureManager.h"
#include "constants.h"

class image
{
protected:
	Graphics *graphics;				//pointer to graphics
	TextureManager *textureManager; //pointer to texturemanager

public:
	image();
	~image();
};

#endif