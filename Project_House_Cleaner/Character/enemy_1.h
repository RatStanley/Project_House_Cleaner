#ifndef ENEMY_1_H
#define ENEMY_1_H

#include "character.h"
#include "Weapons/pistol.h"

class Enemy_1 : public Character
{
protected:
    void draw_a_dir();
    int dir;
    sf::RectangleShape vision;
    std::vector<std::vector<int>> map_grid;
    sf::Vector2f hero_pos;

    Pistol pistol;

    std::vector<sf::RectangleShape> walls;
public:
    Enemy_1(sf::Vector2f pos, std::vector<sf::RectangleShape> walls);
    void attack();
//    friend void cheak_if_hit(Enemy_1 &ch, sf::Vector2f point, float dmg);
    void update_status(sf::Time tm);
    void hear_shot(sf::Vector2f new_hero_pos_);
    void change_dir();
    void see_hero_();
    void new_hero_pos(sf::Vector2f hero_pos_);
    void go_to_hero_pos(sf::Time tm);

    bool follow;
    bool see_hero;
    int dmg;


};

#endif // ENEMY_1_H
