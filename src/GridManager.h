#include <SFML/Graphics.hpp>

const int CELL_SIZE = 16;
const int COLUMN_COUNT = 10;
const int ROW_COUNT = 20;

class GridManager
{
public:
    static sf::Vector2i SnapPositionToGrid(sf::Vector2f pos);
    static sf::Vector2f SnapGridToPosition(sf::Vector2i gridPos);
};