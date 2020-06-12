#include "hero.h"

#include <iostream>

Hero::Hero()
{
    load_texture("../texture/MainCharacter.png");
    current_used = weapon_type::Pistol;
    texture_box.width = 48;
    texture_box.height = 32;
    current_weapon = &pistol;
    next_weapon = current_used;
//    shot_blast.setRadius(120);
}

void Hero::movement()
{

}

void Hero::attack()
{
    current_weapon->Shot();
}

void Hero::reload()
{
    current_weapon->Reload();
}

void Hero::Weapon_Change(int id)
{
    if(id == 1)
    {
        next_weapon = weapon_type::Pistol;
    }
    else if(id == 2)
    {
        next_weapon = weapon_type::ShotGun;
    }
    else if(id == 3)
    {
        next_weapon = weapon_type::MachineGun;
    }
    if(current_used != next_weapon)
        current_weapon->Change();
}

void Hero::update_status(sf::Time tm)
{
    sf::Vector2i temp;
    if(current_used != next_weapon && current_weapon->active == false)
    {
        if(next_weapon == weapon_type::Pistol)
        {
            current_used = weapon_type::Pistol;
            current_weapon = &pistol;
            current_weapon->Change();
        }
        else if(next_weapon == weapon_type::ShotGun)
        {
            current_used = weapon_type::ShotGun;
            current_weapon = &SG;
            current_weapon->Change();
        }
        else if(next_weapon == weapon_type::MachineGun)
        {
            current_used = weapon_type::MachineGun;
            current_weapon = &MG;
            current_weapon->Change();
        }
    }
    temp = current_weapon->Animation(tm);
    texture_box.top = temp.y;
    texture_box.left = temp.x;
    setTextureRect(texture_box);
}
