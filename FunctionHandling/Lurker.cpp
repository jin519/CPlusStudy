#include "Lurker.h"

Lurker::Lurker(const int hp) : Unit{ hp }
{
	burrow(false); 
}

void Lurker::burrow(const bool onOff)
{
	if (onOff) 
	{
		__pDamageFunc = []() -> int
		{
			return 40;
		};
	}
	else 
	{
		__pDamageFunc = []() -> int
		{
			return 0;
		};
	}
}

int Lurker::_getDamage() const
{
	return __pDamageFunc(); 
}