#include "machinegun.h"

MachineGun::MachineGun()
{
    DMG = 10;
    angle = 0;
    rays_count = 1;
    max_ammo = 60;
    ammo = max_ammo;

    idle = sf::Vector2i(0,64);

//    Reload_animation_pos.emplace_back(0,256);//14
//    Reload_animation_pos.emplace_back(48,256);
//    Reload_animation_pos.emplace_back(96,256);

    for(size_t i = 0; i < 14; i++)
        Reload_animation_pos.emplace_back(48*i,256);//14


    shot_animation_pos.emplace_back(0,352);
    shot_animation_pos.emplace_back(48,352);
    shot_animation_pos.emplace_back(96,352);

    muzzle_flash_pos.emplace_back(144,352);
    muzzle_flash_pos.emplace_back(192,352);
    muzzle_flash_pos.emplace_back(240,352);

    Change_Animation_pos.emplace_back(0,160);
    Change_Animation_pos.emplace_back(48,160);

    shot_delay = shot_animation_pos.size()-1;
}
