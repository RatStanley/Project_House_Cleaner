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
    std::vector<std::vector<int>> map_grid;
    const int pix_size = 60;
    float door_open_ = 2;

    void Struct_wall(const sf::RectangleShape &bryla, int id);
    void convert_bitMap_to_grid(const char* file);
    void grid_to_walls();
    void elevator_dor(size_t i,size_t j);

    void cheak_for_intersect();
    void cheak_for_door_intersect();
    sf::Vector2f intersection(std::pair<sf::Vector2f, sf::Vector2f> one, std::pair<sf::Vector2f, sf::Vector2f> two);
    sf::Vector2f wall_length(size_t i,size_t j);
    std::vector<sf::Vector2f> intersection_point;

public:
    Map();//testowy konstruktor z testowym rozłożeniem ścian
    Map(const char*  file);
    void set_curent_visible(sf::RectangleShape view);
    friend void set_point(Map &m, sf::RectangleShape &view, sf::Vector2f pos, sf::Clock cl);
    sf::RectangleShape elevator;

    std::vector<sf::Vector2f> point_on_screen;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls_on_screen;

    void test_Draw(sf::RenderWindow &win);
    void door_move(sf::Vector2f pos, sf::Time cl);
    Wall door[3];

};

#endif // MAP_H
