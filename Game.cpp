#include "Game.h"

Game::Game(const unsigned& h, const unsigned& w)
	: round(0), map(h, w)
{
	srand((unsigned)time(NULL));
	spawnAgents();
	cout << endl << map;
}

Game::~Game()
{
	cout << "\n\nGame over!\n\n";
	if (agents.size() == 1) //in cazul in care jocul nu a fost intrerupt de user, atunci se va afisa agentul care a castigat
		cout << "Agent " << agents[0]->getSymbol() << " is the winner\n\n";

	cout << "Let's eliminate the last agents:\n";

	for (unsigned i = 0; i < weapons.size(); i++) //distruge armele
		delete weapons[i];
	for (unsigned i = 0; i < agents.size(); i++) //distruge agentii ramasi in joc
		delete agents[i];
	
}

//spawneaza agentii pe harta
void Game::spawnAgents()
{
	//creeaza cate o arma pt fiecare tip
	weapons.push_back(new AK47);
	weapons.push_back(new Pistol);
	weapons.push_back(new Shotgun);

	//creeaza cate o armura pt fiecare tip
	armors.push_back(NULL);
	armors.push_back(new Light_Armor);
	armors.push_back(new Heavy_Armor);

	char symbol = 'A';
	pair<unsigned, unsigned> p;
	unsigned i;

	for (i = 0; i < 5; i++, symbol++) //creeaza 5 Vertical_Agents
	{
		do //incearca obtinerea unei pozitii libere de pe harta
		{
			p = make_pair(rand() % map.getHeight(), rand() % map.getWidth());
		} while (map.isPositionEmpty(p) == false);

		agents.push_back(new Vertical_Agent(p, symbol, make_pair(Orientation(rand() % 2), Orientation(rand() % 2 + 2)), weapons[rand() % 3], armors[rand() % 3]));
		map.setChar(agents[i]->getPosition(), agents[i]->getSymbol());
	}

	for (; i < 10; i++, symbol++) //creeaza 5 Orizontal_Agents
	{
		do //incearca obtinerea unei pozitii libere de pe harta
		{
			p = make_pair(rand() % map.getHeight(), rand() % map.getWidth());
		} while (map.isPositionEmpty(p) == false);

		agents.push_back(new Orizontal_Agent(p, symbol, make_pair(Orientation(rand() % 2 + 2), Orientation(rand() % 2)), weapons[rand() % 3], armors[rand() % 3]));
		map.setChar(agents[i]->getPosition(), agents[i]->getSymbol());
	}
}

//porneste jocul
void Game::run()
{
	char input;
	cout << "Press Y to continue or something else to stop... ";
	cin >> input;

	while (agents.size() > 1 && (input == 'Y' || input == 'y'))
	{
		pair<unsigned, unsigned> posEnemy;
		round++;
		cout << "\nRound " << round << endl;

		for (unsigned i = 0; i < agents.size(); i++)
		{
			char s = agents[i]->getSymbol();
			posEnemy = agents[i]->enemyInVision(map); //pozitia unui posibil inamic

			if (posEnemy.first == map.getHeight() && posEnemy.second == map.getWidth()) //daca nu are pe nimeni in raza de viziune atunci se muta pe o pozitie noua
				agents[i]->move(map);
			else //daca se afla cineva in raza de viziune
			{
				if (agents[i]->canShoot(posEnemy) == true) //daca se afla si in raza armei atunci il impusca
					agents[i]->shoot(agents, map, posEnemy);
				else //daca nu se afla in raza armei atunci se muta mai aproape de inamic
					agents[i]->goCloser(agents, map, posEnemy);
			}

			if (i == agents.size() || s != agents[i]->getSymbol()) //pt a mentine for-ul corect in caz ca un agent este eliminat
				i--;
		}

		cout << map;

		cout << "Press Y to continue or something else to stop... ";
		cin >> input;
	}
}