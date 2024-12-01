#include <time.h>
#include "Game.h"

Game::Game()
{
    srand(time(NULL));
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
            tetromino.MoveDown();
        }
    }
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
}
