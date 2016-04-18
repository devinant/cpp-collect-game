#include "Animation.h"
#include <fstream>

Animation::Animation(const char* texture, size_t frames, size_t rows, float fps)
: Graphics(texture, false, Graphics::ANIMATION)
{
	// Animations have frames. Let's add those.
	frames_ = frames;
	rows_ = rows;
	fps_ = fps;

	// We need to update the width and height
	setWidth(getWidth() / frames_);
	setHeight(getHeight() / rows_);

	// Add the frames to each row
	for (size_t i = 0; i < rows; i++)
		load(new hgeAnimation(getTexture(), frames_, fps_, 0.0f, getHeight() * i, getWidth(), getHeight()));

	setCenter(getWidth() * 0.5f, getHeight() * 0.5f);
}
Animation::~Animation() {}

void Animation::play()
{
	for (size_t i = 0; i < assets_.size(); i++)
		if (!isAnimating(i))
			static_cast<hgeAnimation*>(assets_[i])->Play();
}
void Animation::stop()
{
	for (size_t i = 0; i < assets_.size(); i++)
		if (isAnimating(i))
			static_cast<hgeAnimation*>(assets_[i])->Stop();
}
bool Animation::isAnimating(size_t i)
{
	return static_cast<hgeAnimation*>(assets_[i])->IsPlaying();
}