#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"

class Physics : public Component
{
private:
	float acceleration_;
	float velocity_;
	float speed_;
	float maxVelocity_;

	// Original values, we can use reset on them
	float baseValues_[4];
public:
	Physics(float acceleration = 1.0f, float velocity = 1.0f, float speed = 1.0f, float maxVelocity = 0.0f);
	~Physics();

	void setAcceleration(float acceleration);
	void setVelocity(float velocity);
	void setSpeed(float speed);
	void setMaxVelocity(float velocity);
	void decelerate(float factor = -1.0f);
	
	float getAcceleration() const;
	float getVelocity() const;
	float getSpeed() const;
	float getMaxVelocity() const;

	void reset();
	void update();

};

#endif