#include <iostream>
#include <time.h>
#include "Game.h"

Game::Game()
{
    score = 0;
    if (!tetrisFont.loadFromFile("fonts/Tetris.ttf"))
        std::cout << "!!! Error: couldn't load Tetris font !!!";

    scoreText.setFont(tetrisFont);
    scoreText.setPosition(2, 2);
    scoreText.setScale(0.215f, 0.215f);
    scoreText.setString("Score: " + std::to_string(score));

    srand(time(NULL));
}

void Game::IncrementScore(int numberOfRowsCleared)
{
    switch (numberOfRowsCleared)
    {
    case 1:
        score += SINGLE_LINE_SCORE_AMOUNT;
        break;
    case 2:
        score += DOUBLE_LINE_SCORE_AMOUNT;
        break;
    case 3:
        score += TRIPLE_LINE_SCORE_AMOUNT;
        break;
    default:
        score += TETRIS_LINE_SCORE_AMOUNT;
    }
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::DeleteRows(std::vector<int> targetRows)
{
    if (targetRows.size() == 0)
        return;

    for (auto row : targetRows)
    {
        for (auto &tetromino : tetrominosInTheGame)
        {
            tetromino.DeleteBlocksAtRow(row);
        }
    }
    for (auto row : targetRows)
    {
        for (auto &tetromino : tetrominosInTheGame)
        {
            tetromino.MoveAllBlocksDown(row);
        }
    }
    IncrementScore(targetRows.size());
}

Game::TetrominoColor Game::GetRandomTetrominoColor()
{
    int randomIndex = rand() % TetrominoColor::COUNT;
    return static_cast<TetrominoColor>(randomIndex);
}

Tetromino::Shape Game::GetRandomTetrominoShape()
{
    int randomIndex = rand() % Tetromino::Shape::COUNT;
    return static_cast<Tetromino::Shape>(randomIndex);
}

Tetromino *Game::SpawnRandomTetromino(sf::Texture &texture, GridManager &gridManager)
{
    Tetromino::Shape myShape = GetRandomTetrominoShape();
    Tetromino newTetromino(myShape, gridManager, texture, tetrominoColorToTextureCoordinates.at(GetRandomTetrominoColor()));
    tetrominosInTheGame.push_back(newTetromino);
    return &tetrominosInTheGame.back();
}

void Game::Draw(sf::RenderWindow &window)
{
    for (Tetromino &item : tetrominosInTheGame)
        item.Draw(window);
    window.draw(scoreText);
}
