#include "map.h"

void Map::Struct_wall(const sf::RectangleShape &bryla, int id)
{
    Wall Temp;
    if(id == 0 || id == 1) // deklaracja ramek
    {
        window_frame[id].rect = bryla;

        window_frame[id].wall[0] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
        };
        window_frame[id].wall[1] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
        };
        window_frame[id].wall[2] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
        };
        window_frame[id].wall[3] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

        };

        window_frame[id].points[0] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
        window_frame[id].points[1] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
        window_frame[id].points[2] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
        window_frame[id].points[3] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    }
    else if(id == 2)
    {
        Temp.rect = bryla;

        Temp.wall[0] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
        };
        Temp.wall[1] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
        };
        Temp.wall[2] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
        };
        Temp.wall[3] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

        };

        Temp.points[0] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
        Temp.points[1] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
        Temp.points[2] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
        Temp.points[3] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
        Walls.emplace_back(Temp);
    }

}

Map::Map()
{

    sf::RectangleShape map_borders;
    map_borders.setSize(sf::Vector2f(12800,7200));
    map_borders.setPosition(map_borders.getSize().x/2,map_borders.getSize().y/2);
    map_borders.setOrigin(map_borders.getSize().x/2,map_borders.getSize().y/2);

    Struct_wall(map_borders,0);

    sf::RectangleShape map_frame;
    map_frame.setSize(map_borders.getSize());
    map_frame.setOrigin(map_frame.getSize().x/2,map_frame.getSize().y/2);
    map_frame.setPosition(map_borders.getPosition());
    map_frame.setScale(1.01,1.02);

    Struct_wall(map_frame,1);

    sf::RectangleShape sth;
    sth.setSize(sf::Vector2f(25,500));
    sth.setPosition(700,100);
    sth.setFillColor(sf::Color(100,100,100));
    Struct_wall(sth,2);

    sf::RectangleShape sec;
    sec.setSize(sf::Vector2f(5000,25));
    sec.setPosition(10,900);
    sec.setFillColor(sf::Color(100,100,100));
    Struct_wall(sec,2);

    sf::RectangleShape new_;
    new_.setSize(sf::Vector2f(500,25));
    new_.setPosition(600,600);
    new_.setFillColor(sf::Color(100,100,100));
    Struct_wall(new_,2);

    sf::RectangleShape new_2;
    new_2.setSize(sf::Vector2f(500,25));
    new_2.setPosition(100,300);
    new_2.setFillColor(sf::Color(100,100,100));
    Struct_wall(new_2,2);

    sf::RectangleShape new_3;
    new_3.setSize(sf::Vector2f(500,25));
    new_3.setPosition(725,200);
    new_3.setFillColor(sf::Color(100,100,100));
    Struct_wall(new_3,2);

}

void Map::set_curent_visible(sf::RectangleShape view)
{
    point_on_screen.clear();
    walls_on_screen.clear();

    for(auto& frame : window_frame)
    {
        point_on_screen.emplace_back(frame.points[0]);
        point_on_screen.emplace_back(frame.points[1]);
        point_on_screen.emplace_back(frame.points[2]);
        point_on_screen.emplace_back(frame.points[3]);
        walls_on_screen.emplace_back(frame.wall[0]);
        walls_on_screen.emplace_back(frame.wall[1]);
        walls_on_screen.emplace_back(frame.wall[2]);
        walls_on_screen.emplace_back(frame.wall[3]);
    }
    for(auto& el : Walls)
    {
        if(view.getGlobalBounds().intersects(el.rect.getGlobalBounds()))
        {
            for(size_t i = 0; i < 4; i++)
            {
                point_on_screen.emplace_back(el.points[i]);
                walls_on_screen.emplace_back(el.wall[i]);
            }
        }

    }
}
