#include "Tank.h"

Tank::Tank(const int hp) : Unit{ hp }
{
	setSeigeMode(false); 
}

void Tank::setSeigeMode(const bool onOff)
{
	__pGetDamage = onOff ? &Tank::__getOnDamage : &Tank::__getOffDamage;
}

int Tank::_getDamage() const
{
	return (this->*__pGetDamage)(); 
}

int Tank::__getOnDamage() const
{
	return 70; 
}

int Tank::__getOffDamage() const
{
	return 25; 
}
