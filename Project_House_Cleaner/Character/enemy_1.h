#ifndef ENEMY_1_H
#define ENEMY_1_H

#include "character.h"

class Enemy_1 : public Character
{
protected:
    void draw_a_dir();
    int dir;
public:
    Enemy_1(sf::Vector2f pos);
    void attack();
    friend void cheak_if_hit(Enemy_1 &ch, sf::Vector2f point, float dmg);
    void update_status(sf::Time tm);
    void change_dir(std::vector<sf::RectangleShape> walls);

};

#endif // ENEMY_1_H
