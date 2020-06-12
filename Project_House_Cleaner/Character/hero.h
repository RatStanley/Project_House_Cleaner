#ifndef HERO_H
#define HERO_H

#include "character.h"
//#include "Weapons/weapon.h"
#include "Weapons/pistol.h"
#include "Weapons/machinegun.h"
#include "Weapons/shotgun.h"

class Hero : public Character
{
    Weapon *current_weapon;
    Pistol pistol;
    MachineGun MG;
    ShotGun SG;
    weapon_type current_used;
    weapon_type next_weapon;
//    sf::CircleShape shot_blast;
public:
    Hero();
    void movement();
    void attack();
    void reload();
    void Weapon_Change(int id);
    void update_status(sf::Time tm);
};

#endif // HERP_H
