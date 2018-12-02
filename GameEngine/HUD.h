#ifndef _HUD_          // Prevent multiple definitions if this 
#define _HUD_         // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include "image.h"

namespace hudNS
{
	const int   IMAGE_SIZE = 32;        // each texture size
	const int   TEXTURE_COLS = 32;       // texture columns
	const int   BAR_FRAME = 31;         // the frame number of the bar
}

class HealthBar : public Image
{
public:
	bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
		float scale, COLOR_ARGB color);
	void set(float percentOn);
	// Override update so setRect() is not called.
	virtual void update(float frameTime) {}
};

#endif
