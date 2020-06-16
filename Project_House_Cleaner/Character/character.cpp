#include "character.h"

#include <math.h>


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
}

void Character::face_to(sf::Vector2f aim)
{
    float angle = 0;
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
    setRotation(angle-90);
}

Character::Character()
{
    character_bounds.setSize(sf::Vector2f(70,70));
    character_bounds.setOrigin(35,35);
    character_bounds.setFillColor(sf::Color::Red);
}

void Character::colision(std::vector<sf::RectangleShape> walls)
{
    character_bounds.setPosition(getPosition());
//    character_bounds.setPosition(getPosition().x-35,getPosition().y-35);

    for(auto& wall : walls)
    {
        if(character_bounds.getGlobalBounds().intersects(wall.getGlobalBounds()))
        {
//            std::cout << "test";
            if(character_bounds.getGlobalBounds().left+character_bounds.getGlobalBounds().width > wall.getGlobalBounds().left &&
                    character_bounds.getGlobalBounds().left < wall.getGlobalBounds().left+wall.getGlobalBounds().width &&
                    character_bounds.getGlobalBounds().top  + getOrigin().y < wall.getGlobalBounds().top)
            {
                setPosition(character_bounds.getGlobalBounds().left+35, wall.getGlobalBounds().top-character_bounds.getGlobalBounds().height+35);
//                vel_y = 0;
                std::cout << "1" << std::endl;
            }
            else if(character_bounds.getGlobalBounds().left+character_bounds.getGlobalBounds().width > wall.getGlobalBounds().left &&
                    character_bounds.getGlobalBounds().left < wall.getGlobalBounds().left+wall.getGlobalBounds().width &&
                    character_bounds.getGlobalBounds().top > wall.getGlobalBounds().top)
            {
                setPosition(character_bounds.getGlobalBounds().left+35, wall.getGlobalBounds().top+wall.getGlobalBounds().height+35);
//                vel_y = 0;
                std::cout << "4" << std::endl;
            }
//            else if(character_bounds.getGlobalBounds().top + character_bounds.getGlobalBounds().height*0.9 > wall.getGlobalBounds().top &&
//                    character_bounds.getGlobalBounds().top < wall.getGlobalBounds().top + wall.getGlobalBounds().height*0.9 &&
//                    character_bounds.getGlobalBounds().left < wall.getGlobalBounds().left)
//            {
//                setPosition(wall.getGlobalBounds().left - character_bounds.getGlobalBounds().width+35, character_bounds.getGlobalBounds().top+35);
////                vel_x = 0;
//                std::cout << "2" << std::endl;
//            }
//            else if(character_bounds.getGlobalBounds().top + character_bounds.getGlobalBounds().height*0.9 > wall.getGlobalBounds().top &&
//                    character_bounds.getGlobalBounds().top < wall.getGlobalBounds().top + wall.getGlobalBounds().height*0.9 &&
//                    character_bounds.getGlobalBounds().left + character_bounds.getGlobalBounds().width/2 > wall.getGlobalBounds().left + wall.getGlobalBounds().width)
//            {
//                setPosition(wall.getGlobalBounds().left + wall.getGlobalBounds().width +35, character_bounds.getGlobalBounds().top+35);
////                vel_x = 0;
//                std::cout << "3" << std::endl;
//            }

////            if(vel_x == 0 && vel_y == 0)
               break;
        }
    }
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
//                std::cout << "tak" << std::endl;
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
