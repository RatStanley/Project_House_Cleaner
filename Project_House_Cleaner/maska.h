#ifndef MASKA_H
#define MASKA_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class maska
{
protected:
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_walls;// load when new map loaded;
    std::vector<sf::Vector2f> all_points; // load when new map loaded;
    std::vector<sf::Vector2f> current_points;

    std::vector<sf::Vector2f> map_bound;

    std::vector<sf::Vector2f> off_set_point;
    sf::Vector2f Player_pos;

    void intersection_point();
    void sort_vector();
    void off_set();
public:
    maska();
    void rect_to_cheak(const sf::RectangleShape &bryla);
    void set_pos(sf::RectangleShape view, sf::Vector2f mysz);
    void set_Map_Bond(const sf::RectangleShape &boind, const sf::RectangleShape &frame);
    std::vector<sf::ConvexShape> Vec_mask();

    std::vector<std::vector<sf::Vector2f>> insersection;

};

#endif // MASKA_H
