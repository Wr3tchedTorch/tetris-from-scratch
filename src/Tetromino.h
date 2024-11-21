#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "GridManager.h"

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
    GridManager &gridManager;
    sf::Vector2i currentGridPosition = {4, 1};
    sf::RectangleShape body;
    std::vector<sf::Vector2i> shape;
    
    float moveDelay = .65f;
    float totalTime = 0.0f;
    bool isOnGround;

public:
    Tetromino(sf::Texture &texture, TetrominoShape shape, GridManager &manager);
    Tetromino(sf::Color color, TetrominoShape shape, GridManager &manager);    

    void Update(float deltaTime);
    void Rotate();
    void Draw(sf::RenderWindow &window);
    bool MoveDown();
    void SetMovementDelay(float toMoveDelay);
    bool GetIsOnGround();

private:
    void MarkCellsAsOccupied();
};