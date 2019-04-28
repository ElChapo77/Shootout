#pragma once
#include<utility>
#include<queue>
#include"Map.h"
#include"Weapon.h"
#include"Armor.h"

enum Orientation { Up, Down, Left, Right };

class Agent
{
	int health; //viata
	pair<unsigned, unsigned> position; //pozitia pe harta
	const char symbol; //simbol
	pair<Orientation,Orientation> orientation; //orientarea (.first reprezinta de fapt orientarea, .sencond l-am folosit pt a-i schimba directia de deplasare cand se loveste de perete)
	const unsigned vision; //raza de viziune
	const Weapon* const weapon; //arma
	const Armor* const armor; //armura

protected:
	void setPosition(const pair<unsigned, unsigned>&);
	void setOrientation(const pair<Orientation, Orientation>&);
	pair<Orientation, Orientation> getOrientation() const;
	const unsigned getVision() const;
	const unsigned getSpeed() const;
	int getHealth() const;
	string getWeaponName() const;
	string getArmorName() const;
	void takeDamage(const unsigned&);
	unsigned giveDamage() const;

public:
	Agent(const int&, const pair<unsigned, unsigned>&, const char&, const pair<Orientation, Orientation>&, const unsigned&, const Weapon* const&, const Armor* const&);
	virtual ~Agent() = 0;

	pair<unsigned, unsigned> getPosition() const;
	char getSymbol() const;
	virtual void move(Map&) = 0;
	pair<unsigned,unsigned> enemyInVision(Map) const;
	void shoot(vector<Agent*>&, Map&, const pair<unsigned, unsigned>&) const;
	bool isDead() const;
	bool canShoot(const pair<unsigned, unsigned>&) const;
	void goCloser(vector<Agent*>&, Map&, const pair<unsigned, unsigned>&);
};

class Vertical_Agent : public Agent
{
public:
	Vertical_Agent(const pair<unsigned, unsigned>&, const char&, const pair<Orientation, Orientation>&, const Weapon* const&, const Armor* const&);
	~Vertical_Agent();

	void move(Map&);
};

class Orizontal_Agent : public Agent
{
public:
	Orizontal_Agent(const pair<unsigned, unsigned>&, const char&, const pair<Orientation, Orientation>&, const Weapon* const&, const Armor* const&);
	~Orizontal_Agent();

	void move(Map&);
};