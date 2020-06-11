#include "weapon.h"

void Weapon::Reload_Animation()
{
    int i = 0;
    for(auto& frame : Reload_animation_pos)
    {
        if(frame == *Reload_animation_pos.end())
        {
            animation_time = sf::Time::Zero;
        }
        if(animation_time.asMilliseconds() >150*i)
            current_Frame =  frame;
        i++;
    }
}

void Weapon::Shot_Animation()
{
    if(animation_time.asSeconds() > 0.030)
    {
        if(current_frame >= shot_animation_pos.size()-1)
        {
            current_Frame = idle;
            if(shot_delay <= current_frame)
            {
                shot = false;
                current_frame = 0;
            }
            else
                current_frame++;
        }
        else
        {
            current_Frame = shot_animation_pos[current_frame];
            current_frame++;
        }
        animation_time = sf::Time::Zero;
    }
}

void Weapon::Change_Animation()
{
    change_weapon = true;
    if(active == true)
        put_your_weapon_away();
    else if(active == false)
        draw_your_weapon();
}

void Weapon::draw_your_weapon()
{
    if(animation_time.asSeconds() > 0.050)
    {
        if(current_Frame == Change_Animation_pos[0])
        {
            current_Frame = Change_Animation_pos[0];
            change_weapon = false;
            current_frame = 0;
            active = true;
        }
        else
        {
            current_Frame = Change_Animation_pos[current_frame];
            current_frame--;
        }
        animation_time = sf::Time::Zero;
    }
}

void Weapon::put_your_weapon_away()
{
    if(animation_time.asSeconds() > 0.050)
    {
        if(current_Frame == Change_Animation_pos[1])
        {
            current_Frame = Change_Animation_pos[1];
            change_weapon = false;
            current_frame = 0;
            active = false;
        }
        else
        {
            current_Frame = Change_Animation_pos[current_frame];
            current_frame++;
        }
        animation_time = sf::Time::Zero;
    }
}

Weapon::Weapon()
{
    shot = false;
    reload = false;
    animation_time = sf::Time::Zero;
    current_frame = 0;
    active = false;
    change_weapon = false;
}

Weapon::~Weapon()
{

}

void Weapon::Shot()
{
        if(shot == false)
            current_frame = 0;
        shot = true;
}

void Weapon::Change()
{
        if(active)
        {
            current_frame = 0;
        }
        else
        {
            current_frame = 1;
        }
        change_weapon = true;
}

sf::Vector2i Weapon::Animation(sf::Time tm)
{
    if(shot)
    {
        animation_time=tm;
        Shot_Animation();
    }
    else if(change_weapon)
    {
        animation_time+=tm;
        Change_Animation();
    }
    else
        return idle;
    return current_Frame;
}



