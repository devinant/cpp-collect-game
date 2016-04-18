#include "World.h"

//
// Constructs a world based on a few files.
//
// music: A loopable .mp3
// t_set: .png file that in a base with power of two (64x64, 32x32, etc.)
// t_map: .txt file that describes the map
// t_collisions: .txt file that describes map collisions
//
World::World(const char* music, const char* t_set, const char* t_map, const char* t_collisions)
: tileset(t_set)
{
	//
	// BEWARE!
	// Who is responsible for tick tocks?
	// sound_.load("fx/ticktock.wav");
	sound_.load(music);

	// Play the world music
	sound_.loop(0);
	sound_.setVolume(0, 50);

	// Load walls
	loadWalls(t_collisions);

	// Load tileset
	tileset.load(t_map);
}

World::~World()
{
	printf("Unloading %d entites...\n", objects.size());
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
}
void World::loadWalls(const char* fileName)
{
	// Empty the walls vector before we load anything
	walls.clear();

	std::ifstream file(fileName);

	if (file.is_open())
	{
		float x1;
		float x2;
		float y1;
		float y2;

		while (file >> x1 >> y1 >> x2 >> y2)
			walls.push_back(hgeRect(x1, y1, x2, y2));

		file.close();
		
		// Surrounding walls (x1, y1, x2, y2)
		float x = static_cast<float>(Component::getHge()->System_GetState(HGE_SCREENWIDTH));
		float y = static_cast<float>(Component::getHge()->System_GetState(HGE_SCREENHEIGHT));
		float m = 10.0f; // margin

		walls.push_back(hgeRect(0, 0, x, m));     // top wall
		walls.push_back(hgeRect(0, y - m, x, y)); // bottom wall
		walls.push_back(hgeRect(0, 0, m, y));     // left wall
		walls.push_back(hgeRect(x - m, 0, x, y)); // right wall
	}
}
void World::createEntity(Entity* newObject)
{
	// Let this entity know about walls.
	newObject->setWalls(&walls);

	// Add it to the list
	objects.push_back(newObject);
}
void World::destroyEntity(size_t id)
{
	if (id >= 0 && id <= objects.size())
	{
		delete objects[id];
		objects.erase(objects.begin() + id);
	}
		
}
void World::update()
{
	std::vector<Entity*>::iterator it = objects.begin();

	for (size_t i = 0; i < objects.size(); i++)
	{
		// Item collisions
		for (size_t j = i; j < objects.size() && (dynamic_cast<Item*>(objects[i]) == nullptr); j++)
			if (i != j && objects[i]->box().Intersect(&objects[j]->box()))
				objects[i]->event(objects[j]);
	
		// Wall collisions
		for (size_t w = 0; w < walls.size(); w++)
			if (objects[i]->box().Intersect(&walls[w]))
				objects[i]->event(walls[w]);
	
		// Update all entities
		objects[i]->update();
	}

	if (key.press(HGEK_Z))
		loadWalls("collisions.txt");
}
void World::render()
{
	// Render tileset
	tileset.render();

	// Renders all game objects (entities)
	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->render();

	// Render boxes for walls
	// for (size_t w = 0; w < walls.size(); w++)
	// {
	// 	Component::getHge()->Gfx_RenderLine(walls[w].x1, walls[w].y1, walls[w].x2, walls[w].y1);
	// 	Component::getHge()->Gfx_RenderLine(walls[w].x2, walls[w].y1, walls[w].x2, walls[w].y2);
	// 	Component::getHge()->Gfx_RenderLine(walls[w].x2, walls[w].y2, walls[w].x1, walls[w].y2);
	// 	Component::getHge()->Gfx_RenderLine(walls[w].x1, walls[w].y2, walls[w].x1, walls[w].y1);
	// }
}