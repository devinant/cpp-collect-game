#ifndef WEIGHT_H
#define WEIGHT_H

#include <vector>
#include <cmath>
#include "Item.h"

class Weight : public Item
{
public:
	Weight();
	virtual ~Weight();

	// Weight applies stuff to hero
	void stat(std::multimap<const char*, Buff>& stat);

private:
	Graphics graphics_;
	Sound sound_; 
	Point point_; 
	Physics physics_;

	float spawnY_; // End position for the "fall"

	void stateReady();
	void stateSpawning();
	void stateTaken();
};
#endif