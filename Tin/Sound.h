#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include "Component.h"

class Sound : public Component
{
public:
	Sound();
	virtual ~Sound();

	void load(const char* fileName);

	void play(size_t effect, int volume = 100, int pan = 0, float pitch = 1.0f, bool loop = false);
	void loop(size_t effect);
	bool isPlaying(size_t effect) const;
	void resume(size_t effect = -1) const;
	void pause(size_t effect = -1) const;
	void stop(size_t effect) const;

	float getLength(size_t effect) const;

	void setPosition(size_t effect, float seconds = -1.0f) const;
	float getPosition(size_t effect) const;

	void setPanning(size_t effect, signed int pan = 0) const;
	void setVolume(size_t effect, size_t vol = 100) const;
	void setPitch(size_t effect, float pitch = 1.0f) const;

	static void pauseAll();
	static void resumeAll();
	static void stopAll();

private:
	std::vector<HEFFECT> sounds_;
	std::vector<HCHANNEL> channels_;
};

#endif