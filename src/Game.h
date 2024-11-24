#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "Tetromino.h"

class Game
{
public:    
    enum TetrominoColor
    {
        NONE = -1,
        Blue,
        Green,
        Pink,
        // Red,
        // Yellow,
        // Purple,
        COUNT,
    };

    const std::map<TetrominoColor, sf::Vector2i> tetrominoColorToTextureCoordinates{
        {TetrominoColor::Blue, {1, 0}},
        {TetrominoColor::Green, {1, 1}},
        {TetrominoColor::Pink, {1, 2}},
    };

private:
    std::vector<Tetromino> tetrominosInTheGame;

public:
    Game();

    TetrominoColor GetRandomTetrominoColor();
    Tetromino::Shape GetRandomTetrominoShape();
    Tetromino *SpawnRandomTetromino(sf::Texture &texture, GridManager &gridManager);
    void Draw(sf::RenderWindow &window);
};
