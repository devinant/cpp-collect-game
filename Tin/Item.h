#ifndef ITEM_H
#define ITEM_H

#include <random>
#include <list>
#include<map>

#include "Entity.h"

#include "Graphics.h"
#include "Sound.h"
#include "Point.h"
#include "Physics.h"

#include "Buff.h"
#include "Timer.h"

class Item : public Entity
{
public:
	enum State { COMPUTING, READY, SPAWNING, WAITING, EXPIRED, TAKEN };

	Item(float intervalDuration, float aliveDuration, Graphics* graphics = nullptr, Sound* sound = nullptr, Point* point = nullptr, Physics* physics = nullptr);
	virtual ~Item();

	void setState(Item::State state);
	void setIntervalDuration(float intervalDuration);
	void setAliveDuration(float aliveDuration);

	Item::State getState() const;
	float getIntervalDuration() const;
	float getAliveDuration() const;

	bool hasState(Item::State state) const;

	// Entity
	virtual hgeRect box() const;
	virtual Point& position();

	// States
	virtual void stateReady();  
	virtual void stateSpawning();
	virtual void stateWaiting();
	virtual void stateExpired();
	virtual void stateTaken();  

	// Events
	virtual void event(Entity* e);

	// Probabilities
	bool computeProbability(float probability) const;
	void computeNextSpawn();

	void update();
	virtual void render();

	virtual void stat(std::multimap<const char*, Buff>& stat);

private:
	std::mt19937 range_; // Random number generator
	Item::State state_; // State machine

	float intervalDuration_;
	float aliveDuration_;

	Timer interval_;
	Timer alive_;

	// Pointers to components
	Graphics* graphics_;
	Sound* sound_;
	Physics* physics_;
	Point* point_;
};
#endif