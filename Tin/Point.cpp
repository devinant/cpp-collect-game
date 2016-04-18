#include "Point.h"


Point::Point(float x, float y)
{
	x_ = x == 0 ? getRX() : x;
	y_ = y == 0 ? getRY() : y;
}
Point::~Point() {}

float Point::rand(float max) const
{
	// http://stackoverflow.com/a/13445752/2152149
	std::mt19937 range;
	range.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(0, static_cast<unsigned long>(max));
	
	// Return fully rounded floats, else we get issues with interpolation.
	return static_cast<float>(distribution(range));
}

void Point::setX(float x)
{
	x_ = x;
}
void Point::setY(float y)
{
	y_ = y;
}
void Point::setXY(float x, float y)
{
	this->setX(x);
	this->setY(y);
}
void Point::reset()
{
	x_ = 0.0f;
	y_ = 0.0f;
}

void Point::moveX(float x)
{
	x_ += x;
}
void Point::moveY(float y)
{
	y_ += y;
}

void Point::resolveX(float x, const hgeRect &a, const hgeRect& b)
{
	float directionX  = a.x1 - b.x1;
	float directionY  = a.y1 - b.y1;
	float directionX2 = a.x2 - b.x2; 
	float directionY2 = a.y2 - b.y2;

	if (directionX > 0 && directionY > 0 && directionY2 < 0) // right
		x_ += x;
		
	if (directionX < 0 && directionY > 0) // left
		x_ -= x;	
}
void Point::resolveY(float y, const hgeRect &a, const hgeRect& b)
{
	float directionX  = a.x1 - b.x1;
	float directionY  = a.y1 - b.y1;
	float directionY2 = a.y2 - b.y2;
	float directionX2 = a.x2 - b.x2;

	if (directionY > 0 && directionX > 0 && directionY2 > 0) // bottom
		y_ += y;
	
	if (directionY < 0 && directionX > 0) // top
		y_ -= y;
}
void Point::resolve(float velocity, const hgeRect& a, const hgeRect& b)
{
	resolveY(velocity, a, b);
	resolveX(velocity, a, b);
}
bool Point::isResolvable(const hgeRect& a, const hgeRect& b) const
{
	return (a.x1 < b.x2 && a.x2 > b.x1 &&
			a.y1 < b.y2 && a.y2 > b.y1);
}

float Point::getRX() const
{
	return rand(static_cast<float>(Component::getHge()->System_GetState(HGE_SCREENWIDTH)));
}
float Point::getRY() const 
{ 
	return rand(static_cast<float>(Component::getHge()->System_GetState(HGE_SCREENHEIGHT)));
}
float Point::getX() const
{
	return x_;
}
float Point::getY() const
{
	return y_;
}