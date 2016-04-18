#include "Sound.h"

Sound::Sound()
{
	sounds_.reserve(10);
	channels_.reserve(10);
}
Sound::~Sound()
{
	for (size_t i = 0; i < sounds_.size(); i++)
		Component::getHge()->Effect_Free(sounds_[i]);

	sounds_.clear();
	channels_.clear();
}

void Sound::load(const char* fileName)
{
	// Load the sounds_
	sounds_.push_back(Component::getHge()->Effect_Load(fileName));

	// If the sounds_ returns 0, it was not loaded.
	if (sounds_[sounds_.size() - 1] == 0)
		throw std::exception("Effect could not be loaded");
	else
		channels_.push_back(0);
}
void Sound::play(size_t effect, int volume, int pan, float pitch, bool loop)
{
	channels_[effect] = Component::getHge()->Effect_PlayEx(sounds_[effect], volume, pan, pitch, loop);
}
void Sound::loop(size_t effect)
{
	if (effect <= sounds_.size())
		channels_[effect] = Component::getHge()->Effect_PlayEx(sounds_[effect], 100, 0, 1.0, true);
}
bool Sound::isPlaying(size_t effect) const
{
	bool playing = false;

	if (effect <= sounds_.size())
		playing = Component::getHge()->Channel_IsPlaying(channels_[effect]);

	return playing;
}
void Sound::resume(size_t effect) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_Resume(channels_[effect]);
}
void Sound::pause(size_t effect) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_Pause(channels_[effect]);
}
void Sound::stop(size_t effect) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_Stop(channels_[effect]);
}
float Sound::getLength(size_t effect) const
{
	return (effect <= sounds_.size()) ? Component::getHge()->Channel_GetLength(channels_[effect]) : 0;
}
void Sound::setPosition(size_t effect, float seconds) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_SetPos(channels_[effect], seconds);
}
float Sound::getPosition(size_t effect) const
{
	float pos = -1.0f;

	if (effect <= sounds_.size())
		pos = Component::getHge()->Channel_GetPos(channels_[effect]);

	return pos;
}
void Sound::setPanning(size_t effect, signed int pan) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_SetPanning(channels_[effect], pan);
}
void Sound::setVolume(size_t effect, size_t vol) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_SetVolume(channels_[effect], vol);
}
void Sound::setPitch(size_t effect, float pitch) const
{
	if (effect <= sounds_.size())
		Component::getHge()->Channel_SetPitch(channels_[effect], pitch);
}

/* 
 * Pauses ALL sounds_s
 */
void Sound::pauseAll()
{
	Component::getHge()->Channel_PauseAll();
}

/*
* Resumes ALL sounds_s
*/
void Sound::resumeAll()
{
	Component::getHge()->Channel_ResumeAll();
}

/*
* Stops ALL sounds_s
*/
void Sound::stopAll()
{
	Component::getHge()->Channel_StopAll();
}