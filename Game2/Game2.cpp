#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "Tile.h"
#include "Counter.h"

int main()
{
    Tile tile(0, 0);
        
    const int rows = 10;      
    const int cols = 10;
    const int& field = rows*cols;
    const float& windowWidth = cols*50;
    const float& windowHeight = rows*50+100;
    int minesNum = 20;
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
            arr[i][j].ChangePosition(50 * i, 50 * j);
            arr[i][j].fillAround(i, j, rows, cols);
            arrCounter[i][j].ChangePosition(50 * i+3, 50 * j + 10);
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
            counter.update(minesNum);
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    window.draw(arr[i][j]);
                    arr[i][j].update(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y - 150, arr);
                    arrCounter[i][j].draw(window);
                    int thisCounter = arr[i][j].getMinesAround();
                    arrCounter[i][j].update(thisCounter);
                    arrCounter[i][j].update(arr[i][j].getOpened());                                      
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        arr[i][j].update(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y - 150, minesNum, event);

                    }
                }
            }
            window.display();
        }
    }
    return 0;
}
