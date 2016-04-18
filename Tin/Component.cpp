#include "Component.h"

HGE* Component::hge_ = nullptr;

Component::Component()
{
}

Component::~Component()
{
}

void Component::registerHge()
{
	if (hge_ == nullptr)
		Component::hge_ = hgeCreate(HGE_VERSION);
}

void Component::unregisterHge()
{
	// Unload the HGE component
	if (Component::hge_ != nullptr)
	{
		Component::hge_->Release();
		Component::hge_ = nullptr;
	}
}

HGE* Component::getHge()
{
	return hge_;
}