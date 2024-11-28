#include <iostream>
#include "Tetromino.h"
#include "GridManager.h"

Tetromino::Tetromino(Shape myShape, GridManager &manager, sf::Texture &texture, sf::Vector2i textureCoordinates) : gridManager(manager)
{
    this->myShape = myShape;
    blockOffsetCoordinates = shapeBlockCoordinates.at(this->myShape);

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

void Tetromino::SetMovementDelay(float toMoveDelay)
{
    moveDelay = std::max(toMoveDelay, 0.0f);
}

void Tetromino::DeleteBlockAtRow(int row)
{
    if (row < 0 || row > ROW_COUNT)
        return;    
}

bool Tetromino::GetIsOnGround()
{
    return isOnGround;
}

void Tetromino::Rotate()
{
    if (myShape == Shape::O)
        return;

    std::vector<sf::Vector2i> toCoordinates;
    toCoordinates.reserve(blockOffsetCoordinates.size());

    for (const auto &blockOffset : blockOffsetCoordinates)
    {        
        sf::Vector2i newPos = GetBlockGlobalGridPosition({-blockOffset.y, blockOffset.x});
        if (!gridManager.IsPositionValid(newPos))
            return;
        toCoordinates.push_back(newPos);
    }
    blockOffsetCoordinates = toCoordinates;
}

void Tetromino::Draw(sf::RenderWindow &window)
{
    for (auto blockOffset : blockOffsetCoordinates)
    {
        sf::Vector2i newBlockPosition = GetBlockGlobalGridPosition(blockOffset);

        body.setPosition(GridManager::GridToPosition(sf::Vector2i(newBlockPosition)));
        window.draw(body);
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

bool Tetromino::Move(int xQuantity, int yQuantity)
{
    for (auto blockOffset : blockOffsetCoordinates)
    {
        sf::Vector2i blockPosition = GetBlockGlobalGridPosition(blockOffset);
        blockPosition.x += xQuantity;
        blockPosition.y += yQuantity;

        if (!gridManager.IsPositionValid(blockPosition))
        {
            if (yQuantity == 1)
                MarkCellsAsOccupied();
            return false;
        }
    }

    currentGridPosition.x += xQuantity;
    currentGridPosition.y += yQuantity;
    return true;
}

void Tetromino::MarkCellsAsOccupied()
{
    for (auto blockOffset : blockOffsetCoordinates)
    {
        sf::Vector2i blockPosition = GetBlockGlobalGridPosition(blockOffset);
        gridManager.MarkPositionAsOccupied(blockPosition);
    }
}

sf::Vector2i Tetromino::GetBlockGlobalGridPosition(sf::Vector2i blockOffset)
{
    return sf::Vector2i(currentGridPosition.x + blockOffset.x, currentGridPosition.y + blockOffset.y);
}