#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

enum TetrominoShape
{
    NONE = -1,
    T,
    O,
    I,
    S,
    Z,
    L,
    J,
};

const std::map<TetrominoShape, std::vector<sf::Vector2i>> TetrominoShapes = {
    {TetrominoShape::O, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
    {TetrominoShape::I, {{0, -1}, {0, 0}, {0, 1}, {0, 2}}},
    {TetrominoShape::S, {{0, 0}, {1, 0}, {0, 1}, {-1, 1}}},
    {TetrominoShape::Z, {{0, 0}, {-1, 0}, {0, 1}, {1, 1}}},
    {TetrominoShape::L, {{0, 0}, {0, -1}, {0, 1}, {1, 1}}},
    {TetrominoShape::J, {{0, 0}, {0, -1}, {0, 1}, {-1, 1}}},
    {TetrominoShape::T, {{-1, 0}, {0, 0}, {1, 0}, {0, 1}}},
};

class Tetromino
{
private:
    sf::RectangleShape body;
    sf::Vector2i currentGridPosition = {4, 1};

    std::vector<sf::Vector2i> shape;

public:
    Tetromino(sf::Texture &texture, TetrominoShape shape);
    Tetromino(sf::Color color, TetrominoShape shape);
    
    void Update(float deltaTime, sf::RenderWindow & window);
    void Rotate();
    void Draw(sf::RenderWindow &window);
};