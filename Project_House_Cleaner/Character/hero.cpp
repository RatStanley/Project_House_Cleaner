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

    Hero_sprite.setTexture(texture);
    Muzzle_flash.setTexture(texture);
    Muzzle_flash.setOrigin(24,0);

//    setPosition(737,629);
//    shot_blast.setRadius(12);
//    shot_blast.setOrigin(6,6);
//    shot_blast.setFillColor(sf::Color(255,255,0,50));
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
    sf::Vector2i extra_temp;

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
    if(current_weapon->extra)
    {
        extra_temp = current_weapon->Extra_Animation();
    }

    texture_box.top = temp.y;
    texture_box.left = temp.x;

//    setTextureRect(texture_box);
    Hero_sprite.setTextureRect(texture_box);

    texture_box.top = extra_temp.y;
    texture_box.left = extra_temp.x;

    Muzzle_flash.setTextureRect(texture_box);
}

void Hero::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(Hero_sprite,states);
    if(current_weapon->extra)
        target.draw(Muzzle_flash,states);
}
