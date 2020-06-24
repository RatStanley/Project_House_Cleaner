#include "character.h"

#include <math.h>
#include <iostream>

void Character::load_texture(const char* file)
{
    if (!texture.loadFromFile(file))
    {
        std::cout << "Could not load texture" << std::endl;
    }
    setTexture(texture);
    setScale(3.5,3.5);
    setTextureRect(sf::IntRect(0,0,48,32));
    setPosition(600,600);
    setOrigin(24,16);

    test.setSize(sf::Vector2f(10,10));
    test.setOrigin(5,5);
}

void Character::face_to(sf::Vector2f aim)
{
    float angle = 0;
    sf::Vector2f pos = aim;
    sf::Vector2f off_Set_Point;

    off_Set_Point.x = aim.x;
    off_Set_Point.y = aim.y - 21;


    if(aim.x < getPosition().x && aim.y >= getPosition().y)
    {
        angle = 90-atan2(aim.y - getPosition().y,  getPosition().x - aim.x)* 180 / M_PI;
    }
    else if(aim.x <= getPosition().x && aim.y < getPosition().y)
    {
        angle = atan2(getPosition().y - aim.y, getPosition().x - aim.x)* 180 / M_PI +90;
    }
    else if(aim.x > getPosition().x && aim.y <= getPosition().y)
    {
        angle =90- atan2(getPosition().y - aim.y,aim.x - getPosition().x)* 180 / M_PI +180;
    }
    else if(aim.x >= getPosition().x && aim.y > getPosition().y)
    {
        angle = atan2(aim.y - getPosition().y,aim.x - getPosition().x)* 180 / M_PI +270;
    }

    float angle2 = (getRotation()) * (M_PI/180);

    float x4 = cos(angle2)*(off_Set_Point.x - pos.x)-sin(angle2)*(off_Set_Point.y-pos.y) + pos.x;
    float y4 = sin(angle2)*(off_Set_Point.x - pos.x)+cos(angle2)*(off_Set_Point.y - pos.y) + pos.y;

    aim.y = y4;
    aim.x = x4;

    if(aim.x < getPosition().x && aim.y >= getPosition().y) // korekta offsetu broni
    {
        angle2 = 90-atan2(aim.y - getPosition().y,  getPosition().x - aim.x)* 180 / M_PI;
    }
    else if(aim.x <= getPosition().x && aim.y < getPosition().y)
    {
        angle2 = atan2(getPosition().y - aim.y, getPosition().x - aim.x)* 180 / M_PI +90;
    }
    else if(aim.x > getPosition().x && aim.y <= getPosition().y)
    {
        angle2 =90- atan2(getPosition().y - aim.y,aim.x - getPosition().x)* 180 / M_PI +180;
    }
    else if(aim.x >= getPosition().x && aim.y > getPosition().y)
    {
        angle2 = atan2(aim.y - getPosition().y,aim.x - getPosition().x)* 180 / M_PI +270;
    }

    setRotation(angle-90+(angle - angle2));
}

void Character::hit_hp(float dmg)
{
    hp-=dmg;
    if(hp <= 0)
        is_dead = true;
}

Character::Character()
{
    character_bounds.setSize(sf::Vector2f(60,60));
    character_bounds.setOrigin(30,30);
    character_bounds.setFillColor(sf::Color::Red);
    is_dead = false;
}

bool Character::colision(std::vector<sf::RectangleShape> walls)
{
    character_bounds.setPosition(getPosition());
    sf::Vector2f points[] =
    {
        sf::Vector2f(character_bounds.getGlobalBounds().left,character_bounds.getGlobalBounds().top),
        sf::Vector2f(character_bounds.getGlobalBounds().left + character_bounds.getGlobalBounds().width,character_bounds.getGlobalBounds().top),
        sf::Vector2f(character_bounds.getGlobalBounds().left,character_bounds.getGlobalBounds().top + character_bounds.getGlobalBounds().height),
        sf::Vector2f(character_bounds.getGlobalBounds().left + character_bounds.getGlobalBounds().width,character_bounds.getGlobalBounds().top + character_bounds.getGlobalBounds().height)
    };
    /// 1==2
    /// |  |
    /// 3==4
    for(auto& point : points)
    {
        for(auto& wall : walls)
        {
            if(wall.getGlobalBounds().contains(point))
            {
                setPosition(pr_pos);
                return true;
            }
        }
    }
    pr_pos = getPosition();
    wall_ = false;
    return false;
}

void Character::point_contains_colison(std::vector<sf::RectangleShape> walls)
{
    character_bounds.setPosition(getPosition());
    sf::Vector2f points[] =
    {
        sf::Vector2f(character_bounds.getGlobalBounds().left,character_bounds.getGlobalBounds().top),
        sf::Vector2f(character_bounds.getGlobalBounds().left + character_bounds.getGlobalBounds().width,character_bounds.getGlobalBounds().top),
        sf::Vector2f(character_bounds.getGlobalBounds().left,character_bounds.getGlobalBounds().top + character_bounds.getGlobalBounds().height),
        sf::Vector2f(character_bounds.getGlobalBounds().left + character_bounds.getGlobalBounds().width,character_bounds.getGlobalBounds().top + character_bounds.getGlobalBounds().height)
    };
    /// 1==2
    /// |  |
    /// 3==4
    bool next = false;
    for(auto& point : points)
    {
        for(auto& wall : walls)
        {
            if(wall.getGlobalBounds().contains(point))
            {
                setPosition(pr_pos);
                next = true;
                break;
            }
        }
        if(next)
            break;
    }
    pr_pos = getPosition();
}
