#include "Item.h"


Item::Item(float intervalDuration, float aliveDuration, Graphics* graphics, Sound* sound, Point* point, Physics* physics)
	: interval_(intervalDuration), alive_(aliveDuration)
{
	intervalDuration_ = intervalDuration;
	aliveDuration_ = aliveDuration;

	// Bind the specific components
	graphics_ = graphics;
	sound_ = sound;
	point_ = point;
	physics_ = physics;

	computeNextSpawn();
}
Item::~Item() {}

void Item::setState(Item::State state)
{
	state_ = state;
}
void Item::setIntervalDuration(float intervalDuration)
{
	intervalDuration_ = intervalDuration;
}
void Item::setAliveDuration(float aliveDuration)
{
	aliveDuration_ = aliveDuration;
}

Item::State Item::getState() const
{
	return state_;
}
float Item::getIntervalDuration() const
{
	return intervalDuration_;
}
float Item::getAliveDuration() const
{
	return aliveDuration_;
}
bool Item::hasState(Item::State state) const
{
	return (this->state_ == state);
}

//
// Default behavior of different states
//
void Item::stateReady()
{
	if (interval_.isStopped())
	{
		// Reset graphics
		graphics_->setScale(1.0f);

		do
		{
			point_->setXY(point_->getRX(), point_->getRY());
		} while (Entity::isSafeSpawn(point_->getX(), point_->getY()));

		state_ = Item::SPAWNING;
	}
}
void Item::stateSpawning()
{
	// The item has finished spawning (for example, a animation is "done"), set state to "waiting"
	state_ = Item::WAITING;
}
void Item::stateWaiting()
{
}
void Item::stateExpired()
{
	graphics_->setScale(-0.1f, true);

	if (graphics_->getHScale() <= 0.0f)
		computeNextSpawn();
}
void Item::stateTaken()
{
	// The item has been taken, it was picked up by a player, requeue it.
	computeNextSpawn();
}

//
// Event
// When a player interacts with an item (collides). They change the state
// of the item. This is the default behavior
// 
void Item::event(Entity* e)
{
	if (state_ == Item::WAITING)
		state_ = Item::TAKEN;
}
hgeRect Item::box() const
{
	return graphics_->getBoundingBox();
}
Point& Item::position()
{
	return *point_;
}

bool Item::computeProbability(float probability) const
{
	return rand() % 100 < (probability * 100);
}
void Item::computeNextSpawn()
{
	// Seed a range
	range_.seed(std::random_device()());
	
	// Compute a new value for the interval timer,
	std::uniform_int_distribution<std::mt19937::result_type> distribution(0, static_cast<unsigned long>(intervalDuration_));

	// Reset timers
	interval_.reset();
	alive_.reset();
	interval_ = static_cast<float>(distribution(range_)); // Apply the computed time;

	state_ = Item::COMPUTING;
}
void Item::update()
{
	switch (state_)
	{
		case Item::COMPUTING: 
		{
			// Update the main timer
			if (!interval_.isStopped())
				interval_.tick();
			else
				state_ = Item::READY;
			break;
		} 

		case Item::READY:
			this->stateReady();
			break;

		case Item::SPAWNING:
		{
			if (physics_) // The physics engine is loaded, update.
				physics_->update();

			this->stateSpawning();
			break;
		}

		case Item::WAITING:
		{
			this->stateWaiting();
			alive_.tick(); // Item is live, tick the timer.

			if (alive_.isStopped())
				state_ = Item::EXPIRED;
			break;
		}
		
		case Item::EXPIRED:
			this->stateExpired();
			break;

		case Item::TAKEN:
			this->stateTaken();
			break;
	}
}
void Item::render()
{
	if (state_ == Item::SPAWNING || state_ == Item::WAITING || state_ == Item::EXPIRED)
		graphics_->render(point_->getX(), point_->getY());
}

//
// Default behavior of stat changes.
//
void Item::stat(std::multimap<const char*, Buff>& stat)
{}