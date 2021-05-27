#pragma once

#include "Unit.h"

class Tank : public Unit
{
public:
	explicit Tank(const int hp); 

	constexpr void setSeigeMode(const bool onOff);

protected:
	virtual int _getDamage() const override;

private:
	int(Tank::* __pGetDamage)() const;

	constexpr int __getOnDamage() const;
	constexpr int __getOffDamage() const;
};