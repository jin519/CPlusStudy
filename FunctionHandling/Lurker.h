#pragma once

#include "Unit.h"

class Lurker : public Unit 
{
public:
	explicit Lurker(const int hp); 

	void burrow(const bool onOff);

protected:
	virtual int _getDamage() const override;

private:
	int(Lurker::* __pGetDamage)() const;

	int __getOnDamage() const;
	int __getOffDamage() const;
};