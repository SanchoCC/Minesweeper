#include "Tile.h"
void Tile::setBaseColor()
{
	shape.setFillColor(sf::Color(100, 100, 100));
}
Tile::Tile()
{
	setBaseColor();
	shape.setSize(sf::Vector2f(this->height, this->width));
	shape.setOrigin(0, -100);
	shape.setOutlineColor(sf::Color(50, 50, 50));
	shape.setOutlineThickness(4);
}
float Tile::getHeight() 
{
	return height;
}
float Tile::getWidth()
{
	return width;
}
void Tile::ChangePosition(float x, float y) 
{
	shape.setPosition(y, x);
}
void Tile::draw(sf::RenderTarget& target, sf::RenderStates state) const 
{
	target.draw(this->shape, state);
}
void Tile::scanAround(Tile** arr)
{
	if (minesAround == 0)
	{
		for (int i = 0; i < getAround().size(); ++i)
		{
			arr[getAround()[i].first][getAround()[i].second].setOpened();
		}
	}	
}
void Tile::update(float x, float y, int& minesNum, sf::Event event)
{
	if (x > shape.getPosition().x && x < shape.getPosition().x + height && y < shape.getPosition().y && y > shape.getPosition().y - width)
	{
			if (event.mouseButton.button == sf::Mouse::Right && !opened && !flag)
			{
				setFlag();
				--minesNum;
			}
			else if (event.mouseButton.button == sf::Mouse::Right && flag)
			{
				setFlag();
				++minesNum;
			}
			else if (event.mouseButton.button == sf::Mouse::Left && !flag)
			{
				setOpened();
			}
	}
}
void Tile::update(float x, float y, Tile **arr)
{
	if (opened)
	{
		shape.setFillColor(sf::Color::White);
		flag = false;
		scanAround(arr);
	}
	if (flag)
	{
		shape.setFillColor(sf::Color::Red);
	}
	/*else if (mine)
	{
		shape.setFillColor(sf::Color::Red);
	}
	else if (minesAround>0)
	{
		shape.setFillColor(sf::Color::Green);
	}*/
	if (!flag&&!opened)
	{
		setBaseColor();
	}
	if (x > shape.getPosition().x && x < shape.getPosition().x + height && y < shape.getPosition().y && y > shape.getPosition().y - width && !flag && !opened)
	{
		shape.setFillColor(sf::Color(100, 100, 100, 120));
	}
}
void Tile::setMine()
{
	mine = true;
}
bool Tile::getMine()
{
	return mine;
}
void Tile::setFlag()
{
	flag = !getFlag(); 
}
bool Tile::getFlag()
{
	return flag;
}
void Tile::addMinesAround()
{
	if (!mine)
	{
		++minesAround;
	}
}
int Tile::getMinesAround()
{
	if (mine) 
	{
		++minesAround;
		return 100;
	}
	else 
	{
		return minesAround;
	}
}
bool Tile::getOpened()
{
	return opened;
}
void Tile::setOpened()
{
	opened = true;
}
void SpawnMines(Tile** arr, int minesNum, int rows, int cols) 
{
	std::srand(time(NULL));
	for (int i = 0; i < minesNum; ++i)
	{
		int randomX = rand() % rows;
		int randomY = rand() % cols;
		if (!arr[randomX][randomY].getMine())
		{
			arr[randomX][randomY].setMine();
			for (int i = 0; i < arr[randomX][randomY].getAround().size(); ++i)
			{
				arr[arr[randomX][randomY].getAround()[i].first][arr[randomX][randomY].getAround()[i].second].addMinesAround();
			}
		}
		else
		{
			--i;
		}
	}
}
void Tile::fillAround(int x, int y, int rows, int cols)
{
	if (around.size() < 1)
	{
		around.push_back(std::make_pair(x, y));
		if (x != rows - 1)
		{
			around.push_back(std::make_pair(x + 1, y));
			if (y != cols - 1)
			{
				around.push_back(std::make_pair(x + 1, y + 1));
			}
			if (y != 0)
			{
				around.push_back(std::make_pair(x + 1, y - 1));
			}
		}

		if (x != 0)
		{
			around.push_back(std::make_pair(x - 1, y));
			if (y != cols - 1)
			{
				around.push_back(std::make_pair(x - 1, y + 1));
			}
			if (y != 0)
			{
				around.push_back(std::make_pair(x - 1, y - 1));
			}
		}
		if (y != cols - 1)
		{
			around.push_back(std::make_pair(x, y + 1));
		}
		if (y != 0)
		{
			around.push_back(std::make_pair(x, y - 1));
		}
	}
}
std::vector <std::pair<int, int>> Tile::getAround()
{
	return around;
}