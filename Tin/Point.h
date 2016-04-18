#ifndef POINT_H
#define POINT_H

#include <random>
#include <cmath>
#include "hgerect.h"
#include "Component.h"

class Point : public Component
{
public:
	Point(float x = 0, float y = 0);
	virtual ~Point();

	// Positioning
	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);
	void reset();

	// Movement
	void moveX(float x);
	void moveY(float y);

	// Point resolvement
	void resolveX(float x, const hgeRect& a, const hgeRect& b);
	void resolveY(float y, const hgeRect& a, const hgeRect& b);
	void resolve(float velocity, const hgeRect& a, const hgeRect& b);
	bool isResolvable(const hgeRect& a, const hgeRect& b) const;

	float getX() const;
	float getY() const;
	float getRX() const;
	float getRY() const;

private:
	std::mt19937 range_;
	float x_;
	float y_;

	float rand(float max) const;
};

#endif