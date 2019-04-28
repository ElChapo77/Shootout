#include "Agent.h"

/////////////////////////////// Agent ///////////////////////////////
Agent::Agent(const int& h, const pair<unsigned, unsigned>& p, const char& s, const pair<Orientation, Orientation>& o, const unsigned& v, const Weapon* const& w, const Armor* const& a)
	: health(h), position(p), symbol(s), orientation(o), vision(v), weapon(w), armor(a)
{
	cout << "Agent " << symbol << " spawned on position (" << position.first << ',' << position.second << ") with " << weapon->getName();
	if (armor != NULL)
		cout << " and " << armor->getName();
	cout << endl;
}

Agent::~Agent()
{
	cout << "!!!!!!!!!! Agent " << symbol << " was eliminated !!!!!!!!!!\n";
}

void Agent::setPosition(const pair<unsigned, unsigned>& p)
{
	position = p;
}

void Agent::setOrientation(const pair<Orientation, Orientation>& o)
{
	orientation = o;
}

pair<Orientation, Orientation> Agent::getOrientation() const
{
	return orientation;
}

const unsigned Agent::getVision() const
{
	return vision;
}

//obtine viteza de deplasare a agentului
const unsigned Agent::getSpeed() const
{
	return vision / 2;
}

int Agent::getHealth() const
{
	return health;
}

string Agent::getWeaponName() const
{
	return weapon->getName();
}

string Agent::getArmorName() const
{
	if (armor == NULL)
		return "no armor";
	return armor->getName();
}

pair<unsigned, unsigned> Agent::getPosition() const
{
	return position;
}

char Agent::getSymbol() const
{
	return symbol;
}

//returneaza pozitia celui mai apropiat inamic aflat in raza de viziune, iar daca nu exista, returneaza o pozitie in afara hartii
pair<unsigned,unsigned> Agent::enemyInVision(Map map) const
{
	//un agent are viziunea matricea patratica de marimea razei de viziune (x2) ce il are pe el ca centru
	//daca aceasta matrice iese de pe harta, atunci acele parti ce ies, sunt ignorate

	unsigned startLine, endLine, startCol, endCol;
	//obinerea matricei in care agentul are viziune
	if (position.first - vision < map.getHeight())
		startLine = position.first - vision;
	else
		startLine = 0;

	if (position.first + vision < map.getHeight())
		endLine = position.first + vision;
	else
		endLine = map.getHeight() - 1;

	if (position.second - vision < map.getWidth())
		startCol = position.second - vision;
	else
		startCol = 0;

	if (position.second + vision < map.getWidth())
		endCol = position.second + vision;
	else
		endCol = map.getWidth() - 1;

	queue<pair<unsigned, unsigned>> q;
	pair<unsigned, unsigned> pos = position;
	q.push(pos);
	map.setChar(pos, '-');
	//aflarea celui mai apropiat agent aflat in raza de viziune
	while (q.size() > 0)
	{
		pos = q.front();
		q.pop();
		for (unsigned i = pos.first - 1; i <= pos.first + 1; i++)
			for (unsigned j = pos.second - 1; j <= pos.second + 1; j++)
			{
				pair<unsigned, unsigned> posEnemy(i, j);
				if (posEnemy.first >= startLine && posEnemy.first <= endLine && posEnemy.second >= startCol && posEnemy.second <= endCol)
				{
					if (map.getChar(posEnemy) != '-')
						if (map.isPositionEmpty(posEnemy) == false)
							return posEnemy;
						else
						{
							q.push(posEnemy);
							map.setChar(posEnemy, '-');
						}
				}
			}
	}

	return make_pair(map.getHeight(), map.getWidth());
}

//updateaza viata agentului dupa ce a fost impuscat
void Agent::takeDamage(const unsigned& d)
{
	if (armor == NULL)
		health -= (int)d;
	else
		health = health - ((int)d - armor->getResistance());
}

//obtine damage-ul pe care il poate oferi agentul
unsigned Agent::giveDamage() const
{
	return weapon->getDamage();
}

//verifica daca a murit
bool Agent::isDead() const
{
	return health <= 0;
}

