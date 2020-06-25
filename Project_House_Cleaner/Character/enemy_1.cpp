#include "enemy_1.h"
#include <math.h>

void Enemy_1::draw_a_dir()
{
    int pr_dir = dir;
    dir = rand()%4;
    if(dir == 0 && dir != pr_dir)
    {
        vel_x = 300;
        vel_y = 0;
        setRotation(180);
    }
    else if(dir == 1 && dir != pr_dir)
    {
        vel_x = -300;
        vel_y = 0;
        setRotation(0);
    }
    else if(dir == 2 && dir != pr_dir)
    {
        vel_x = 0;
        vel_y = 300;
        setRotation(270);
    }
    else if(dir == 3 && dir != pr_dir)
    {
        vel_x = 0;
        vel_y = -300;
        setRotation(90);
    }
}

Enemy_1::Enemy_1(sf::Vector2f pos,std::vector<sf::RectangleShape> walls)
{
    hp = 75;
    load_texture("../Resources/texture/MainCharacter.png");
    setPosition(pos);
    character_bounds.setPosition(getPosition());
    dir = 5;
    this->walls = walls;
    walls_count = this->walls.size();
    this->walls.emplace_back(sf::RectangleShape(sf::Vector2f(2,2)));
    draw_a_dir();
    follow = false;
    see_hero = false;
    texture_box = sf::IntRect(0,0,48,32);
    pistol.Bot_options();
    dmg = pistol.DMG;
    cheak_if_hit_sth = false;
}

void Enemy_1::attack()
{
    pistol.Shot();
    if(pistol.hit_show)
    {
        hit_point = pistol.hits(walls,getPosition(),getRotation());
        cheak_if_hit_sth = true;
    }
    if(pistol.ammo == 0)
    {
        pistol.Reload();
    }
}

void Enemy_1::update_status(sf::Time tm)
{
    sf::Vector2i animation_temp;
    float pos_to_hero_pos = pow(getPosition().x - hero_pos.x,2) + pow(getPosition().y - hero_pos.y,2);
    cheak_if_hit_sth = pistol.hit_show;

    if(pos_to_hero_pos > 90000 && see_hero)
    {
        go_to_hero_pos(tm);
    }
    else if(pos_to_hero_pos < 90000 && see_hero)
        attack();
    else
    {
        move(vel_x*tm.asSeconds(), vel_y*tm.asSeconds());
        change_dir();
    }

    if(see_hero)
    {
        face_to(hero_pos);
    }
    animation_temp = pistol.Animation(tm);
    texture_box.top = animation_temp.y;
    texture_box.left = animation_temp.x;
    setTextureRect(texture_box);
}

//void Enemy_1::hear_shot(sf::Vector2f hero_pos_)
//{
//    if(pow(getPosition().x - hero_pos_.x,2) + pow(getPosition().y - hero_pos_.y,2) < 500000 && follow == false)
//    {
//        follow = true;
////        setColor(sf::Color::Green);
//    }

//    if(pow(getPosition().x - hero_pos_.x,2) + pow(getPosition().y - hero_pos_.y,2) < 250000)
//        setColor(sf::Color::Green);
//}

void Enemy_1::change_dir()
{
    if(colision(walls) && see_hero == false && follow == false )
        draw_a_dir();
}

void Enemy_1::see_hero_()
{

        bool see = false;
        float x1 = getPosition().x;
        float y1 = getPosition().y;
        float x2 = hero_pos.x;
        float y2 = hero_pos.y;
//        for(auto& wall : walls)
        for(size_t i = 0; i < walls_count; i++)
        {
            std::pair<sf::Vector2f, sf::Vector2f> wall_[4];
            wall_[0] = {
                sf::Vector2f(walls[i].getGlobalBounds().left,walls[i].getGlobalBounds().top),                             //lt
                sf::Vector2f(walls[i].getGlobalBounds().left+walls[i].getGlobalBounds().width,walls[i].getGlobalBounds().top)  //pt
            };
            wall_[1] = {
                sf::Vector2f(walls[i].getGlobalBounds().left+walls[i].getGlobalBounds().width,walls[i].getGlobalBounds().top),  //pt
                sf::Vector2f(walls[i].getGlobalBounds().left+walls[i].getGlobalBounds().width,walls[i].getGlobalBounds().top + walls[i].getGlobalBounds().height)//pd
            };
            wall_[2] = {
                sf::Vector2f(walls[i].getGlobalBounds().left+walls[i].getGlobalBounds().width,walls[i].getGlobalBounds().top + walls[i].getGlobalBounds().height),//pd
                sf::Vector2f(walls[i].getGlobalBounds().left,walls[i].getGlobalBounds().top + walls[i].getGlobalBounds().height)//ld
            };
            wall_[3] = {
                sf::Vector2f(walls[i].getGlobalBounds().left,walls[i].getGlobalBounds().top),
                sf::Vector2f(walls[i].getGlobalBounds().left,walls[i].getGlobalBounds().top + walls[i].getGlobalBounds().height)
            };
            for(auto& one : wall_)
            {
                float x3 = one.first.x;
                float y3 = one.first.y;
                float x4 = one.second.x;
                float y4 = one.second.y;

                float M_t = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
                float L_t = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4);
                float l_u = (x1-x2)*(y1-y3)-(y1-y2)*(x1-x3);
                float m_u = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
                if(M_t != 0 && m_u != 0 )
                {
                    float t = L_t/M_t;
                    float u = -l_u/m_u;
                    if(0<=t && t <= 1 && 0<= u && u <= 1)
                    {
                        see = true;
                        see_hero = false;
                        break;
                    }
                }
            }
            if(see)
                break;
        }
        if(see == false)
        {
            see_hero = true;
        }

}

void Enemy_1::new_hero_pos(sf::Vector2f hero_pos_, sf::RectangleShape hero_rec)
{
    hero_pos = hero_pos_;
    walls[walls_count] = hero_rec;
}

void Enemy_1::go_to_hero_pos(sf::Time tm)
{
    if(see_hero || follow)
    {
        move((hero_pos.x-getPosition().x)*tm.asSeconds(), (hero_pos.y-getPosition().y)*tm.asSeconds());
    }
    else
        move(vel_x*tm.asSeconds(),vel_y*tm.asSeconds());
}
