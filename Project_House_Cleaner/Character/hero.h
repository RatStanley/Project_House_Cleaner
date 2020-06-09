#ifndef HERO_H
#define HERO_H

#include "character.h"

class Hero : public Character
{
public:
    Hero();
    void movement();
    void attack();
    void Weapon_Change();
};

#endif // HERP_H
