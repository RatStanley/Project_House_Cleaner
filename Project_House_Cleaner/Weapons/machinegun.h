#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "weapon.h"

class MachineGun : public Weapon
{
public:
    MachineGun();
    std::vector<sf::Vector2f> hits(std::vector<sf::RectangleShape> walls, sf::Vector2f pos, float rotation);
};

#endif // MACHINEGUN_H
