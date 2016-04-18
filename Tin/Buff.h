#ifndef BUFF_H
#define BUFF_H

#include "Entity.h"
#include "Timer.h"

class Buff
{
public:
	enum Type { ADDITION, MULTIPLICATION, NR_OF_TYPES };
	enum Job { SCALE, VELOCITY, NR_OF_JOBS };

	Buff(float duration, Buff::Type type, Buff::Job job, float stat, bool infinite = false);
	virtual ~Buff();

	void setStat(float value);
	void setType(Buff::Type type);
	void setJob(Buff::Job job);

	void apply(float& orig);
	bool update(); // returns false when expired

	Buff::Type getType() const;
	Buff::Job getJob() const;
	const Timer* getTimer();

	float getStat() const;
	bool isInfinite() const;

private:
	Type type_;
	Job job_;

	Timer duration_;
	float stat_;
	bool infinite_;
};

#endif