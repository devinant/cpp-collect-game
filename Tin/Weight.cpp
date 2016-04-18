#include "Weight.h"


Weight::Weight()
	: Item(20.0f, 7.0f, &graphics_, &sound_, &point_, &physics_),
	  graphics_("textures/weight.png"),
	  physics_(9.8f, 1.0f, 12.0f)
{
	sound_.load("fx/weight_drop3.wav");
	sound_.load("fx/pop.wav");
	sound_.load("fx/grow.wav");
}
Weight::~Weight() {}
void Weight::stateReady()
{
	// Test if the final position is good:
	do
	{
		// Accuire a random x value and set Y to out of bounds
		point_.setXY(point_.getRX(), -graphics_.getHeight());
		spawnY_ = point_.getRY();
	} while (Entity::isSafeSpawn(point_.getX(), spawnY_));

	sound_.play(1, 80);
	physics_.reset();
	graphics_.setScale(1.0f);

	Item::setState(Item::SPAWNING);
}
void Weight::stateSpawning()
{
	// Let the item fall
	point_.moveY(physics_.getVelocity());

	if (point_.getY() >= spawnY_)
	{
		point_.setY(spawnY_);
		physics_.decelerate(-0.2f);
		sound_.play(0, 80); // Thud

		if ((int)physics_.getVelocity() == 0)
			Item::setState(Item::WAITING); // Item has fallen. Reset its timers and enable it
	}
}
void Weight::stateTaken()
{
	sound_.play(2, 80);
	Item::stateTaken();
}
void Weight::stat(std::multimap<const char*, Buff>& stat)
{
	// Apply these effects only if the item is waiting for collisions
	if (Item::hasState(Item::WAITING))
	{
		float duration = 5.0f;

		stat.insert(std::pair<const char*, Buff>("Giant", Buff(duration, Buff::MULTIPLICATION, Buff::SCALE,    1.5f)));
		stat.insert(std::pair<const char*, Buff>("Haste", Buff(duration, Buff::MULTIPLICATION, Buff::VELOCITY, 0.85f)));
	}
}