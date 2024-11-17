#include <SFML/Graphics.hpp>
#include "GridManager.h"
#include "Tetromino.h"

static const int WINDOW_ASPECT_RATIO_MULTIPLIER = 4;

int main()
{
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMN_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER, CELL_SIZE * ROW_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::View view(sf::Vector2f(CELL_SIZE * COLUMN_COUNT / 2, CELL_SIZE * ROW_COUNT / 2), sf::Vector2f(CELL_SIZE * COLUMN_COUNT, CELL_SIZE * ROW_COUNT));

    sf::RectangleShape body(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    body.setFillColor(sf::Color::Blue);

    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block_tiles.png");

    Tetromino Tpiece(blockTexture, TetrominoShape::Z);

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

        auto targetPos = GridManager::SnapPositionToGrid(sf::Vector2f(sf::Mouse::getPosition(window) / WINDOW_ASPECT_RATIO_MULTIPLIER));
        body.setPosition(sf::Vector2f(targetPos));

        window.clear();
        Tpiece.Draw(window);
        window.draw(body);
        window.display();
    }
}
