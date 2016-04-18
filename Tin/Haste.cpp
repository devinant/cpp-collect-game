#include "Haste.h"


Haste::Haste() 
	: Item(15.0f, 5.0f, &graphics_, nullptr, &point_), 
	  graphics_("textures/haste.png") 
{}

Haste::~Haste() {}

void Haste::stateWaiting()
{
	// Rotate the item continuosly
	graphics_.setRotation(0.05f, true);
}
void Haste::render()
{
	if (hasState(Item::SPAWNING) || hasState(Item::WAITING) || hasState(Item::EXPIRED))
		graphics_.render(point_.getX(), point_.getY());
}
void Haste::stat(std::multimap<const char*, Buff>& stat)
{
	if (Item::hasState(Item::WAITING))
	{
		// There's a 50-50 chance this item is good/bad
		float velocity = Item::computeProbability(0.50f) ? 1.5f : 0.5f;

		stat.insert(std::pair<const char*, Buff>("Haste", Buff(5.0f, Buff::MULTIPLICATION, Buff::VELOCITY, velocity)));
	}
		
}