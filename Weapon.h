#pragma once
#include<string>
using namespace std;

class Weapon
{
	const unsigned damage; //damage-ul pe care il da arma
	const unsigned range; //raza in care gloantele lovesc tinta
	const string name; //numele armei
public:
	Weapon(const unsigned&, const unsigned&, const string&);
	virtual ~Weapon() = 0;

	unsigned getDamage() const;
	unsigned getRange() const;
	string getName() const;
};

class AK47 : public Weapon
{
public:
	AK47();
	~AK47();
};

class Pistol : public Weapon
{
public:
	Pistol();
	~Pistol();
};

class Shotgun : public Weapon
{
public:
	Shotgun();
	~Shotgun();
};