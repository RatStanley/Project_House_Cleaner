#include "weapon.h"

void Weapon::Reload_Animation()
{
    int i = 0;
    for(auto& frame : Reload_animation_pos)
    {
        animation_end = true;
        if(frame == *Reload_animation_pos.end())
        {
            animation_end = false;
            animation_time = sf::Time::Zero;
        }
        if(animation_time.asMilliseconds() >150*i)
            current_Frame =  frame;
        i++;
    }
}

void Weapon::Shot_Animation()
{
//    int i = 0;
//    for(auto& frame : shot_animation_pos)
//    {
////        animation_end = true;
////        if(frame == *shot_animation_pos.end())
////        {
////            animation_end = false;
////            shot = false;
////        }
//        if(animation_time.asSeconds() <0.15*i && animation_time.asSeconds() <0.15*(i+1))
//            current_Frame =  frame;
//        if(animation_time.asSeconds() >0.60*i)
//        {
//            shot = false;
//            animation_time = sf::Time::Zero;
//        }
//        i++;
//    }
//    if(animation_time.asSeconds() < 0.0010 && animation_time.asSeconds() >= 0)
//        current_Frame = shot_animation_pos[0];
//    if(animation_time.asSeconds() < 0.0020 && animation_time.asSeconds() >= 0.0010)
//        current_Frame = shot_animation_pos[1];
//    if(animation_time.asSeconds() < 0.0030 && animation_time.asSeconds() >= 0.0020)
//        current_Frame = shot_animation_pos[2];
//    if(animation_time.asSeconds() >= 0.0030)
//    {
//        current_Frame = idle;
//        shot = false;
//        animation_time = sf::Time::Zero;
//    }
    if(animation_time.asSeconds() < 0.0010 && animation_time.asSeconds() >= 0)
        current_Frame = shot_animation_pos[0];
    if(animation_time.asSeconds() < 0.0020 && animation_time.asSeconds() >= 0.0010)
        current_Frame = shot_animation_pos[1];
    if(animation_time.asSeconds() < 0.0030 && animation_time.asSeconds() >= 0.0020)
        current_Frame = shot_animation_pos[2];
    if(animation_time.asSeconds() >= 0.0030)
    {
        current_Frame = idle;
        shot = false;
        animation_time = sf::Time::Zero;
    }
}

Weapon::Weapon()
{
    shot = false;
    reload = false;
    animation_time = sf::Time::Zero;
}

Weapon::~Weapon()
{

}

void Weapon::Shot()
{
    shot = true;
}

sf::Vector2i Weapon::Animation(sf::Time tm)
{
    std::cout << animation_time.asSeconds() << std::endl;
    if(shot)
    {
        animation_time+=tm;
        Shot_Animation();
    }
    else
        return idle;
    return current_Frame;
}



