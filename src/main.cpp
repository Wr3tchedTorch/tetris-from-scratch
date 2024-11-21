#include <SFML/Graphics.hpp>
#include <functional>
#include "GridManager.h"
#include "Tetromino.h"

static const int WINDOW_ASPECT_RATIO_MULTIPLIER = 4;

int main()
{
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMN_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER, CELL_SIZE * ROW_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::View view(sf::Vector2f(CELL_SIZE * COLUMN_COUNT / 2, CELL_SIZE * ROW_COUNT / 2), sf::Vector2f(CELL_SIZE * COLUMN_COUNT, CELL_SIZE * ROW_COUNT));

    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block_tiles.png");

    GridManager manager;

    float defaultMovementDelay = 0.65f;
    Tetromino Tpiece(blockTexture, TetrominoShape::I, manager);

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Tpiece.SetMovementDelay(defaultMovementDelay);

        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.scancode)
                {
                case sf::Keyboard::Scancode::R:
                    printf("Rotating Tetromino!!!");
                    if (!Tpiece.GetIsOnGround())
                        Tpiece.Rotate();
                    break;
                case sf::Keyboard::Scancode::Down:
                    Tpiece.SetMovementDelay(defaultMovementDelay / 3.0f);
                    break;
                }
            }
        }

        window.setView(view);

        Tpiece.Update(deltaTime);        

        window.clear();
        Tpiece.Draw(window);
        window.display();
    }

    return 0;
}
