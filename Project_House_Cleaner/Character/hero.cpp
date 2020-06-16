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

    vel_x = 300;
    vel_y = 300;



    setPosition(737,629);
//    shot_blast.setRadius(12);
//    shot_blast.setOrigin(6,6);
//    shot_blast.setFillColor(sf::Color(255,255,0,50));
}

void Hero::movement(sf::Time el, std::vector<sf::RectangleShape> walls)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move(-150*el.asSeconds()*2,0);
        vel_x = -300;
//        col_4(walls);
//        colision(walls);
//        colision(walls);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move(150*el.asSeconds()*2,0);
//        vel_x = 300;
//        col_3(walls);
//        colision(walls);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
//        vel_y = -300;
//        col_2(walls);
        move(0,-150*el.asSeconds()*2);
//        colision(walls);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
//        vel_y = 300;

//        colision(walls);
        move(0,150*el.asSeconds()*2);
//        colision(walls);
//        col_1(walls);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        vel_x = 0;
        vel_y = 0;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        attack();

//    move(vel_x*el.asSeconds(),vel_y*el.asSeconds());

    point_contains_colison(walls);
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
//    get

//    character_bounds.setPosition(getPosition().x-35,getPosition().y-35);
//    test.setSize(sf::Vector2f(getGlobalBounds().width,getGlobalBounds().height));
//    test.setOrigin(getGlobalBounds().width/2,getGlobalBounds().height/2);
}

void Hero::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

//    target.draw(character_bounds);

    target.draw(Hero_sprite,states);
    if(current_weapon->extra)
        target.draw(Muzzle_flash,states);
}