//impusca un agent
void Agent::shoot(vector<Agent*>& agents, Map& map, const pair<unsigned, unsigned>& posEnemy) const
{
	for (unsigned j = 0; j < agents.size(); j++)
		if (agents[j]->getPosition().first == posEnemy.first && agents[j]->getPosition().second == posEnemy.second)
		{
			agents[j]->takeDamage(giveDamage());
			cout << "Agent " << symbol << " (" << health << " hp, " << weapon->getName() << ", " << getArmorName() << ") shots agent " << agents[j]->symbol << endl;
			if (agents[j]->isDead()) //daca agentul impuscat moare, atunci va fi eliminat din joc
			{
				map.setChar(posEnemy, ' ');
				delete agents[j];
				agents.erase(agents.begin() + j);
			}
			break;
		}
}

//returneaza true daca inamicul poate fi impuscat (se afla in raza armei)
bool Agent::canShoot(const pair<unsigned, unsigned>& posEnemy) const
{
	if (max(position.first, posEnemy.first) - min(position.first, posEnemy.first) > weapon->getRange() + (armor == NULL ? 0 : armor->getRangeFactor()))
		return false;
	if (max(position.second, posEnemy.second) - min(position.second, posEnemy.second) > weapon->getRange() + (armor == NULL ? 0 : armor->getRangeFactor()))
		return false;
	return true;
}

//muta agentul mai aproape de inamicul ce are ca pozitie parametrul posEnemy
void Agent::goCloser(vector<Agent*>& agents, Map& map, const pair<unsigned, unsigned>& posEnemy)
{
	map.setChar(position, ' ');
	//am folosit o metoda personala si greu de explicat prin comentarii...
	if (position.first >= posEnemy.first && position.second <= posEnemy.second)
	{
		if (position.first - getSpeed() < map.getHeight())
			position.first = max(position.first - getSpeed(), posEnemy.first + 1);
		else
			position.first = posEnemy.first + 1;

		position.second = min(position.second + getSpeed(), posEnemy.second - 1);
	}

	else if (position.first >= posEnemy.first && position.second >= posEnemy.second)
	{
		if (position.first - getSpeed() < map.getHeight())
			position.first = max(position.first - getSpeed(), posEnemy.first + 1);
		else
			position.first = posEnemy.first + 1;

		if (position.second - getSpeed() < map.getWidth())
			position.second = max(position.second - getSpeed(), posEnemy.second + 1);
		else
			position.second = posEnemy.second + 1;
	}

	else if (position.first <= posEnemy.first && position.second >= posEnemy.second)
	{
		position.first = min(position.first + getSpeed(), posEnemy.first - 1);

		if (position.second - getSpeed() < map.getWidth())
			position.second = max(position.second - getSpeed(), posEnemy.second + 1);
		else
			position.second = posEnemy.second + 1;
	}

	else
	{
		position.first = min(position.first + getSpeed(), posEnemy.first - 1);
		position.second = min(position.second + getSpeed(), posEnemy.second - 1);
	}

	map.setChar(position, symbol);
	for (unsigned j = 0; j < agents.size(); j++)
		if (agents[j]->getPosition().first == posEnemy.first && agents[j]->getPosition().second == posEnemy.second)
		{
			cout << "Agent " << symbol << " (" << health << " hp, " << weapon->getName() << ", " << getArmorName() << ") moved closer to agent " << agents[j]->symbol << endl;
			break;
		}
}

/////////////////////////////// Vertical_Agent ///////////////////////////////
Vertical_Agent::Vertical_Agent(const pair<unsigned, unsigned>& p, const char& s, const pair<Orientation, Orientation>& o, const Weapon* const& w, const Armor* const& a)
	: Agent(100, p, s, o, 10, w, a)
{}

Vertical_Agent::~Vertical_Agent()
{}

