#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Character : public sf::Sprite
{
protected:
    int hp;
    sf::Texture texture;
    float vel_y;
    float vel_x;
    sf::IntRect texture_box;
    sf::RectangleShape character_bounds;

    sf::Vector2f pr_pos;
    void load_texture(const char* file);
public:
    Character();
    bool colision(std::vector<sf::RectangleShape> walls);
    void point_contains_colison(std::vector<sf::RectangleShape> walls);
    void face_to(sf::Vector2f aim);
//    virtual void movement(sf::Time el);
//    virtual void attack();
    virtual void update_status(sf::Time tm) = 0;
//    friend void cheak_if_hit(Character &, sf::Vector2f point, float dmg);
    sf::RectangleShape hit_box(){return character_bounds;};
    void hit_hp(float dmg);
    bool is_dead;
};

#endif // CHARACTER_H
