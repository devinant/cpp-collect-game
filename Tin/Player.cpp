#include "Player.h"


Player::Player(bool controlable)
	: graphics_("textures/hero.png", 4, 4, 12.0f),
	  physics_(3.0f, 1.0f, 3.0f, 3.0f),

	  guiContainer_("textures/gui/timer.png"),
	  guiContainerCoin_("textures/gui/timer-coin.png", 5, 1, 24.0f),
	  guiTimer_(60.0f, true)
{
	controlable_ = controlable;
	score_ = 0;
	printf("Hero spawned at %f %f with id: %d\n", point_.getX(), point_.getY(), this->getId());

	if (this->getId() == 1)
	{
		point_.setXY(176.0f, 107.f); // Player 1 start position
		
		guiElements[0].setXY(4.0f,  4.0f);  // GUI
		guiElements[1].setXY(64.0f, 40.0f); // Coin
		guiElements[2].setXY(48.0f, 8.0f);  // ContainerRectangle
	}
		
	else if (this->getId() == 2)
	{
		point_.setXY(928.0f, 648.0f); // Player 2 start position

		float mvX = 680.0f;
		guiElements[0].setXY(4.0f + mvX, 4.0f);   // GUI
		guiElements[1].setXY(64.0f + mvX, 40.0f); // Coin
		guiElements[2].setXY(48.0f + mvX, 8.0f);  // ContainerRectangle
	}
	

	renderer_.setAsset(Player::DOWN);
	renderer_.setPoint(point_);

	// Set the basestats for the Hero object
	base_[Buff::SCALE].first    = base_[Buff::SCALE].second = graphics_.getHScale();
	base_[Buff::VELOCITY].first = base_[Buff::VELOCITY].second = physics_.getMaxVelocity();

	// Load the font for the GUI
	guiText_ = new hgeFont("fonts/gooddog16px.fnt");
	guiContainerRectangle_.setColor(0xffff79a5);
	guiContainerRectangle_.setRectangle(0.0f, 0.0f, guiContainer_.getWidth(), 24.0f);

	printf("Size of image: %f\nRect: %f\n", guiContainer_.getWidth(), (guiContainer_.getWidth()-41.0f));
	guiContainer_.setCenter();
	guiContainerCoin_.setCenter();
}
Player::~Player()
{
	delete guiText_;
}
bool Player::isControlable() const
{
	return controlable_;
}
void Player::setScore(size_t score)
{
	score_ = score;
}
size_t Player::getScore() const
{
	return score_;
}
Timer* Player::getTimer() 
{
	return &guiTimer_;
}
void Player::handleControls()
{
	if (isControlable()) {
		int up = (this->getId() == 1) ? HGEK_UP : HGEK_W;
		int down = (this->getId() == 1) ? HGEK_DOWN : HGEK_S;
		int left = (this->getId() == 1) ? HGEK_LEFT : HGEK_A;
		int right = (this->getId() == 1) ? HGEK_RIGHT : HGEK_D;

		if (input_.press(up) || input_.press(down) || input_.press(left) || input_.press(right))
		{
			// Constant velocity. For now.
			float v = physics_.getVelocity();
			
			if (input_.press(up))
			{
				point_.moveY(-v);
				renderer_.setAsset(Player::UP);
			}	

			if (input_.press(down))
			{
				point_.moveY(v);
				renderer_.setAsset(Player::DOWN);
			}
			
			if (input_.press(left))
			{
				point_.moveX(-v);
				renderer_.setAsset(Player::LEFT);
			}

			if (input_.press(right))
			{
				point_.moveX(v);
				renderer_.setAsset(Player::RIGHT);
			}
			 
			renderer_.setPoint(point_);
			graphics_.play();
		}
		else 
		{
			graphics_.stop();
		}
	}
}
void Player::handleBuffs()
{
	
	// Set default buffs
	graphics_.setScale(base_[Buff::SCALE].first);
	renderer_.setScale(base_[Buff::SCALE].first);

	   physics_.setVelocity(base_[Buff::VELOCITY].first);
	physics_.setMaxVelocity(base_[Buff::VELOCITY].first);


	// Modify the values
	base_[Buff::SCALE].second    = base_[Buff::SCALE].first;
	base_[Buff::VELOCITY].second = base_[Buff::VELOCITY].first;

	// Update buffs.
	std::multimap<const char*, Buff>::iterator it = stats_.begin();

	while (it != stats_.end())
	{
		if (it->second.update())
			stats_.erase(it++);
		else
		{
			const Buff::Job job = it->second.getJob();

			// Get our value
			it->second.apply(base_[job].second); 

			if (job == Buff::VELOCITY)
			{
				physics_.setVelocity(base_[job].second);
				physics_.setMaxVelocity(base_[job].second);
			}

			if (job == Buff::SCALE)
			{
				renderer_.setScale(base_[job].second);
				graphics_.setScale(base_[job].second);
			}
			++it;
		}
	}
}
void Player::event(const hgeRect &w)
{
	// Hero collides with a wall
	point_.resolve(physics_.getVelocity(), box(), w);

	// Update the point for the renderer immedietly
	renderer_.setPoint(point_);
}
void Player::event(Entity* e)
{
	// The item will contain stats that we apply to the player.
	Item* item = dynamic_cast<Item*>(e);

	if (item)
	{
		// Apply all the buffs
		// item->buff(buffs_); // Apply item modifiers
		item->stat(stats_);

		// Send a message to the item aswell. We've picked it up!
		item->event(this);
	}
	
	// Another player
	if (dynamic_cast<Player*>(e))
	{
		// Decrease the speed of both players
		PDescriptor buff = PDescriptor("Hit", Buff(0.5f, Buff::MULTIPLICATION, Buff::VELOCITY, 0.99f));

		stats_.insert(buff);
		static_cast<Player*>(e)->stats_.insert(buff);

		e->event(box());
		event(e->box());
	}

}
hgeRect Player::box() const
{
	// Hero has a smaller bounding box.
	hgeRect orig = graphics_.getBoundingBox();
	return hgeRect(orig.x1, orig.y1 + ((orig.y2 - orig.y1) * 0.5f), orig.x2, orig.y2);
}
Point& Player::position()  
{ 
	return point_;
}
Graphics::Renderer* Player::getRenderer()
{
	return &renderer_;
}
void Player::update()
{

	handleBuffs();
	handleControls();
	physics_.update();

	// Tick down the timer
	guiTimer_.tick();

	// Decrease the size
	guiContainerRectangle_.setRectangle(guiElements[0].getX(), guiElements[0].getY(), 279.0f * guiTimer_.format<Timer::TO_FRACTION, float>(guiTimer_.getRemainder()), 24.0f);
}
void Player::render()
{
	/* PERFORMANCE WARNING */
	//StatList::iterator it = stats_.begin();
	//size_t i = 0;
	//
	//for (it = stats_.begin(); it != stats_.end(); it++)
	//{
	//	font->printf(
	//		200.0f, 
	//		20.0f + (15.0f * i++), 0, 
	//		
	//		"Buff active: %s: %d", it->first, 
	//		
	//		it->second.getTimer()->format<Timer::TO_SECONDS, int>(
	//			it->second.getTimer()->getRemainder()
	//		)
	//	);
	//}
	
	guiContainerRectangle_.render(guiElements[2].getX(), guiElements[2].getY());
	guiContainerCoin_.render(guiElements[1].getX(), guiElements[1].getY());
	guiContainer_.render(guiElements[0].getX(), guiElements[0].getY());
	guiText_->printf(guiElements[2].getX() + 24.0f, 12.0f, HGETEXT_LEFT, "%d seconds left", guiTimer_.format<Timer::TO_SECONDS, int>(guiTimer_.getRemainder()));
	guiText_->printf(guiElements[1].getX() + 24.0f, guiElements[1].getY(), HGETEXT_LEFT, "%d coins", score_);
	graphics_.render(renderer_);
}