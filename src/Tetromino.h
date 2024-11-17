#include <SFML/Graphics.hpp>

class Tetromino
{
public:
    Tetromino(sf::Texture &texture);
    Tetromino(sf::Color color);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window);

private:
    int shape[4][4];
    sf::Vector2i currentPosition = {5, 0};
    sf::RectangleShape body;
};