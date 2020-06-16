#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character/character.h"
#include "map.h"

enum class weapon_type
{
    Pistol,
    MachineGun,
    ShotGun
};

enum class Animation_type
{
    Reload,
    Shot,
    Change,
    idle
};

class Weapon
{
protected:
    float DMG;
    float angle;
    unsigned int rays_count;
    int max_ammo;
    int ammo;
    size_t current_frame;
    size_t shot_delay;

    Animation_type anim_type;
    sf::SoundBuffer shot_Buf;
    sf::Sound shot_sound;

    sf::Time animation_time;
    sf::Vector2i current_Frame;
    sf::Vector2i extra_Frame;
    sf::Vector2i idle;
    std::vector<sf::Vector2i> Reload_animation_pos;
    std::vector<sf::Vector2i> shot_animation_pos;
    std::vector<sf::Vector2i> Change_Animation_pos;
    std::vector<sf::Vector2i> muzzle_flash_pos;

    sf::RectangleShape barrel;

    virtual void Reload_Animation();
    void Shot_Animation();
    void Change_Animation();
    void draw_your_weapon();
    void put_your_weapon_away();
public:
    Weapon();
    ~Weapon();
    void hit_scan();
    void Shot();
    void Change();
    void Reload();
    sf::Vector2i Animation(sf::Time cl);
    sf::Vector2i Extra_Animation();
    bool extra;
    bool active;
//    friend void deal_dmg(Character &ch,Map &m);
};

#endif // WEAPON_H
