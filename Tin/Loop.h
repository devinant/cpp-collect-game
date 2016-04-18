#ifndef LOOP_H
#define LOOP_H

#include "GameObject.h"
#include "World.h"
#include "Controls.h"

class Loop : public GameObject
{
public:
	Loop();
	virtual ~Loop();

	int update();
	void render();

private:
	World* world_;
	Controls input_;
};

#endif