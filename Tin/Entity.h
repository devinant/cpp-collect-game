#ifndef ENTITY_H
#define ENTITY_H

#include <hgerect.h>
#include <iostream>

#include "Component.h"
#include "Point.h"
#include "Graphics.h"

typedef std::vector<hgeRect> Walls;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	static size_t getNrOfEntities();
	size_t getId() const;

	// Data all entities need
	virtual hgeRect box() const = 0;
	virtual Point& position() = 0;
	virtual Graphics::Renderer* getRenderer();

	void setWalls(Walls* walls);
	Walls* getWalls() const;

	bool isSafeSpawn(float x, float y);

	// Events in the game world
	virtual void event(Entity* e) = 0; // A entity collides with another entity
	// virtual void event(Entity* entity, World* world);
	virtual void event(const hgeRect& rect); // A entity collides with a wall
	
	virtual void update() = 0;
	virtual void render() = 0;

private:
	size_t id;
	static size_t nrOfEntities;

	Walls* walls_;
};
#endif