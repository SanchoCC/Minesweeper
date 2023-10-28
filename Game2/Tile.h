#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <Windows.h>
#include <vector>
class Tile : public sf::Drawable
{
public:
	Tile();
	Tile(float t_X, float t_Y);
	~Tile() = default;
	void ChangePosition(float x, float y);
	float getHeight();
	float getWidth();
	void update(float x, float y, Tile** arr);
	void update(float x, float y, int& minesNum, sf::Event event);
	void setMine();
	bool getMine();
	void setFlag();
	bool getFlag();
	void setBaseColor();
	void addMinesAround();
	int getMinesAround();
	bool getOpened();
	void setOpened();
	void fillAround(int x, int y, int rows, int cols);
	std::vector < std::pair<int, int> > getAround();
	void scanAround(Tile** arr);
private:
	sf::RectangleShape shape;
	const float height = 50;
	const float width = 50;
	int minesAround = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	bool mine = false;
	bool flag = false;
	bool opened = false;
	std::vector <std::pair<int, int>> around;
};
void SpawnMines(Tile** arr, int minesNum, int rows, int cols);
