#include "machinegun.h"

MachineGun::MachineGun()
{
    DMG = 10;
    angle = 0;
    rays_count = 1;
    max_ammo = 7;


    idle = sf::Vector2i(0,64);

    Reload_animation_pos.emplace_back(0,336);
    Reload_animation_pos.emplace_back(32,336);
    Reload_animation_pos.emplace_back(64,336);

    shot_animation_pos.emplace_back(0,352);
    shot_animation_pos.emplace_back(48,352);
    shot_animation_pos.emplace_back(96,352);

    Change_Animation_pos.emplace_back(0,160);
    Change_Animation_pos.emplace_back(48,160);

    shot_delay = shot_animation_pos.size()-1;
}
