#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>
using namespace std;

class Map
{
	vector<vector<char>> matrix; //matricea de caractere a hartii
	const unsigned height; //inaltimea hartii
	const unsigned width; //latimea hartii
public:
	Map(const unsigned&, const unsigned&);
	Map(const Map&);
	~Map();

	void setChar(const pair<unsigned, unsigned>&, const char&);
	char getChar(const pair<unsigned, unsigned>&) const;
	const unsigned getHeight() const;
	const unsigned getWidth() const;
	bool isPositionEmpty(const pair<unsigned, unsigned>&) const;

	friend ostream& operator<<(ostream&, const Map&);
};