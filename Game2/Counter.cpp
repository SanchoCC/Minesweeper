#include "Counter.h"
void Counter::setCounter(int &counter)
{
    this->counter = counter;
}
std::string Counter::getCounter()
{
        if (this->counter == 100)
        {
            return "M";
        }
        if (this->counter <= 0)
        {
            return " ";
        }
        else
        {
            return std::to_string(this->counter);
        }
}
Counter::Counter(int counter, float positionX, float positionY, int CharacterSize)
{

    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    setCounter(counter);
    text.setString(getCounter());
    text.setCharacterSize(CharacterSize);
    text.setOrigin(0, 0);
    text.setPosition(positionX, positionY);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    opened = true;
}
Counter::Counter()
{
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    if (tile.getHeight() > tile.getWidth()) 
    {
        text.setCharacterSize(tile.getHeight() * 0.7);
        text.setScale(1, tile.getWidth() / tile.getHeight());
    }
    else {
        text.setCharacterSize(tile.getWidth() * 0.7);
        text.setScale(tile.getHeight() / tile.getWidth(), 1);
    }
   
    text.setOrigin(0, -100);
    text.setPosition(0, 0);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
}
void Counter::draw(sf::RenderWindow& window) const
{
    window.draw(this->text);
}
void Counter::ChangePosition(float x, float y)
{
    text.setPosition(y, x);
}
void Counter::update(int minesNum, bool opened)
{
    setCounter(minesNum);
    switch (minesNum)
    {
    case 0:       
        break;
    case 1:
        text.setFillColor(sf::Color::Cyan);
        break;
    case 2: 
        text.setFillColor(sf::Color::Green);
        break;
    case 3: 
        text.setFillColor(sf::Color::Red);
        break;
    case 4:
        text.setFillColor(sf::Color::Blue);
        break;
    case 5:
        text.setFillColor(sf::Color::Yellow);
        break;
    case 6:
        text.setFillColor(sf::Color::Magenta);
        break;
    default:
        text.setFillColor(sf::Color::Black);
        break;
    }  
    if (opened)
    {
        text.setString(getCounter());
    }
}