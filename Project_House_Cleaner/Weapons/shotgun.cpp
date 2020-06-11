#include "shotgun.h"

ShotGun::ShotGun()
{
    DMG = 10;
    angle = 0;
    rays_count = 8;
    max_ammo = 7;
    shot_delay = 12;
    idle = sf::Vector2i(0,32);

    Reload_animation_pos.emplace_back(0,336); // do zmiany
    Reload_animation_pos.emplace_back(32,336);
    Reload_animation_pos.emplace_back(64,336);

    shot_animation_pos.emplace_back(0,320);
    shot_animation_pos.emplace_back(48,320);
    shot_animation_pos.emplace_back(96,320);

    Change_Animation_pos.emplace_back(0,128);
    Change_Animation_pos.emplace_back(48,128);
}
