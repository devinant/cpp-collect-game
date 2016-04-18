#ifndef QUADRUPLICATE
#define QUADRUPLICATE

#include "Item.h"
#include "Player.h"

class Quadruplicate : public Item
{
public:
	Quadruplicate();
	virtual ~Quadruplicate();

private:
	static const size_t SIZE_ = 3;

	Point point_;
	Graphics graphics_;
	Player* orig_;
	Player copies_[SIZE_];

	

	// Events
	void event(Entity* e);

	// States
	void stateTaken();
	
	// Render & update
	void render();
};
#endif