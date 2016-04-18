#ifndef TIMER_H
#define TIMER_H

#include<cmath>
#include "Component.h"

using std::fabs;

class Timer : public Component
{
public:
	enum Formats { TO_MILLISECONDS, TO_SECONDS, TO_FLOAT, TO_FRACTION };

	Timer(float timer, bool startOnInstance = false);
	void start();
	void pause();
	void stop();
	void reset(bool startAgain = false);
	void tick();
	void setTimer(float time);
	void setElapsed(float time);
	
	float getTimer() const;
	float getElapsed() const;
	float getRemainder() const;

	bool isStarted() const;
	bool isPaused() const;
	bool isStopped() const;
	bool isActive() const;

	bool hasElapsed(float time) const;

	template <Timer::Formats T, typename R>
	R format(float value) const;

	// Equivalent to Timer::setTimer()
	Timer& operator=(float value);
	Timer operator+=(float value);
	Timer operator-=(float value);
	
	// Equivalent to Timer::hasElapsed()
	bool operator>(float value);
	bool operator<(float value);
private:
	float timer_;
	float elapsed_;

	bool started_;
	bool paused_;
	bool stopped_;
};


template <Timer::Formats T, typename R>
R Timer::format(float floatValue) const
{
	R translatedValue;

	switch (T)
	{
		// TO_FLOAT is ignored, since its the default value.
		case Timer::TO_MILLISECONDS: translatedValue = static_cast<R>(floatValue * 1.000f); break;
		case Timer::TO_SECONDS:      translatedValue = static_cast<R>(floatValue); break;
		case Timer::TO_FRACTION:     translatedValue = static_cast<R>(floatValue / timer_); break;
	}

	return translatedValue;
}
#endif