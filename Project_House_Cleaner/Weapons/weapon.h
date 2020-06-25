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
    int max_ammo;
    size_t current_frame;
    size_t shot_delay;

    Animation_type anim_type;
    sf::SoundBuffer shot_Buf;
    sf::Sound shot_sound;

    sf::Time animation_time;
    sf::Vector2i current_Frame;
    sf::Vector2i extra_Frame;
    sf::Vector2i idle;

    sf::Vector2f barrel_point_one;
    sf::Vector2f barrel_point_two;
    int barrel_one_offset_x;
    int barrel_two_offset_x;
    int barrel_offset_y;

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
    sf::Vector2f hit_place(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4);

public:
    Weapon();
    ~Weapon();
    void hit_scan();
    void Shot();
    void Change();
    void Reload();
    sf::Vector2i Animation(sf::Time cl);
    sf::Vector2i Extra_Animation();
    virtual std::vector<sf::Vector2f> hits(std::vector<sf::RectangleShape> walls, sf::Vector2f pos, float rotation) = 0;
    void Bot_options();
    bool hit_show;
    bool extra;
    bool active;
    float DMG;
    int ammo;
};

#endif // WEAPON_H
