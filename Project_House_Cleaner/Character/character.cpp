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
//    load_texture("../texture/MainCharacter.png");
//    hit_box = sf::FloatRect(getGlobalBounds().left-60,getGlobalBounds().left-60,getGlobalBounds().width+120,getGlobalBounds()+120);

}

void Character::colision(sf::RectangleShape &el)
{
    if(getGlobalBounds().intersects(el.getGlobalBounds()))
    {
        if(getGlobalBounds().left+getGlobalBounds().width*0.9 > el.getGlobalBounds().left &&
                getGlobalBounds().left < el.getGlobalBounds().left+el.getGlobalBounds().width*0.9 &&
                getGlobalBounds().top < el.getGlobalBounds().top)
        {
            setPosition(getGlobalBounds().left, el.getGlobalBounds().top-getGlobalBounds().height);
            vel_y = 0;
        }
        else if(getGlobalBounds().top + getGlobalBounds().height*0.9 > el.getGlobalBounds().top &&
                 getGlobalBounds().top < el.getGlobalBounds().top + el.getGlobalBounds().height*0.9 &&
                 getGlobalBounds().left < el.getGlobalBounds().left)
         {
             setPosition(el.getGlobalBounds().left - getGlobalBounds().width, getGlobalBounds().top);
             vel_x = 0;
         }
        else if(getGlobalBounds().top + getGlobalBounds().height*0.9 > el.getGlobalBounds().top &&
                 getGlobalBounds().top < el.getGlobalBounds().top + el.getGlobalBounds().height*0.9 &&
                 getGlobalBounds().left + getGlobalBounds().width/2 > el.getGlobalBounds().left + el.getGlobalBounds().width)
         {
             setPosition(el.getGlobalBounds().left + el.getGlobalBounds().width, getGlobalBounds().top);
             vel_x = 0;
         }
        else if(getGlobalBounds().left+getGlobalBounds().width > el.getGlobalBounds().left &&
                getGlobalBounds().left < el.getGlobalBounds().left+el.getGlobalBounds().width &&
                getGlobalBounds().top > el.getGlobalBounds().top)
        {
            setPosition(getGlobalBounds().left, el.getGlobalBounds().top+el.getGlobalBounds().height);
            vel_y = 0;
        }
    }
}
