#include "Timer.h"

Timer::Timer(float timer, bool startOnInstance)
: started_(startOnInstance), paused_(false), stopped_(false)
{
	timer_ = timer;
	elapsed_ = 0;
}

void Timer::start()
{
	if (isPaused())
		paused_ = false;

	started_ = true;
}
void Timer::pause()
{
	paused_ = true;
}
void Timer::stop()
{
	stopped_ = true;
}
void Timer::reset(bool start)
{
	started_ = start;
	paused_ = false;
	stopped_ = false;

	elapsed_ = 0;
}
void Timer::tick()
{
	if (isActive())
		elapsed_ += Component::getHge()->Timer_GetDelta();

	if (elapsed_ >= timer_)
	{
		stop();
		elapsed_ = timer_;
	}
	
}
void Timer::setTimer(float time)
{
	timer_ = time;
}
void Timer::setElapsed(float time)
{
	elapsed_ = time;
}
float Timer::getTimer() const
{
	return timer_;
}
float Timer::getElapsed() const
{
	return elapsed_;
}
float Timer::getRemainder() const
{
	float remainder = fabs(elapsed_ - timer_);
	return (remainder >= timer_) ? timer_ : remainder;
}
bool Timer::isStarted() const
{
	return started_;
}
bool Timer::isPaused() const
{
	return paused_;
}
bool Timer::isStopped() const
{
	return stopped_;
}
bool Timer::isActive() const
{
	return !stopped_ && !paused_;
}
bool Timer::hasElapsed(float value) const
{
	return elapsed_ >= value;
}
Timer& Timer::operator=(float value)
{
	timer_ = value;
	
	return *this;
}
Timer Timer::operator+=(float value)
{
	timer_ += value;

	return *this;
}
Timer Timer::operator-=(float value)
{
	timer_ -= value;

	return *this;
}
bool Timer::operator>(float value)
{
	return hasElapsed(value);
}
bool Timer::operator<(float value)
{
	return !hasElapsed(value);
}