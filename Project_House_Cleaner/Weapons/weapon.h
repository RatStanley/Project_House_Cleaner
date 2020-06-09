#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Character/character.h"
#include "map.h"

class Weapon
{
    float DMG;
    float angle;
    unsigned int rays_count;
    int max_ammo;
    sf::Vector2i idle;
    sf::Vector2i *Reload_animation_pos;
    sf::Vector2i *shot_animation_pos;
    sf::RectangleShape *barrel;
public:
    Weapon();
    ~Weapon();
    void hit_scan();
    void Reload_Animation();
    void Shot_Animation();
    friend void deal_dmg(Character &ch,Map &m);
};

#endif // WEAPON_H
