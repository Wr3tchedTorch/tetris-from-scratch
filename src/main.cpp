// *ADD: refactor the code

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

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMN_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER, CELL_SIZE * ROW_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER), "Tetris from scratch in C++");
    window.setFramerateLimit(144);

    sf::View view(sf::Vector2f(CELL_SIZE * COLUMN_COUNT / 2, CELL_SIZE * ROW_COUNT / 2), sf::Vector2f(CELL_SIZE * COLUMN_COUNT, CELL_SIZE * ROW_COUNT));

    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block_tiles.png");

    GridManager gridManager;
    Game gameManager;

    float defaultMovementDelay = .50f;
    Tetromino *currentTetrominoPointer = gameManager.SpawnRandomTetromino(blockTexture, gridManager);

    float minMovementDelay = 0.06f;

    float movementDelayMultiplier = 0.90f;
    float movementDelayIncreaseDelayCounter = 0.0f;
    float movementDelayIncreaseDelay = 2.0f;

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        movementDelayIncreaseDelayCounter += deltaTime;
        if (movementDelayIncreaseDelayCounter >= movementDelayIncreaseDelay)
        {
            movementDelayIncreaseDelayCounter = 0.0f;
            
            if (defaultMovementDelay * movementDelayMultiplier >= minMovementDelay)
                defaultMovementDelay *= movementDelayMultiplier;
            else
                defaultMovementDelay = minMovementDelay;
        }

        if (currentTetrominoPointer->GetIsPinned())
        {
            gameManager.DeleteRows(gridManager.GetOccupiedRows());
            currentTetrominoPointer = gameManager.SpawnRandomTetromino(blockTexture, gridManager);
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