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
};

const std::map<TetrominoShape, std::vector<sf::Vector2i>> TetrominoShapes = {
    {TetrominoShape::T, {{0, 0}, {1, 0}, {2, 0}, {1, 1}}},
    {TetrominoShape::O, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
    {TetrominoShape::I, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
    {TetrominoShape::S, {{1, 0}, {2, 0}, {0, 1}, {1, 1}}},
    {TetrominoShape::Z, {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
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

    void Update(float deltaTime);
    void Rotate();
    void Draw(sf::RenderWindow &window);
};