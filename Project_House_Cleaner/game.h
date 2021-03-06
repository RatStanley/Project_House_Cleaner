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

    sf::Font font;
    sf::RectangleShape text_box[3];
    sf::Text hud_info[3];

    sf::Music ambient_sound;

    sf::Texture particle_tex;
    std::vector<std::pair<sf::Sprite,int>*> particle_vec;
    std::vector<std::pair<sf::Sprite,int>*>::iterator par_it;
    sf::Sprite particle;
    sf::Time frame_time;

    sf::Vector2f mouse_pos;
    sf::Vector2f player_pos;
    sf::RectangleShape View_rec;

    std::vector<Enemy_1*> enemy_vec;
    std::vector<Enemy_1*>::iterator enemy_it;
    std::vector<sf::RectangleShape> wall;
    std::vector<sf::RectangleShape> all_walls;
    bool end_game;


    void set_enemy();
    void set_Game();
    bool is_hit();

    void Enemy_logic(sf::Time cl);
    void Enemy_move(sf::Time cl);
    void cheak_if_hit(Character &ch, sf::Vector2f point, float dmg);
    void Events(sf::Event event);
    void Draw();
    void anime_particle(sf::Time cl);
    void hud();

    void dead_screen();
    void end_screen();

public:
    Game();
    void menu();
    void Game_loop();
};

#endif // GAME_H
