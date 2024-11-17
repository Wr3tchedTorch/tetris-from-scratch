#include "Tetromino.h"
#include "GridManager.h"

Tetromino::Tetromino(sf::Texture &texture, TetrominoShape shape)
{
    this->shape = TetrominoShapes.at(shape);
    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(CELL_SIZE, CELL_SIZE)));
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
}

Tetromino::Tetromino(sf::Color color, TetrominoShape shape)
{
    this->shape = TetrominoShapes.at(shape);
    body.setFillColor(color);
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
}

void Tetromino::Update(float deltaTime)
{
}

void Tetromino::Rotate()
{
}

void Tetromino::Draw(sf::RenderWindow &window)
{
    for (auto block : shape)
    {
        int xGridPosition = currentGridPosition.x + block.x;
        int yGridPosition = currentGridPosition.y + block.y;

        body.setPosition(GridManager::GridToPosition(sf::Vector2i(xGridPosition, yGridPosition)));
        window.draw(body);
    }
}
