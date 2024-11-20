#include <iostream>
#include "Tetromino.h"
#include "GridManager.h"

Tetromino::Tetromino(sf::Texture &texture, TetrominoShape shape, GridManager &manager) : gridManager(manager)
{
    this->shape = TetrominoShapes.at(shape);
    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(CELL_SIZE, CELL_SIZE)));
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
}

Tetromino::Tetromino(sf::Color color, TetrominoShape shape, GridManager &manager) : gridManager(manager)
{
    this->shape = TetrominoShapes.at(shape);
    body.setFillColor(color);
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
}

void Tetromino::Update(float deltaTime)
{
    totalTime += deltaTime;
    if (totalTime >= moveDelay)
    {
        totalTime = 0.0f;
        MoveDown();
    }
}

void Tetromino::MoveDown()
{
    for (auto block : shape)
    {
        sf::Vector2i blockPosition = sf::Vector2i(currentGridPosition.x + block.x, currentGridPosition.y + block.y + 1);
        if (!gridManager.IsPositionValid(blockPosition))
            return;
    }
    sf::Vector2i newPosition = sf::Vector2i(currentGridPosition.x, currentGridPosition.y + 1);
    currentGridPosition = newPosition;
}

void Tetromino::SetMovementDelay(float toMoveDelay)
{
    moveDelay = std::max(toMoveDelay, 0.0f);
}

void Tetromino::MarkCellsAsOccupied()
{
    for (auto block : shape)
    {
        sf::Vector2i blockPosition = sf::Vector2i(currentGridPosition.x + block.x, currentGridPosition.y + block.y);
        gridManager.MarkPositionAsOccupied(blockPosition);
    }
}

void Tetromino::Rotate()
{
    for (auto &block : shape)
    {
        int temp = block.y;
        block.y = block.x;
        block.x = -temp;
    }
}

void Tetromino::Draw(sf::RenderWindow &window)
{
    for (auto block : shape)
    {
        sf::Vector2i newBlockPosition = sf::Vector2i(currentGridPosition.x + block.x, currentGridPosition.y + block.y);

        body.setPosition(GridManager::GridToPosition(sf::Vector2i(newBlockPosition)));
        window.draw(body);
    }
}
