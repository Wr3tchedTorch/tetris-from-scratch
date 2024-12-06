//* ADD: Score system
//* ADD: Sound effects

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
        Red,
        Yellow,
        Purple,
        COUNT,
    };

    const std::map<TetrominoColor, sf::Vector2i> tetrominoColorToTextureCoordinates{
        {TetrominoColor::Blue, {1, 0}},
        {TetrominoColor::Green, {1, 1}},
        {TetrominoColor::Pink, {1, 2}},
        {TetrominoColor::Red, {1, 8}},
        {TetrominoColor::Yellow, {1, 9}},
        {TetrominoColor::Purple, {2, 7}},
    };

private:
    std::vector<Tetromino> tetrominosInTheGame;
    int score;
    const int SINGLE_LINE_SCORE_AMOUNT = 100;
    const int DOUBLE_LINE_SCORE_AMOUNT = 300;
    const int TRIPLE_LINE_SCORE_AMOUNT = 600;
    const int TETRIS_LINE_SCORE_AMOUNT = 1000;

    sf::Text scoreText;
    sf::Font tetrisFont;

public:
    Game();

    void IncrementScore(int numberOfRowsCleared);
    void DeleteRows(std::vector<int> targetRows);
    TetrominoColor GetRandomTetrominoColor();
    Tetromino::Shape GetRandomTetrominoShape();
    Tetromino *SpawnRandomTetromino(sf::Texture &texture, GridManager &gridManager);

    void Draw(sf::RenderWindow &window);
};
