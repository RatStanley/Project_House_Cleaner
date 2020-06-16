#include "shotgun.h"

ShotGun::ShotGun()
{
    DMG = 10;
    angle = 0;
    rays_count = 8;
    max_ammo = 7;
    ammo = max_ammo;
    shot_delay = 20;
    idle = sf::Vector2i(0,32);

    for(size_t i = 0; i < 6; i++)
    {
        Reload_animation_pos.emplace_back(48*i,224); // do zmiany
    }


    shot_animation_pos.emplace_back(0,320);
    shot_animation_pos.emplace_back(48,320);
    shot_animation_pos.emplace_back(96,320);

    muzzle_flash_pos.emplace_back(144,320);
    muzzle_flash_pos.emplace_back(192,320);
    muzzle_flash_pos.emplace_back(240,320);


    Change_Animation_pos.emplace_back(0,128);
    Change_Animation_pos.emplace_back(48,128);

    if (!shot_Buf.loadFromFile("../sounds/shotgun-mossberg.wav"))
            std::cout << "problem";
    shot_sound.setBuffer(shot_Buf);
}

void ShotGun::Reload_Animation()
{
    if(animation_time.asSeconds() > 0.110)
    {
        if(current_frame >= Reload_animation_pos.size() && ammo == max_ammo)
        {
            current_Frame = idle;
            anim_type = Animation_type::idle;
            current_frame = 0;
        }
        else if(current_frame == 4 && ammo != max_ammo)
        {
            current_Frame = Reload_animation_pos[current_frame];
            ammo++;
            if(ammo != max_ammo)
                current_frame = 2;
            std::cout <<ammo << std::endl;
        }
        else
        {
            current_Frame = Reload_animation_pos[current_frame];
            current_frame++;
        }
        animation_time = sf::Time::Zero;
    }
}
