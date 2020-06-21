#ifndef ENEMY_1_H
#define ENEMY_1_H

#include "character.h"

class Enemy_1 : public Character
{
public:
    Enemy_1(sf::Vector2f pos);
    void attack();
    friend void cheak_if_hit(Enemy_1 &ch, sf::Vector2f point, float dmg);

};

#endif // ENEMY_1_H
