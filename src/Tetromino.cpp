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

void Tetromino::SetMovementDelay(float toMoveDelay)
{
    moveDelay = std::max(toMoveDelay, 0.0f);
}

int Tetromino::DeleteBlocksAtRow(int row)
{
    if (row < 0 || row > ROW_COUNT)
        return -1;

    RemoveCellsAsOccupied();
    int quantityOfBlocksDeleted = 0;
    for (int i = blockOffsetCoordinates.size() - 1; i >= 0; i--)
    {
        auto blockOffset = blockOffsetCoordinates.at(i);
        sf::Vector2i blockPosition = GetBlockGlobalGridPosition(blockOffset);
        if (blockPosition.y == row)
        {
            blockOffsetCoordinates.erase(blockOffsetCoordinates.begin() + i);
            quantityOfBlocksDeleted++;
        }
    }
    return quantityOfBlocksDeleted;
}

bool Tetromino::IsOnGround()
{
    for (auto blockOffset : blockOffsetCoordinates)
    {
        sf::Vector2i blockPosition = GetBlockGlobalGridPosition(blockOffset);
        blockPosition.y += 1;

        if (!gridManager.IsPositionValid(blockPosition))
        {
            return true;
        }
    }
    return false;
}

void Tetromino::Rotate()
{
    if (myShape == Shape::O)
        return;

    std::vector<sf::Vector2i> toCoordinates;
    toCoordinates.reserve(blockOffsetCoordinates.size());

    for (const auto &blockOffset : blockOffsetCoordinates)
    {
        sf::Vector2i toBlockOffset = {-blockOffset.y, blockOffset.x};
        sf::Vector2i toGlobalPosition = GetBlockGlobalGridPosition(toBlockOffset);
        if (!gridManager.IsPositionValid(toGlobalPosition))
            return;
        toCoordinates.push_back(toBlockOffset);
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
    if (IsOnGround())
        MarkCellsAsOccupied();
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

void Tetromino::RemoveCellsAsOccupied()
{
    for (auto blockOffset : blockOffsetCoordinates)
    {
        sf::Vector2i blockPosition = GetBlockGlobalGridPosition(blockOffset);
        gridManager.RemovePositionAsOccupied(blockPosition);
    }
}

sf::Vector2i Tetromino::GetBlockGlobalGridPosition(sf::Vector2i blockOffset)
{
    return sf::Vector2i(currentGridPosition.x + blockOffset.x, currentGridPosition.y + blockOffset.y);
}