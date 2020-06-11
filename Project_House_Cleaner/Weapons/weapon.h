#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Character/character.h"
#include "map.h"

enum class weapon_type
{
    Pistol = 1,
    MachineGun = 2,
    ShotGun = 3
};

class Weapon
{
protected:
    float DMG;
    float angle;
    unsigned int rays_count;
    int max_ammo;
    int current_frame;
    int shot_delay;

    bool animation_end;
    bool shot;
    bool reload;
    bool change_weapon;

    sf::Time animation_time;
    sf::Vector2i current_Frame;
    sf::Vector2i idle;
    std::vector<sf::Vector2i> Reload_animation_pos;
    std::vector<sf::Vector2i> shot_animation_pos;
    std::vector<sf::Vector2i> Change_Animation_pos;
    sf::RectangleShape barrel;

    void Reload_Animation();
    void  Shot_Animation();
    void Change_Animation();
    void draw_your_weapon();
    void put_your_weapon_away();
public:
    Weapon();
    ~Weapon();
    void hit_scan();
    void Shot();
    void Change();
    sf::Vector2i Animation(sf::Time cl);
    bool active;
//    friend void deal_dmg(Character &ch,Map &m);
};

#endif // WEAPON_H
