#include "Unit.h"

using namespace std; 

Unit::Unit(const int hp) : __hp{ hp }
{}

bool Unit::isAlive() const
{
	return (__hp > 0);
}

void Unit::attack(Unit& unit) const
{
	unit.__hp -= _getDamage();
}

ostream& operator<<(ostream& o, const Unit& unit)
{
	o << "HP: " << unit.__hp << ", damage: " << unit._getDamage();
	return o; 
}