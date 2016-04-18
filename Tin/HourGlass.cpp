#include "HourGlass.h"


HourGlass::HourGlass()
	: Item(10.0f, 5.0f, &graphics_, &sound_, &point_), // 20.0f, 5.0f
	  graphics_("textures/hourglass.png")
{
	sound_.load("fx/good.wav");
	sound_.load("fx/bad.wav"); 
	sound_.load("fx/spawn_hourglass.wav");
}
HourGlass::~HourGlass() {}

void HourGlass::event(Entity* e)
{
	if (Item::hasState(Item::WAITING))
	{
		Timer* time = static_cast<Player*>(e)->getTimer();

		// There is a 50-50 chance that this item will decrease time or increase time.
		if (rand() % 2)
		{
			time->setElapsed(time->getElapsed() + 5);
			sound_.play(0, 80); // Lost 5 seconds
		} else {
			time->setElapsed(time->getElapsed() + 10);
			sound_.play(1, 80); // Got 10 seconds.
		}

		Item::setState(Item::TAKEN);
	}
}
void HourGlass::stateReady()
{
	sound_.play(2, 80);
	Item::stateReady();
}