#include <iostream>
#include "Tetromino.h"
#include "GridManager.h"

Tetromino::Tetromino(Shape myShape, GridManager &manager, sf::Texture &texture, sf::Vector2i textureCoordinates) : gridManager(manager)
{
    this->myShape = myShape;
    myShapeCoordinates = shapeBlockCoordinates.at(this->myShape);

    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect(textureCoordinates * CELL_SIZE, sf::Vector2i(CELL_SIZE, CELL_SIZE)));
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    isOnGround = false;
}

void Tetromino::Update(float deltaTime)
{
    totalTime += deltaTime;
    if (totalTime >= moveDelay)
    {
        totalTime = 0.0f;
        isOnGround = !MoveDown();
    }
}

bool Tetromino::MoveDown()
{
    return Move(0, 1);
}

void Tetromino::MoveLeft()
{
    Move(-1, 0);
}

void Tetromino::MoveRight()
{
    Move(1, 0);
}

bool Tetromino::Move(int xOffset, int yOffset)
{
    for (auto block : myShapeCoordinates)
    {
        sf::Vector2i blockPosition = sf::Vector2i(currentGridPosition.x + block.x + xOffset, currentGridPosition.y + block.y + yOffset);
        if (!gridManager.IsPositionValid(blockPosition))
        {
            if (yOffset == 1) MarkCellsAsOccupied();
            return false;
        }
    }

    sf::Vector2i newPosition = sf::Vector2i(currentGridPosition.x + xOffset, currentGridPosition.y + yOffset);
    currentGridPosition = newPosition;
    return true;
}

void Tetromino::SetMovementDelay(float toMoveDelay)
{
    moveDelay = std::max(toMoveDelay, 0.0f);
}

bool Tetromino::GetIsOnGround()
{
    return isOnGround;
}

void Tetromino::MarkCellsAsOccupied()
{
    for (auto block : myShapeCoordinates)
    {
        sf::Vector2i blockPosition = sf::Vector2i(currentGridPosition.x + block.x, currentGridPosition.y + block.y);
        gridManager.MarkPositionAsOccupied(blockPosition);
    }
}

void Tetromino::Rotate()
{
    if (myShape == Shape::O)
        return;

    std::vector<sf::Vector2i> toCoordinates;
    toCoordinates.reserve(myShapeCoordinates.size());

    for (const auto &block : myShapeCoordinates)
    {
        sf::Vector2i newPos = {-block.y, block.x};
        if (!gridManager.IsPositionValid({currentGridPosition.x + newPos.x, currentGridPosition.y + newPos.y}))
            return;
        toCoordinates.push_back(newPos);
    }
    myShapeCoordinates = toCoordinates;
}

void Tetromino::Draw(sf::RenderWindow &window)
{
    for (auto block : myShapeCoordinates)
    {
        sf::Vector2i newBlockPosition = sf::Vector2i(currentGridPosition.x + block.x, currentGridPosition.y + block.y);

        body.setPosition(GridManager::GridToPosition(sf::Vector2i(newBlockPosition)));
        window.draw(body);
    }
}
