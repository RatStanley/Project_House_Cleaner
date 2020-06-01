#ifndef MAP_H
#define MAP_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "BMP.h"

struct Conversion
{
    RGB from;
    std::string to;
};

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
    Wall door[2];
    std::vector<std::vector<int>> map_grid;
    const int pix_size = 60;

    void Struct_wall(const sf::RectangleShape &bryla, int id);
    void convert_bitMap_to_grid(const char* file);
    void grid_to_walls();
    sf::Vector2f wall_length(size_t i,size_t j);
public:
    Map();//testowy konstruktor z testowym rozłożeniem ścian
    Map(const char*  file);
    void set_curent_visible(sf::RectangleShape view);
    friend void set_point(Map &m, sf::RectangleShape &view, sf::Vector2f pos);

    std::vector<sf::Vector2f> point_on_screen;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls_on_screen;
};

#endif // MAP_H
