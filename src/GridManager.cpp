#include "GridManager.h"
#include <cmath>

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
