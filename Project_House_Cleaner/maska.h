#ifndef MASKA_H
#define MASKA_H
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class maska
{
protected:
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_walls;// load when new map loaded;
    std::vector<sf::Vector2f> points; // load when new map loaded;

    sf::RectangleShape current_view;
    sf::Vector2f Player_pos;

    void intersection_point();
    void sort_vector();
    void off_set();
public:
    maska();
    void rect_to_cheak(const sf::RectangleShape &bryla);
    void set_pos(sf::RectangleShape view, sf::Vector2f mysz);
    std::vector<sf::ConvexShape> Done_maska();

    std::vector<std::vector<sf::Vector2f>> insersection;
    std::vector<sf::Vector2f> off_set_point;

};

#endif // MASKA_H
