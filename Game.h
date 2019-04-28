#pragma once
#include"Map.h"
#include"Agent.h"
#include<ctime>

class Game
{
	Map map; //harta
	unsigned round; //numarul rundei curente
	vector<Agent*> agents; //vector ce retine toti agentii aflati in joc in runda curenta
	vector<const Weapon*> weapons; //vector ce contine toate tipurile de arme
	vector<const Armor*> armors; //vector ce contine toate tipurile de armuri

	void spawnAgents();
public:
	Game(const unsigned&, const unsigned&);
	~Game();

	void run();
};