#include <SFML/Graphics.hpp>
#include <vector>
#include "GridManager.h"
#include "Tetromino.h"

static const int WINDOW_ASPECT_RATIO_MULTIPLIER = 4;

TetrominoShape GetRandomTetrominoShape();
Tetromino SpawnRandomTetromino(Tetromino * tetrominoPointer, sf::Texture &texture, GridManager &gridManager);

int main()
{
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMN_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER, CELL_SIZE * ROW_COUNT * WINDOW_ASPECT_RATIO_MULTIPLIER), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::View view(sf::Vector2f(CELL_SIZE * COLUMN_COUNT / 2, CELL_SIZE * ROW_COUNT / 2), sf::Vector2f(CELL_SIZE * COLUMN_COUNT, CELL_SIZE * ROW_COUNT));

    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block_tiles.png");

    GridManager manager;

    float defaultMovementDelay = 0.65f;
    
    Tetromino *currentTetrominoPointer;
    std::vector<Tetromino> tetrominosInTheGame;
    tetrominosInTheGame.push_back(SpawnRandomTetromino(currentTetrominoPointer, blockTexture, manager));

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        if (currentTetrominoPointer->GetIsOnGround())
        {
            tetrominosInTheGame.push_back(SpawnRandomTetromino(currentTetrominoPointer, blockTexture, manager));
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
                case sf::Keyboard::Scancode::R:
                    printf("Rotating Tetromino!!!");
                    if (!currentTetrominoPointer->GetIsOnGround())
                        currentTetrominoPointer->Rotate();
                    break;
                case sf::Keyboard::Scancode::Down:
                    currentTetrominoPointer->SetMovementDelay(defaultMovementDelay / 3.0f);
                    break;
                }
            }
        }

        window.setView(view);        

        currentTetrominoPointer->Update(deltaTime);
        window.clear();
        for (Tetromino item : tetrominosInTheGame)
            item.Draw(window);
        window.display();
    }

    return 0;
}

TetrominoShape GetRandomTetrominoShape()
{
    int randomIndex = rand() % 7;
    return static_cast<TetrominoShape>(randomIndex + 1);
}

Tetromino SpawnRandomTetromino(Tetromino *tetrominoPointer, sf::Texture &texture, GridManager &gridManager)
{
    Tetromino toTetromino(texture, GetRandomTetrominoShape(), gridManager);
    tetrominoPointer = &toTetromino;
    return toTetromino;
}