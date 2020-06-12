#include "pistol.h"

Pistol::Pistol()
{
    DMG = 10;
    angle = 0;
    rays_count = 1;
    max_ammo = 7;
    ammo = max_ammo;
    shot_delay = 10;
    idle = sf::Vector2i(0,0);

    Reload_animation_pos.emplace_back(0,192);
    Reload_animation_pos.emplace_back(48,192);
    Reload_animation_pos.emplace_back(96,192);
    Reload_animation_pos.emplace_back(144,192);
    Reload_animation_pos.emplace_back(192,192);



    shot_animation_pos.emplace_back(0,288);
    shot_animation_pos.emplace_back(48,288);
    shot_animation_pos.emplace_back(96,288);

    Change_Animation_pos.emplace_back(0,96);
    Change_Animation_pos.emplace_back(48,96);
}