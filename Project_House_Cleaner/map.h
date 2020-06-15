#ifndef MAP_H
#define MAP_H

#include <thread>


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

struct Elevator
{
    Elevator(){ };
    Elevator(sf::RectangleShape &door_1,
             sf::RectangleShape &door_2,
             sf::RectangleShape &tp_space,
             sf::RectangleShape &open_zone,
             bool used);
    sf::RectangleShape door[2];
    sf::RectangleShape tp_space;    
    sf::RectangleShape open_zone;
    bool used = false;
    int level;
    std::pair<sf::Vector2f, sf::Vector2f> wall[8];
    sf::Vector2f points[2][4];  
    
    float door_gape = 2.5;
    void refresh_walls(size_t i);
    void door_move(sf::Vector2f pos, sf::Time cl);
    //std::pair<sf::RectangleShape, sf::RectangleShape> door_move(sf::Vector2f pos, sf::Time cl); //sprawdz czy void nie lepszy
};



class Map
{
protected:
    std::vector<Wall> Walls;
    Wall window_frame[2];
    int actual_level = 0;
    const int pix_size = 60;
    float door_open_ = 2;

    std::vector<std::vector<int>> map_grid;
    std::vector<sf::Vector2f> intersection_point;

    void convert_bitMap_to_grid(const char* file);
    void grid_to_walls();
    void elevator_door(size_t i,size_t j);
    void cheak_for_intersect();
    void cheak_for_door_intersect();

    std::tuple<sf::RectangleShape, sf::RectangleShape,bool> tp_space_detect(size_t i,size_t j);
    Wall Struct_walls(const sf::RectangleShape &bryla);
    sf::Vector2f intersection(std::pair<sf::Vector2f, sf::Vector2f> one, std::pair<sf::Vector2f, sf::Vector2f> two);
    sf::Vector2f wall_length(size_t i,size_t j);

public:
    //void operator()();
    Map();//testowy konstruktor z testowym rozłożeniem ścian
    Map(const char*  file);
    friend void set_point(Map &m, sf::RectangleShape &view, sf::Vector2f pos, sf::Clock cl);
    void set_curent_visible(sf::RectangleShape view);
    void test_Draw(sf::RenderWindow &win);
    void door_move(sf::Vector2f pos, sf::Time cl);
    void set_new_Map(int level);

    std::vector<sf::Vector2f> point_on_screen;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls_on_screen;
    std::vector<sf::RectangleShape> Wall_cols;
    Elevator elev[2];

    std::vector<sf::Vector2f> enemy_pos;
};

#endif // MAP_H
