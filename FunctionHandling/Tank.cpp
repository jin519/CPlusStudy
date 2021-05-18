#include "Tank.h"

Tank::Tank(const int hp) : Unit{ hp }
{
	setSeigeMode(false); 
}

void Tank::setSeigeMode(const bool onOff)
{
	if (onOff)
	{
		__pDamageFunc = []() -> int
		{
			return 70;
		};
	}
	else
	{
		__pDamageFunc = []() -> int
		{
			return 25;
		};
	}
}

int Tank::_getDamage() const
{
	return __pDamageFunc();
}