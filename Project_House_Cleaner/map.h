#ifndef MAP_H
#define MAP_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct Wall
{
    sf::RectangleShape rect;
    sf::Vector2f points[4];
    std::pair<sf::Vector2f, sf::Vector2f> wall[4];
};

class Map
{
protected:
    std::vector<Wall> Walls;
    Wall window_frame[2];

    void Struct_wall(const sf::RectangleShape &bryla, int id);
public:
    Map();
    void set_curent_visible(sf::RectangleShape view);
    friend void set_point(Map &m, sf::RectangleShape &view, sf::Vector2f pos);

    std::vector<sf::Vector2f> point_on_screen;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls_on_screen;
};

#endif // MAP_H
