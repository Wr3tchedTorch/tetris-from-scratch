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
    for (auto block : myShapeCoordinates)
    {
        sf::Vector2i blockPosition = sf::Vector2i(currentGridPosition.x + block.x, currentGridPosition.y + block.y + 1);
        if (!gridManager.IsPositionValid(blockPosition))
        {
            MarkCellsAsOccupied();
            return false;
        }
    }

    sf::Vector2i newPosition = sf::Vector2i(currentGridPosition.x, currentGridPosition.y + 1);
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
