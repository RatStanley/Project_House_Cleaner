#include "enemy_1.h"

Enemy_1::Enemy_1(sf::Vector2f pos)
{
    hp = 100;
    load_texture("../texture/MainCharacter.png");
    setTextureRect(sf::IntRect(0,0,48,32));
    setPosition(pos);
    setColor(sf::Color::Red);
    character_bounds.setPosition(getPosition());
}

void Enemy_1::attack()
{

}
