#include "Buff.h"


Buff::Buff(float duration, Buff::Type type, Buff::Job job, float stat, bool infinite)
	: duration_(duration)
{
	type_ = type;
	job_ = job; // They job this buff will do.
	stat_ = stat;
	infinite_ = infinite;
}

Buff::~Buff(){}

void Buff::setStat(float value)
{
	stat_ = value;
}
void Buff::setType(Buff::Type type)
{
	type_ = type;
}
void Buff::setJob(Buff::Job job)
{
	job_ = job;
}

void Buff::apply(float& orig)
{
	switch (type_)
	{
		case Buff::ADDITION: orig += stat_; break;
		case Buff::MULTIPLICATION: orig *= stat_; break;
	}
}
bool Buff::update()
{
	duration_.tick();

	return (infinite_ == true) ? false : duration_.isStopped();
}

Buff::Type Buff::getType() const
{
	return type_;
}
Buff::Job Buff::getJob() const
{
	return job_;
}
const Timer* Buff::getTimer()
{
	return &duration_;
}
float Buff::getStat() const
{
	return stat_;
}

bool Buff::isInfinite() const
{
	return infinite_;
}