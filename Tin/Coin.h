#ifndef COIN_H
#define COIN_H

#include "Item.h"
#include "Animation.h"
#include "Player.h"

class Coin : public Item
{
public:
	Coin();
	virtual ~Coin();

	void stat(std::multimap<const char*, Buff>& stat);

private:
	Animation graphics_; 
	Point point_;
	Sound sound_;

	// Events
	void event(Entity* e);

	// States
	void stateReady();
	void stateWaiting();
};
#endif