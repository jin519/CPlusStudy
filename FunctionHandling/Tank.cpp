#include "Tank.h"

Tank::Tank(const int hp) : Unit{ hp }
{
	setSeigeMode(false); 
}

constexpr void Tank::setSeigeMode(const bool onOff)
{
	__pGetDamage = onOff ? &Tank::__getOnDamage : &Tank::__getOffDamage;
}

int Tank::_getDamage() const
{
	return (this->*__pGetDamage)(); 
}

constexpr int Tank::__getOnDamage() const
{
	return 70; 
}

constexpr int Tank::__getOffDamage() const
{
	return 25; 
}
