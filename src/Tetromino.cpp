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

void Tetromino::Update(float deltaTime, sf::RenderWindow & window)
{    
    auto mousePosition = sf::Mouse::getPosition(window) / 4;
    currentGridPosition = GridManager::SnapPositionToGrid(mousePosition);
    printf("\nCurrent grid pos (X:%i;Y:%i)\n", currentGridPosition.x, currentGridPosition.y);
}

void Tetromino::Rotate()
{
    for (auto &block : shape)
    {
        int temp = block.y;
        block.y = block.x;
        block.x = -temp;
    }
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
