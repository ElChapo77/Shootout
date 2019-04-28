#pragma once
#include<string>
using namespace std;

class Armor
{
	const unsigned resistance; //resistenta la damage pe care o ofera armura
	const string name; //numele armurii
	const int range_factor; //un factor care influenteaza range-ul unei arme (daca este pozitiv atunci arma are range-ul mai mare, daca e negativ atunci acesta este mai mic)
public:
	Armor(const unsigned&, const string&, const int&);
	virtual ~Armor() = 0;

	unsigned getResistance() const;
	string getName() const;
	int getRangeFactor() const;
};

class Light_Armor : public Armor
{
public:
	Light_Armor();
	~Light_Armor();
};

class Heavy_Armor : public Armor
{
public:
	Heavy_Armor();
	~Heavy_Armor();
};