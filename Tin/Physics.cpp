#include "Physics.h"

Physics::Physics(float acceleration, float velocity, float speed, float maxVelocity)
{
	acceleration_ = baseValues_[0] = acceleration;
	velocity_ = baseValues_[1] = velocity;
	speed_ = baseValues_[2] = speed;
	maxVelocity_ = baseValues_[3] = maxVelocity;
}
Physics::~Physics(){}

void Physics::setAcceleration(float acceleration)
{
	acceleration_ = fabs(acceleration);
}
void Physics::decelerate(float factor)
{
	velocity_ *= factor;
}
void Physics::setVelocity(float velocity)
{
	velocity_ = velocity;
}
void Physics::setSpeed(float speed)
{
	speed_ = speed;
}
void Physics::setMaxVelocity(float velocity)
{
	maxVelocity_ = velocity;
}

float Physics::getAcceleration() const
{
	return acceleration_;
}
float Physics::getVelocity() const
{
	return velocity_;
}
float Physics::getSpeed() const 
{
	return speed_;
}
float Physics::getMaxVelocity() const
{
	return maxVelocity_;
}

void Physics::reset()
{
	acceleration_ = baseValues_[0];
	velocity_ = baseValues_[1];
	speed_ = baseValues_[2];
	maxVelocity_ = baseValues_[3];
}
void Physics::update()
{
	// Acceleration
	acceleration_ += acceleration_ * Component::getHge()->Timer_GetDelta();
	velocity_ += acceleration_ * Component::getHge()->Timer_GetDelta();

	// Enforce maxVelocity
	if (maxVelocity_ != 0.0f && acceleration_ > 0.0f && velocity_ >= maxVelocity_)
		velocity_ = maxVelocity_;
}