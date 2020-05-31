#ifndef MASKA_H
#define MASKA_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"

class maska
{
protected:
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> visible_walls;
    std::vector<sf::Vector2f> current_points;
    std::vector<sf::Vector2f> off_set_point;
    sf::Vector2f Player_pos;

    void intersection_point();
    void sort_vector();
    void off_set();
public:
    maska();
    std::vector<sf::ConvexShape> Vec_mask();

    std::vector<std::vector<sf::Vector2f>> insersection;
    void set_point(Map &m, sf::RectangleShape &view, sf::Vector2f pos);

};

#endif // MASKA_H
