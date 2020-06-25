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

    sf::Sprite Hero_sprite;
    sf::Sprite Muzzle_flash;

public:
    Hero();
    void movement(sf::Time el, std::vector<sf::RectangleShape> walls);
    void attack(std::vector<sf::RectangleShape> walls);
    void reload();
    void Weapon_Change(int id);
    void update_status(sf::Time tm);
    void hit_Scan(std::vector<sf::RectangleShape> walls);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    float dmg(){return current_weapon->DMG;};
    std::string info_to_hud(std::string hud);
    void new_map(){hp = 100;}
};

#endif // HERP_H
