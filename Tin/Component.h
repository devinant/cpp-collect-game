#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <hge.h>

class Component
{
public:
	Component();
	virtual ~Component();

	static HGE* getHge();
	static void registerHge();
	static void unregisterHge();

	virtual void update() {}

private:
	static HGE* hge_;
};

#endif