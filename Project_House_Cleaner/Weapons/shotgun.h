#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapons/weapon.h"

class ShotGun : public Weapon
{


public:
    ShotGun();
    void Reload_Animation();
    std::vector<sf::Vector2f> hits(std::vector<sf::RectangleShape> walls, sf::Vector2f pos, float rotation);
};

#endif // SHOTGUN_H
