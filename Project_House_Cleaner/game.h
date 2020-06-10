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

    void set_enemy();
    void Events(sf::Event event);

public:
    Game();
    void Game_loop();
};

#endif // GAME_H
