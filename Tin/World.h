#ifndef WORLD_H
#define WORLD_H

#include<fstream>
#include<ostream>

#include "Controls.h"
#include "Tileset.h"
#include "Sound.h"
#include "Entity.h"
#include "Item.h"

class World
{
public:
	World(const char* music, const char* t_set, const char* t_map, const char* t_collisions);
	
	// Collision loading
	void loadWalls(const char* filename);

	// Entities
	void createEntity(Entity* newObject);
	void destroyEntity(size_t id);

	// World updates and rendering
	void update();
	void render();

	virtual ~World();
	
private:
	Controls key;
	Tileset tileset;

	std::vector<hgeRect> walls;

	// Amount of entities this world can hold
	std::vector<Entity*> objects;

	// Sounds in the world
	Sound sound_;

};

#endif