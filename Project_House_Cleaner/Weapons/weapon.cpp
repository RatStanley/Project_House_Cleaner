#include "weapon.h"

void Weapon::Reload_Animation()
{
    if(animation_time.asSeconds() > 0.110)
    {
        if(current_frame >= Reload_animation_pos.size())
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
        if(current_frame >= shot_animation_pos.size())
        {
            current_Frame = idle;
            if(shot_delay <= current_frame)
            {
                anim_type = Animation_type::idle;
                current_frame = 0;
                extra = false;
            }
            else
            {
                extra = false;
                current_frame++;
            }
        }
        else
        {
            current_Frame = shot_animation_pos[current_frame];
            extra_Frame = muzzle_flash_pos[current_frame];
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

sf::Vector2f Weapon::hit_place(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float M_t = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    float L_t = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4);

    if(M_t != 0 )
    {
        float t = L_t/M_t;
        if(0<=t && t <= 1) //0<=t && t <= 1 && 0<= u && u <= 1
        {
            sf::Vector2f cord(x1+t*(x2-x1),y1+t*(y2-y1));
            sf::Vector2f rogi_offset(x3-x4,y3-y4);
            sf::Vector2f cord_offset(cord.x-x4,cord.y-y4);
            float iloczyn = rogi_offset.x*cord_offset.x+rogi_offset.y*cord_offset.y;
            if(iloczyn > 0)
            {
                return cord;
            }
        }
    }
    return sf::Vector2f(0,0);
}

Weapon::Weapon()
{
    animation_time = sf::Time::Zero;
    current_frame = 0;
    active = false;
    anim_type = Animation_type::idle;
    extra = false;
    hit_show = false;
}

Weapon::~Weapon()
{

}

void Weapon::Shot()
{
    if(anim_type == Animation_type::idle || anim_type == Animation_type::Reload)
    {
        if(ammo != 0)
        {
            if(anim_type != Animation_type::Shot)
            {
                current_frame = 0;
                ammo--;
            }
            anim_type = Animation_type::Shot;
            extra = true;
            shot_sound.setBuffer(shot_Buf);
            shot_sound.play();
            hit_show = true;
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
    if(anim_type == Animation_type::idle)
    {
        if(ammo != max_ammo)
            anim_type = Animation_type::Reload;
    }
}

sf::Vector2i Weapon::Animation(sf::Time tm)
{
    animation_time+=tm;
    if(hit_show)
        hit_show = false;
    if(anim_type == Animation_type::Shot)
    {
//        animation_time=tm;
        Shot_Animation();
    }
    else if(anim_type == Animation_type::Change)
    {
//        animation_time+=tm;
        Change_Animation();
    }
    else if(anim_type == Animation_type::Reload)
    {
//        animation_time+=tm;
        Reload_Animation();
    }
    else
        return idle;
    return current_Frame;
}

sf::Vector2i Weapon::Extra_Animation()
{
    return extra_Frame;
}

void Weapon::Bot_options()
{
    DMG = 5;
    shot_delay = 20;
}




