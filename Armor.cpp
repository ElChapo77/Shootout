#include "Armor.h"

/////////////////////////////// Armor ///////////////////////////////
Armor::Armor(const unsigned& r, const string& n, const int& rf)
	: resistance(r), name(n), range_factor(rf)
{}

Armor::~Armor()
{}

unsigned Armor::getResistance() const
{
	return resistance;
}

string Armor::getName() const
{
	return name;
}

int Armor::getRangeFactor() const
{
	return range_factor;
}

/////////////////////////////// Light_Armor ///////////////////////////////
Light_Armor::Light_Armor()
	: Armor(10, "Light Armor", 1)
{}

Light_Armor::~Light_Armor()
{}

/////////////////////////////// Heavy_Armor ///////////////////////////////
Heavy_Armor::Heavy_Armor()
	: Armor(20, "Heavy Armor", -1)
{}

Heavy_Armor::~Heavy_Armor()
{}