#include "Map.h"

Map::Map(const unsigned& h, const unsigned& w)
	: height(h), width(w)
{
	matrix.resize(height);
	for (unsigned i = 0; i < height; i++)
	{
		matrix[i].resize(width);
		fill(matrix[i].begin(), matrix[i].end(), ' ');
	}
}

Map::Map(const Map& map)
	: Map(map.height, map.width)
{
	matrix = map.matrix;
}

Map::~Map()
{}

//pune pe harta caracterul c, pe pozitia p
void Map::setChar(const pair<unsigned, unsigned>& p, const char& c)
{
	if (p.first >= height || p.second >= width)
	{
		throw out_of_range("Invalid position");
	}
	matrix[p.first][p.second] = c;
}

//returneaza caracterul de pe harta aflat pe pozitia p
char Map::getChar(const pair<unsigned, unsigned>& p) const
{
	if (p.first >= height || p.second >= width)
	{
		throw out_of_range("Invalid position");
	}
	return matrix[p.first][p.second];
}
 //returneaza true daca pe pozitia p nu se afla vreun agent
bool Map::isPositionEmpty(const pair<unsigned, unsigned>& p) const
{
	if (p.first >= height || p.second >= width)
	{
		throw out_of_range("Invalid position");
	}
	return matrix[p.first][p.second] == ' ';
}

const unsigned Map::getHeight() const
{
	return height;
}

const unsigned Map::getWidth() const
{
	return width;
}

//pt afisarea hartii
ostream& operator<<(ostream& out, const Map& map)
{
	out << ' ';
	for (unsigned j = 1; j < map.width + 1; j++)
		out << '-';
	out << endl;
	for (unsigned i = 0; i < map.height; i++)
	{
		out << '|';
		for (unsigned j = 0; j < map.width; j++)
			out << map.matrix[i][j];
		out << '|' << endl;
	}
	out << ' ';
	for (unsigned j = 1; j < map.width + 1; j++)
		out << '-';
	out << endl;
	return out;
}