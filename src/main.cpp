// *ADD: brief delay before tetromino is set fixed on the ground

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>

#include "GridManager.h"
#include "Tetromino.h"
#include "Game.h"

static const int WINDOW_ASPECT_RATIO_MULTIPLIER = 4;

int score = 0;

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMN_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER, CELL_SIZE * ROW_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::View view(sf::Vector2f(CELL_SIZE * COLUMN_COUNT / 2, CELL_SIZE * ROW_COUNT / 2), sf::Vector2f(CELL_SIZE * COLUMN_COUNT, CELL_SIZE * ROW_COUNT));

    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block_tiles.png");

    GridManager gridManager;
    Game gameManager;

    float defaultMovementDelay = 0.50f;

    Tetromino *currentTetrominoPointer = gameManager.SpawnRandomTetromino(blockTexture, gridManager);    

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        if (currentTetrominoPointer->IsOnGround())
        {
            currentTetrominoPointer = gameManager.SpawnRandomTetromino(blockTexture, gridManager);
            gameManager.DeleteRows(gridManager.GetOccupiedRows());
        }

        currentTetrominoPointer->SetMovementDelay(defaultMovementDelay);
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
                case sf::Keyboard::Scancode::Left:
                case sf::Keyboard::Scancode::A:
                    currentTetrominoPointer->MoveLeft();
                    break;
                case sf::Keyboard::Scancode::Right:
                case sf::Keyboard::Scancode::D:
                    currentTetrominoPointer->MoveRight();
                    break;
                case sf::Keyboard::Scancode::Down:
                case sf::Keyboard::Scancode::S:
                    currentTetrominoPointer->SetMovementDelay(defaultMovementDelay / 6.0f);
                    break;
                case sf::Keyboard::Scancode::R:
                    currentTetrominoPointer->Rotate();
                    break;
                }
            }
        }        

        window.setView(view);

        currentTetrominoPointer->Update(deltaTime);

        window.clear();
        gameManager.Draw(window);
        window.display();
    }

    delete currentTetrominoPointer;

    return 0;
}