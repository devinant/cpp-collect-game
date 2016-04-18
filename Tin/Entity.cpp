#include "Entity.h"

size_t Entity::nrOfEntities = 0;

Entity::Entity()
{
	// Increase the entity ID and assign its value to the id.
	Entity::nrOfEntities++;
	id = Entity::nrOfEntities;
}

Entity::~Entity() {}

size_t Entity::getNrOfEntities()
{
	return Entity::nrOfEntities;
}

size_t Entity::getId() const
{
	return id;
}

// Resolves a position
void Entity::event(const hgeRect &w)
{
	position().resolve(1, box(), w);
}

// Entity returntypes
Graphics::Renderer* Entity::getRenderer()
{
	return nullptr;
}

void Entity::setWalls(Walls* walls)
{
	walls_ = walls;
}

Walls* Entity::getWalls() const
{
	return walls_;
}

bool Entity::isSafeSpawn(float x, float y)
{
	bool safe = false;

	for (size_t w = 0; w < walls_->size() && !safe; w++)
	{
		hgeRect wall = walls_->at(w);
		safe = (x < wall.x1 || x >= wall.x2 || y < wall.y1 || y >= wall.y2) ? false : true;
	}

	return safe;
}