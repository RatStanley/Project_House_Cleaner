#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "maska.h"
#include "map.h"
#include "Character/character.h"
#include "Character/hero.h"
#include "Character/enemy_1.h"

class Game
{
    maska *Maska;
    Map *mapa;
    Hero *hero;

    sf::RenderWindow *window;
    sf::Clock clock;
    sf::View view;
    sf::Vector2f mouse_pos;
    sf::Vector2f player_pos;
    sf::RectangleShape View_rec;

    std::vector<Enemy_1*> enemy_vec;
    std::vector<Enemy_1*>::iterator enemy_it;
    std::vector<sf::RectangleShape> wall;
    std::vector<sf::RectangleShape> all_walls;


    void set_enemy();
    bool is_hit();

    void Enemy_logic(sf::Time cl);
    void Enemy_move(sf::Time cl);
    void cheak_if_hit(Enemy_1 &ch, sf::Vector2f point, float dmg);
    void Events(sf::Event event);

public:
    Game();
    void Game_loop();
};

#endif // GAME_H
