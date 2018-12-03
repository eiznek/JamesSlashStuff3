// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// dashboard.cpp v1.0

#include "HUD.h"

bool HealthBar::initialize(Graphics *graphics, TextureManager *textureM, int left,
	int top, float scale, COLOR_ARGB color)
{
	try {
		Image::initialize(graphics, hudNS::IMAGE_SIZE, hudNS::IMAGE_SIZE,
			hudNS::TEXTURE_COLS, textureM);

		setCurrentFrame(hudNS::BAR_FRAME);
		spriteData.x = (float)left;
		spriteData.y = (float)top;
		spriteData.scale = scale;
		spriteData.rect.bottom = hudNS::IMAGE_SIZE / spriteData.scale;
		colorFilter = color;
	}
	catch (...)
	{
		return false;
	}
	//return okay
	return true;
}

//=============================================================================
// set the Bar size
//=============================================================================
void HealthBar::set(float p)
{
	if (p < 0)
		p = 0;
	else if (p > 100)
		p = 100;
	spriteData.rect.right = spriteData.rect.left + (LONG)(spriteData.width*p / 100);
}
