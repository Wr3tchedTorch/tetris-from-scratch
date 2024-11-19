const int CELL_SIZE = 8;
const int COLUMN_COUNT = 10;
const int ROW_COUNT = 20;

#pragma once

#include <SFML/Graphics.hpp>
#include <set>

struct Vector2Compare
{
    bool operator()(const sf::Vector2<int> &lhs, const sf::Vector2<int> &rhs) const
    {
        if (lhs.x != rhs.x)
            return lhs.x < rhs.x;
        return lhs.y < rhs.y;
    }
};

class GridManager
{
private:
    std::set<sf::Vector2i, Vector2Compare> occupiedCells;

public:
    static sf::Vector2i SnapPositionToGrid(sf::Vector2f pos);
    static sf::Vector2i SnapPositionToGrid(sf::Vector2i pos);
    static sf::Vector2f GridToPosition(sf::Vector2i gridPos);
    bool IsPositionValid(sf::Vector2i pos);
    void MarkPositionAsOccupied(sf::Vector2i pos);
    void RemovePositionAsOccupied(sf::Vector2i pos);
    bool ClearFilledRows();
};