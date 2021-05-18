#pragma once

#include <iostream>

class Unit 
{
public:
	explicit Unit(const int hp); 

	bool isAlive() const;
	void attack(Unit& unit) const;

	friend std::ostream& operator<<(std::ostream& o, const Unit& unit);

protected:
	virtual int _getDamage() const = 0;

private:
	int __hp = 0; 
};