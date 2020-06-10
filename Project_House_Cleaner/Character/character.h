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
//    sf::FloatRect hit_box;
    sf::IntRect texture_box;
    void load_texture(const char* file);
//    void animations();
public:
    Character();
    void colision(sf::RectangleShape &el);
    void face_to(sf::Vector2f aim);
    virtual void movement() = 0;
    virtual void attack() = 0;
//    void update_status(sf::Time tm);

};

#endif // CHARACTER_H
