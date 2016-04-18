#include "Loop.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Helpers
#include "Sound.h"
#include "Controls.h"
#include "Graphics.h"
#include "Animation.h"
#include "Sound.h"
#include "Tileset.h"

// Entities
#include "Player.h"
#include "Item.h"
#include "Coin.h"
#include "Weight.h"
#include "HourGlass.h"
#include "Quadruplicate.h"
#include "Haste.h"

Loop::Loop()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Component::registerHge();
	world_ = new World("music/worldloop.wav", "textures/tiles/tiles.png", "map.txt", "collisions.txt");

	printf("Loop: Registring game engine.\nLoop: Loading game world\n");

	// Spawn entities into the world
	world_->createEntity(new Player(true));
	world_->createEntity(new Player(true));
	world_->createEntity(new Coin());
	world_->createEntity(new Weight());
	world_->createEntity(new HourGlass());
	world_->createEntity(new Haste());
}
Loop::~Loop() 
{
	delete world_;
	Component::unregisterHge();

	printf("Loop: Deleting world\nLoop: Unregistring the game engine.\n");
}
int Loop::update() 
{
	// Update the world and all its components
	world_->update();
	
	// Shuts down the game
	if (input_.down(HGEK_ESCAPE))
		return 1;

	return 0;
}
void Loop::render() 
{
	world_->render();
}
