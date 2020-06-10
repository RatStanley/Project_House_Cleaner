#include "pistol.h"

Pistol::Pistol()
{
    DMG = 10;
    angle = 0;
    rays_count = 1;
    max_ammo = 7;

    idle = sf::Vector2i(0,0);

    Reload_animation_pos.emplace_back(0,336);
    Reload_animation_pos.emplace_back(32,336);
    Reload_animation_pos.emplace_back(64,336);

    shot_animation_pos.emplace_back(0,288);
    shot_animation_pos.emplace_back(48,288);
    shot_animation_pos.emplace_back(96,288);

//        shot_animation_pos.emplace_back(480,0);
//        shot_animation_pos.emplace_back(480,32);
//        shot_animation_pos.emplace_back(480,64);
}

