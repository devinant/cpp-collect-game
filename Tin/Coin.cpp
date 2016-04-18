#include "Coin.h"


Coin::Coin()
	: Item(0.0f, 5.0f, &graphics_, &sound_, &point_),
	  graphics_("textures/coin/spinning.png", 6, 1, 16.0f)
{
	sound_.load("fx/pickup.wav");
	sound_.load("fx/spawn_coin.wav");
}
Coin::~Coin() {}

// Item collided with another entity
void Coin::event(Entity* e)
{
	// Can only be picked-up when state is "waiting"
	if (Item::hasState(Item::WAITING))
	{
		sound_.play(0, 80);
		
		// Increase player score
		Player* player = static_cast<Player*>(e);

		player->setScore(player->getScore() + 1);
		
		Item::setState(Item::TAKEN);
	}
}
void Coin::stateReady()
{	
	sound_.play(1, 80);
	Item::stateReady();
}
void Coin::stateWaiting()
{
	graphics_.play(); // Play the animation while we're waiting.
}

void Coin::stat(std::multimap<const char*, Buff>& stat)
{
	// Give the player a little boost when they collect a coin
	if (Item::hasState(Item::WAITING))
		stat.insert(std::pair<const char*, Buff>("Haste", Buff(2.0f, Buff::MULTIPLICATION, Buff::VELOCITY, 1.02f)));
}