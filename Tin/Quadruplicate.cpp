#include "Quadruplicate.h"


Quadruplicate::Quadruplicate()
	: Item(0.0f, 5.0f, &graphics_, nullptr, &point_),
	graphics_("textures/tin.png")
{
}


Quadruplicate::~Quadruplicate()
{
	for (size_t i = 0; i < SIZE_; i++)
	{
		
	}
}

// Events
void Quadruplicate::event(Entity* e)
{
	if (Item::hasState(Item::WAITING))
	{
		// Use the default player as a clone
		orig_ = static_cast<Player*>(e);

		Item::setState(Item::TAKEN);
	}

}

void Quadruplicate::stateTaken()
{
	for (size_t i = 0; i < SIZE_; i++)
	{
		// Use the renderer objects to set new values.
		*copies_[i].getRenderer() = *orig_->getRenderer();

		copies_[i].getRenderer()->setX(orig_->getRenderer()->getX() + 32.0f * i);
	}
}

void Quadruplicate::render()
{
	if (hasState(Item::SPAWNING) || hasState(Item::WAITING) || hasState(Item::EXPIRED))
		graphics_.render(point_.getX(), point_.getY());


	for (size_t i = 0; i < SIZE_ && hasState(Item::TAKEN); i++)
		copies_[i].render();
	
}