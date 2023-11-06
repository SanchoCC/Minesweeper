#include <iostream>
#include <ctime>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Tile.h"
#include "Counter.h"

int main()
{   
    Tile tile;
    float tileHeight = tile.getHeight();
    float tileWidth = tile.getWidth();
    const int rows = 9;      
    const int cols = 9;
    const int& field = rows*cols;
    const float& windowWidth = cols*tileHeight;
    const float& windowHeight = rows*tileWidth+100;
    int minesNum = 10;
    if (minesNum >= field)
    {
        std::cerr << "Too many mines." << std::endl;
        return 1;
    }
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    window.setFramerateLimit(60);
    sf::Event event;
    
    Tile** arr = new Tile * [rows];
    for (int i = 0; i < rows; ++i)
    {
        arr[i] = new Tile[cols];
    }
    Counter** arrCounter = new Counter * [rows];
    for (int i = 0; i < rows; ++i)
    {
        arrCounter[i] = new Counter[cols];
    }
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            arr[i][j].ChangePosition(tileWidth * i, tileHeight * j);
            arr[i][j].fillAround(i, j, rows, cols);
            arrCounter[i][j].ChangePosition(tileWidth * i+tileWidth/15, tileHeight * j+tileHeight/10);
            int thisCounter = arr[i][j].getMinesAround();
            arrCounter[i][j].setCounter(thisCounter);
        }
    }
    SpawnMines(arr, minesNum, rows, cols);
    Counter counter(minesNum, 30, 0, 80);
    while (window.isOpen())
    {
        while (window.pollEvent(event)) 
        {
            window.clear(sf::Color::White);
            if (event.type == sf::Event::Closed)
            {
                for (int i = 0; i < rows; ++i)
                {
                    delete[] arr[i];
                }
                delete[] arr;
                for (int i = 0; i < rows; ++i)
                {
                    delete[] arrCounter[i];
                }
                delete[] arrCounter;
                window.close();
                break;
            }
            counter.draw(window);
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    window.draw(arr[i][j]);
                    arrCounter[i][j].draw(window);
                    int thisCounter = arr[i][j].getMinesAround();
                    arrCounter[i][j].update(thisCounter, arr[i][j].getOpened());;                                      
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        arr[i][j].update(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y - (100 + tileWidth), minesNum, event);

                    }
                    arr[i][j].update(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y - (100+tileWidth), arr);

                    counter.update(minesNum, true);
                }
            }
            window.display();
        }
    }
    return 0;
}
