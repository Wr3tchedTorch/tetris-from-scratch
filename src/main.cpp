#include <SFML/Graphics.hpp>
#include "GridManager.h"
#include "Tetromino.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMN_COUNT * 3, CELL_SIZE * ROW_COUNT * 3), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::View view(sf::Vector2f(CELL_SIZE * COLUMN_COUNT / 2, CELL_SIZE * ROW_COUNT / 2), sf::Vector2f(CELL_SIZE * COLUMN_COUNT, CELL_SIZE * ROW_COUNT));

    sf::RectangleShape body(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    body.setFillColor(sf::Color::Blue);

    Tetromino Tpiece(sf::Color::Red);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.setView(view);

        auto targetPos = GridManager::SnapPositionToGrid(sf::Vector2f(sf::Mouse::getPosition(window) / 3));
        body.setPosition(sf::Vector2f(targetPos));

        window.clear();
        Tpiece.Draw(window);
        window.draw(body);
        window.display();
    }
}
