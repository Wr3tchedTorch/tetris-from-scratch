#include <SFML/Graphics.hpp>

const int CELL_SIZE = 8;
const int COLUMN_COUNT = 10;
const int ROW_COUNT = 20;

class GridManager
{
private:
    unsigned int grid[COLUMN_COUNT][ROW_COUNT];

public:
    static sf::Vector2i SnapPositionToGrid(sf::Vector2f pos);
    static sf::Vector2i SnapPositionToGrid(sf::Vector2i pos);
    static sf::Vector2f GridToPosition(sf::Vector2i gridPos);
};