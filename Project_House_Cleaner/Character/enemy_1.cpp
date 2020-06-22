#include "enemy_1.h"

void Enemy_1::draw_a_dir()
{
    int pr_dir = dir;
    dir = rand()%4;
    if(dir == 0 && dir != pr_dir)
    {
        vel_x = 300;
        vel_y = 0;
    }
    else if(dir == 1 && dir != pr_dir)
    {
        vel_x = -300;
        vel_y = 0;
    }
    else if(dir == 2 && dir != pr_dir)
    {
        vel_x = 0;
        vel_y = 300;
    }
    else if(dir == 3 && dir != pr_dir)
    {
        vel_x = 0;
        vel_y = -300;
    }
}

Enemy_1::Enemy_1(sf::Vector2f pos)
{
    hp = 100;
    load_texture("../texture/MainCharacter.png");
    setTextureRect(sf::IntRect(0,0,48,32));
    setPosition(pos);
    setColor(sf::Color::Red);
    character_bounds.setPosition(getPosition());
    dir = 5;

    draw_a_dir();

}

void Enemy_1::attack()
{

}

void Enemy_1::update_status(sf::Time tm)
{
    move(vel_x*tm.asSeconds(),vel_y*tm.asSeconds());
}

void Enemy_1::change_dir(std::vector<sf::RectangleShape> walls)
{
    if(colision(walls))
        draw_a_dir();
}
