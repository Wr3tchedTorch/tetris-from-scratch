#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "GridManager.h"

class Tetromino
{
public:
    enum Shape
    {
        NONE = -1,
        T,
        O,
        I,
        S,
        Z,
        L,
        J,
        COUNT,
    };

private:
    GridManager &gridManager;
    sf::Vector2i currentGridPosition = {4, 1};
    sf::RectangleShape body;

    std::vector<sf::Vector2i> blockOffsetCoordinates;
    Shape myShape;

    float moveDelay = .65f;
    float totalTime = 0.0f;

    const std::map<Tetromino::Shape, std::vector<sf::Vector2i>> shapeBlockCoordinates = {
        {Tetromino::Shape::O, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
        {Tetromino::Shape::I, {{0, -1}, {0, 0}, {0, 1}, {0, 2}}},
        {Tetromino::Shape::S, {{0, 0}, {1, 0}, {0, 1}, {-1, 1}}},
        {Tetromino::Shape::Z, {{0, 0}, {-1, 0}, {0, 1}, {1, 1}}},
        {Tetromino::Shape::L, {{0, 0}, {0, -1}, {0, 1}, {1, 1}}},
        {Tetromino::Shape::J, {{0, 0}, {0, -1}, {0, 1}, {-1, 1}}},
        {Tetromino::Shape::T, {{-1, 0}, {0, 0}, {1, 0}, {0, 1}}},
    };

public:
    Tetromino(Shape myShape, GridManager &manager, sf::Texture &texture, sf::Vector2i textureCoordinates = {0, 0});

    void Update(float deltaTime);
    void Rotate();
    void Draw(sf::RenderWindow &window);

    bool MoveDown();
    void MoveLeft();
    void MoveRight();

    void SetMovementDelay(float toMoveDelay);
    int DeleteBlocksAtRow(int row);
    bool IsOnGround();

private:
    bool Move(int xOffset = 0, int yOffset = 0);
    void MarkCellsAsOccupied();
    void RemoveCellsAsOccupied();
    sf::Vector2i GetBlockGlobalGridPosition(sf::Vector2i block);
};