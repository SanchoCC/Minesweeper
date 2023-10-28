#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"
class Counter
{
public:
	Counter(int counter, float positionX, float positionY, int CharacterSize);
	Counter();
	void setCounter(int& counter);
	std::string getCounter();
	void draw(sf::RenderWindow& window) const;
	void update(int minesNum);
	void update(bool opened);
	void ChangePosition(float x, float y);
private:
	sf::Font font;
	sf::Text text;
	int counter;
	bool opened = false;
};




			