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

    cheak_if_hit_sth = false;

    vel_x = 300;
    vel_y = 300;



//    setPosition(737,629);
//    setPosition(2000,2000);

    Weapon_Change(1);



    shot_blast.setSize(sf::Vector2f(2,2));
    shot_blast.setOrigin(1,1);

    test2.setSize(sf::Vector2f(2,2));
    test2.setOrigin(1,1);
}

void Hero::movement(sf::Time el, std::vector<sf::RectangleShape> walls)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move(-150*el.asSeconds()*2,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move(150*el.asSeconds()*2,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move(0,-150*el.asSeconds()*2);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move(0,150*el.asSeconds()*2);
    }
//    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
//            !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
//            !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
//            !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//    {
//        vel_x = 0;
//        vel_y = 0;
//    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(current_weapon->hit_show == false)
        {
            attack(walls);
            //current_weapon->hit_show;

        }
    }

//    move(vel_x*el.asSeconds(),vel_y*el.asSeconds());

    point_contains_colison(walls);
}

void Hero::attack(std::vector<sf::RectangleShape> walls)
{
    current_weapon->Shot();
    if(current_weapon->hit_show)
    {
        hit_point = current_weapon->hits(walls,getPosition(),getRotation());
        //    test.clear();
//        std::cout << "test";
        cheak_if_hit_sth = true;
        for(auto& hit : hit_point)
        {
            test2.setPosition(hit);
            test.emplace_back(test2);
        }
    }
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
    cheak_if_hit_sth = current_weapon->hit_show;
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

    Hero_sprite.setTextureRect(texture_box);

    texture_box.top = extra_temp.y;
    texture_box.left = extra_temp.x;

    Muzzle_flash.setTextureRect(texture_box);

}

void Hero::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(character_bounds);

    target.draw(Hero_sprite,states);
    if(current_weapon->extra)
        target.draw(Muzzle_flash,states);

    for(auto& el : test)
        target.draw(el);

//    target.draw(test);
//    target.draw(shot_blast);

//    target.draw(test2);
}
