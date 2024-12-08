#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <algorithm>
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

    bool startPinDelayTimer = false;
    bool isPinned = false;

    float moveDelay;
    float moveDelayCounter = 0.0f;

    float pinDelay = 1.0f;
    float pinDelayCounter = 0.0f;

    sf::Clock pinDelayClock;
    const std::map<Tetromino::Shape, std::vector<sf::Vector2i>> shapeBlockCoordinates = {
        {Tetromino::Shape::O, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
        {Tetromino::Shape::I, {{0, -1}, {0, 0}, {0, 1}, {0, 2}}},
        {Tetromino::Shape::S, {{0, 0}, {1, 0}, {0, 1}, {-1, 1}}},
        {Tetromino::Shape::Z, {{0, 0}, {-1, 0}, {0, 1}, {1, 1}}},
        {Tetromino::Shape::L, {{0, -1}, {0, 0}, {0, 1}, {1, 1}}},
        {Tetromino::Shape::J, {{0, -1}, {0, 0}, {0, 1}, {-1, 1}}},
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
    void MoveAllBlocksDown(int deletedRow);

    void SetMovementDelay(float toMoveDelay);
    int DeleteBlocksAtRow(int row);
    bool GetIsPinned();

private:
    bool IsOnGround();
    bool Move(int xOffset = 0, int yOffset = 0);
    void MarkCellsAsOccupied();
    void RemoveCellsAsOccupied();
    sf::Vector2i GetBlockGlobalGridPosition(sf::Vector2i block);
};