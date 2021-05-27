#pragma once

#include "Unit.h"

class Lurker : public Unit 
{
public:
	explicit Lurker(const int hp); 
	constexpr void burrow(const bool onOff);

protected:
	virtual int _getDamage() const override;

private:
	int(Lurker::* __pGetDamage)() const;

	constexpr int __getOnDamage() const;
	constexpr int __getOffDamage() const;
};