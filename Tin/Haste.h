#ifndef HASTE_H
#define HASTE_H

#include "Item.h"


class Haste :
	public Item
{
public:
	Haste();
	virtual ~Haste();

	void stat(std::multimap<const char*, Buff>& stat);
private:
	Point point_;
	Graphics graphics_;

	// Events
	// void event(Entity* e);

	// States
	void stateWaiting();

	// Render & update
	void render();
};
#endif