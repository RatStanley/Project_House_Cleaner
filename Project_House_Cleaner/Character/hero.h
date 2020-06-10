#ifndef HERO_H
#define HERO_H

#include "character.h"
#include "Weapons/pistol.h"


class Hero : public Character
{
    Pistol pistol;

    weapon_type current_used;

public:
    Hero();
    void movement();
    void attack();
    void Weapon_Change();
    void update_status(sf::Time tm);
};

#endif // HERP_H
