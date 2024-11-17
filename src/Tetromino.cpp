#include "Tetromino.h"
#include "GridManager.h"

Tetromino::Tetromino(sf::Texture &texture)
{

    body.setTexture(&texture);
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    body.setPosition(GridManager::SnapGridToPosition(sf::Vector2i(5, 0)));
}

Tetromino::Tetromino(sf::Color color)
{
    body.setFillColor(color);
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    body.setPosition(GridManager::SnapGridToPosition(sf::Vector2i(5, 0)));
}

void Tetromino::Update(float deltaTime)
{
}

void Tetromino::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}
