#include <cmath>
#include <iostream>
#include "GridManager.h"

sf::Vector2i GridManager::SnapPositionToGrid(sf::Vector2f pos)
{
    int newX = static_cast<int>(floor(pos.x / CELL_SIZE));
    int newY = static_cast<int>(floor(pos.y / CELL_SIZE));

    return sf::Vector2i(newX, newY);
}

sf::Vector2i GridManager::SnapPositionToGrid(sf::Vector2i pos)
{
    return SnapPositionToGrid(sf::Vector2f(pos));
}

sf::Vector2f GridManager::GridToPosition(sf::Vector2i gridPos)
{
    float x = gridPos.x * CELL_SIZE;
    float y = gridPos.y * CELL_SIZE;
    return sf::Vector2f(x, y);
}

std::vector<int> GridManager::GetOccupiedRows()
{
    std::vector<int> occupiedRows;

    int numberOfItemsOnRow = 0;
    int currentRow = -1;
    for (auto pos : occupiedCells)
    {
        if (pos.y != currentRow)
        {
            currentRow = pos.y;
            numberOfItemsOnRow = 0;
        }

        numberOfItemsOnRow++;

        if (numberOfItemsOnRow == COLUMN_COUNT)
        {
            occupiedRows.push_back(currentRow);
        }
    }

    std::cout << "\n";
    return occupiedRows;
}

bool GridManager::IsPositionValid(sf::Vector2i pos)
{
    bool isOutOfBounds = (pos.x < 0 || pos.x >= COLUMN_COUNT) || (pos.y < 0 || pos.y >= ROW_COUNT);
    return !isOutOfBounds && occupiedCells.find(pos) == occupiedCells.end();
}

void GridManager::MarkPositionAsOccupied(sf::Vector2i pos)
{
    occupiedCells.insert(pos);
}

void GridManager::RemovePositionAsOccupied(sf::Vector2i pos)
{
    occupiedCells.erase(pos);
}
