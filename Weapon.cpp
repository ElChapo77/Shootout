#include "Weapon.h"

///////////////////////////// Weapon /////////////////////////////
Weapon::Weapon(const unsigned& d, const unsigned& r, const string& n)
	: damage(d), range(r), name(n)
{}

Weapon::~Weapon()
{}

unsigned Weapon::getDamage() const
{
	return damage;
}

unsigned Weapon::getRange() const
{
	return range;
}

string Weapon::getName() const
{
	return name;
}
///////////////////////////// AK47 /////////////////////////////
AK47::AK47()
	: Weapon(50, 8, "AK47")
{}

AK47::~AK47()
{}

///////////////////////////// Pistol /////////////////////////////
Pistol::Pistol()
	: Weapon(30, 6, "Pistol")
{}

Pistol::~Pistol()
{}

///////////////////////////// Shotgun /////////////////////////////
Shotgun::Shotgun()
	: Weapon(100, 3, "Shotgun")
{}

Shotgun::~Shotgun()
{}