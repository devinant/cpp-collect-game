#ifndef HOURGLASS_H
#define HOURGLASS_H

#include "Item.h"
#include "Player.h"

class HourGlass : public Item
{
public:
	HourGlass();
	virtual ~HourGlass();

private:
	Graphics graphics_;
	Sound sound_;
	Point point_;

	// Events
	void event(Entity* e);

	// States
	void stateReady();
};
#endif