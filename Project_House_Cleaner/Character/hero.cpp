#include "hero.h"

#include <iostream>

Hero::Hero()
{
    load_texture("../texture/MainCharacter.png");
    current_used = weapon_type::Pistol;
    texture_box.width = 48;
    texture_box.height = 32;
}

void Hero::movement()
{

}

void Hero::attack()
{

    std::cout<<"strzal" << std::endl;
    //    setTextureRect()
    if(current_used == weapon_type::Pistol)
    {
        pistol.Shot();
    }
    if(current_used == weapon_type::MachineGun)
    {

    }
    if(current_used == weapon_type::ShotGun)
    {

    }
}

void Hero::update_status(sf::Time tm)
{

    sf::Vector2i temp;
    if(current_used == weapon_type::Pistol)
    {
        temp = pistol.Animation(tm);
    }
    if(current_used == weapon_type::MachineGun)
    {

    }
    if(current_used == weapon_type::ShotGun)
    {

    }
    texture_box.top = temp.y;
    texture_box.left = temp.x;
    setTextureRect(texture_box);
}
