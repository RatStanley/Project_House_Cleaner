#include "weapon.h"

void Weapon::Reload_Animation()
{
    if(animation_time.asSeconds() > 0.110)
    {
        if(current_frame >= Reload_animation_pos.size()-1)
        {
            current_Frame = idle;
            anim_type = Animation_type::idle;
            current_frame = 0;
            ammo = max_ammo;
        }
        else
        {
            current_Frame = Reload_animation_pos[current_frame];
            current_frame++;
        }
        animation_time = sf::Time::Zero;
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
                anim_type = Animation_type::idle;
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
    if(active == true)
        put_your_weapon_away();
    else if(active == false)
        draw_your_weapon();
}

void Weapon::draw_your_weapon()
{
    if(animation_time.asSeconds() > 0.060)
    {
        if(current_Frame == Change_Animation_pos[0])
        {
            current_Frame = Change_Animation_pos[0];
            anim_type = Animation_type::idle;
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
    if(animation_time.asSeconds() > 0.060)
    {
        if(current_Frame == Change_Animation_pos[1])
        {
            current_Frame = Change_Animation_pos[1];
            anim_type = Animation_type::idle;
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
    animation_time = sf::Time::Zero;
    current_frame = 0;
    active = false;
    anim_type = Animation_type::idle;
}

Weapon::~Weapon()
{

}

void Weapon::Shot()
{
    if(anim_type == Animation_type::idle)
    {
        if(ammo != 0)
        {
            if(anim_type != Animation_type::Shot)
            {
                current_frame = 0;
                ammo--;
                std::cout << ammo << std::endl;
            }
            anim_type = Animation_type::Shot;
        }
    }
}

void Weapon::Change()
{
    if(anim_type == Animation_type::idle)
    {
        if(active)
        {
            current_frame = 0;
        }
        else
        {
            current_frame = 1;
        }
        anim_type = Animation_type::Change;
    }
}

void Weapon::Reload()
{
    if(ammo != max_ammo)
        anim_type = Animation_type::Reload;
}

sf::Vector2i Weapon::Animation(sf::Time tm)
{
    if(anim_type == Animation_type::Shot)
    {
        animation_time=tm;
        Shot_Animation();
    }
    else if(anim_type == Animation_type::Change)
    {
        animation_time+=tm;
        Change_Animation();
    }
    else if(anim_type == Animation_type::Reload)
    {
        animation_time+=tm;
        Reload_Animation();
    }
    else
        return idle;
    return current_Frame;
}