//schimba pozitia agentului pe harta intr-un mod determinist
void Vertical_Agent::move(Map& map)
{
	//acest tip de agent se misca vertical (in sus sau in jos) iar atunci cand loveste peretii hartii isi schimba pozitia (la stanga sau la dreapta in functie de context), urmand apoi sa-si continue miscarea obisnuita (in jos sau sus)

	map.setChar(getPosition(), ' ');

	pair<Orientation, Orientation> orientation = getOrientation();
	pair<unsigned, unsigned> position = getPosition();

	if (orientation.first == Up)
	{
		if (position.first - getSpeed() < map.getHeight())
			setPosition(make_pair(position.first - getSpeed(), position.second));
		else
		{
			if (orientation.second == Right)
			{
				if (position.second + getSpeed() < map.getWidth())
				{
					setPosition(make_pair(position.first, position.second + getSpeed()));
					setOrientation(make_pair(Down, Right));
				}
				else
				{
					setPosition(make_pair(position.first, position.second - getSpeed()));
					setOrientation(make_pair(Down, Left));
				}
			}
			else
			{
				if (position.second - getSpeed() < map.getWidth())
				{
					setPosition(make_pair(position.first, position.second - getSpeed()));
					setOrientation(make_pair(Down, Left));
				}
				else
				{
					setPosition(make_pair(position.first, position.second + getSpeed()));
					setOrientation(make_pair(Down, Right));
				}
			}
		}
	}
	else
	{
		if (position.first + getSpeed() < map.getHeight())
			setPosition(make_pair(position.first + getSpeed(), position.second));
		else
		{
			if (orientation.second == Right)
			{
				if (position.second + getSpeed() < map.getWidth())
				{
					setPosition(make_pair(position.first, position.second + getSpeed()));
					setOrientation(make_pair(Up, Right));
				}
				else
				{
					setPosition(make_pair(position.first, position.second - getSpeed()));
					setOrientation(make_pair(Up, Left));
				}
			}
			else
			{
				if (position.second - getSpeed() < map.getWidth())
				{
					setPosition(make_pair(position.first, position.second - getSpeed()));
					setOrientation(make_pair(Up, Left));
				}
				else
				{
					setPosition(make_pair(position.first, position.second + getSpeed()));
					setOrientation(make_pair(Up, Right));
				}
			}
		}
	}

	map.setChar(getPosition(), getSymbol());
	cout << "Agent " << getSymbol() << " (" << getHealth() << " hp, " << getWeaponName() << ", " << getArmorName() << ") moved to another position \n";
}

/////////////////////////////// Orizontal_Agent ///////////////////////////////
Orizontal_Agent::Orizontal_Agent(const pair<unsigned, unsigned>& p, const char& s, const pair<Orientation, Orientation>& o, const Weapon* const& w, const Armor* const& a)
	: Agent(100, p, s, o, 10, w, a)
{}

Orizontal_Agent::~Orizontal_Agent()
{}

//schimba pozitia agentului pe harta intr-un mod determinist
void Orizontal_Agent::move(Map& map)
{
	//acest tip de agent se misca orizontal (in stanga sau in dreapta) iar atunci cand loveste peretii hartii isi schimba pozitia (in sus sau in jos in functie de context), urmand apoi sa-si continue miscarea obisnuita (in stanga sau in dreapta)

	map.setChar(getPosition(), ' ');

	pair<Orientation, Orientation> orientation = getOrientation();
	pair<unsigned, unsigned> position = getPosition();

	if (orientation.first == Right)
	{
		if (position.second + getSpeed() < map.getWidth())
			setPosition(make_pair(position.first, position.second + getSpeed()));
		else
		{
			if (orientation.second == Up)
			{
				if (position.first - getSpeed() < map.getHeight())
				{
					setPosition(make_pair(position.first - getSpeed(), position.second));
					setOrientation(make_pair(Left, Up));
				}
				else
				{
					setPosition(make_pair(position.first + getSpeed(), position.second));
					setOrientation(make_pair(Left, Down));
				}
			}
			else
			{
				if (position.first + getSpeed() < map.getHeight())
				{
					setPosition(make_pair(position.first + getSpeed(), position.second));
					setOrientation(make_pair(Left, Down));
				}
				else
				{
					setPosition(make_pair(position.first - getSpeed(), position.second));
					setOrientation(make_pair(Left, Up));
				}
			}
		}
	}
	else
	{
		if (position.second - getSpeed() < map.getWidth())
			setPosition(make_pair(position.first, position.second - getSpeed()));
		else
		{
			if (orientation.second == Up)
			{
				if (position.first - getSpeed() < map.getHeight())
				{
					setPosition(make_pair(position.first - getSpeed(), position.second));
					setOrientation(make_pair(Right, Up));
				}
				else
				{
					setPosition(make_pair(position.first + getSpeed(), position.second));
					setOrientation(make_pair(Right, Down));
				}
			}
			else
			{
				if (position.first + getSpeed() < map.getHeight())
				{
					setPosition(make_pair(position.first + getSpeed(), position.second));
					setOrientation(make_pair(Right, Down));
				}
				else
				{
					setPosition(make_pair(position.first - getSpeed(), position.second));
					setOrientation(make_pair(Right, Up));
				}
			}
		}
	}

	map.setChar(getPosition(), getSymbol());
	cout << "Agent " << getSymbol() << " (" << getHealth() << " hp, " << getWeaponName() << ", " << getArmorName() << ") moved to another position \n";
}