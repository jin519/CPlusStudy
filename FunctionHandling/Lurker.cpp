#include "Lurker.h"

Lurker::Lurker(const int hp) : Unit{ hp }
{
	burrow(false); 
}

constexpr void Lurker::burrow(const bool onOff)
{
	__pGetDamage = onOff ? &Lurker::__getOnDamage : &Lurker::__getOffDamage;
}

int Lurker::_getDamage() const
{
	return (this->*__pGetDamage)(); 
}

constexpr int Lurker::__getOnDamage() const
{
	return 40;
}

constexpr int Lurker::__getOffDamage() const
{
	return 0;
}
