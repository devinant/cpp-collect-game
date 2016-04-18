#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <list>
#include <map>

#include <hgefont.h>

#include "Entity.h"
#include "Item.h"
#include "Controls.h"
#include "Animation.h"
#include "Physics.h"
#include "Buff.h"

typedef std::pair<const char*, Buff> PDescriptor;

class Player : public Entity 
{
public:
	enum Direction { DOWN, LEFT, RIGHT, UP };

	Player(bool controlable = false);
	virtual ~Player();

	bool isControlable() const;

	// Scoring
	void setScore(size_t score);
	size_t getScore() const;

	Timer* getTimer();

	// Enable controls for this entity
	void handleControls();
	void handleBuffs();

	hgeRect box() const;
	Point& position();
	Graphics::Renderer* getRenderer();

	// Events
	void event(Entity* e);
	void event(const hgeRect &w);

	void update();
	void render();

private:
	// Stats
	std::multimap<const char*, Buff> stats_;
	std::pair<float, float> base_[Buff::NR_OF_JOBS];

	// Components
	Controls input_;
	Point point_;
	Animation graphics_;
	Graphics::Renderer renderer_;
	Physics physics_;

	bool controlable_;
	hgeFont* font;

	// UI Elements for this player
	Graphics guiContainer_;
	Graphics guiContainerRectangle_;
	Animation guiContainerCoin_;
	hgeFont* guiText_;
	Point guiElements[3]; // Points for all gui elements

	Timer guiTimer_;
	
	// The current player score
	size_t score_;
};
#endif