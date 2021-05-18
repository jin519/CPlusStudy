#pragma once

#include "Unit.h"

class Tank : public Unit
{
public:
	explicit Tank(const int hp); 

	void setSeigeMode(const bool onOff);

protected:
	virtual int _getDamage() const override;

private:
	int(*__pDamageFunc)();
};