#ifndef PISTOL_H
#define PISTOL_H

#include "weapon.h"

class Pistol : public Weapon
{
public:
    Pistol();
    std::vector<sf::Vector2f> hits(std::vector<sf::RectangleShape> walls, sf::Vector2f pos, float rotation);
};

#endif // PISTOL_H
