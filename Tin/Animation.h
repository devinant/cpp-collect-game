#ifndef ANIMATION_H
#define ANIMATION_H

#include "Graphics.h"

class Animation : public Graphics
{
public:
	Animation(const char* texture, size_t frames, size_t rows, float fps = 60.0f);
	virtual ~Animation();

	void play();
	void stop();
	bool isAnimating(size_t i);

private:
	size_t frames_;
	size_t rows_;

	float fps_;
};



#endif