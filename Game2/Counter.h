#pragma once

#include <string>
#include "Tile.h"

#include <SFML/Graphics.hpp>

class Counter
{
public:
	Counter(int counter, float positionX, float positionY, int CharacterSize);
	Counter();
	void setCounter(int& counter);
	std::string getCounter();
	void draw(sf::RenderWindow& window) const;
	void update(int minesNum, bool opened);
	void ChangePosition(float x, float y);
private:
	Tile tile;
	sf::Font font;
	sf::Text text;
	int counter;
	bool opened = false;
};




			