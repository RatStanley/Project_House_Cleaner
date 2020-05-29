#pragma once
#include "maska.h"
#include <math.h>
#include <iostream>

void maska::intersection_point()
{
    insersection.clear();
    float x4 = Player_pos.x;
    float y4 = Player_pos.y;

    std::vector<sf::Vector2f> points_repeat;
    for(auto& el : points)
    {
        float x3 = el.x;
        float y3 = el.y;

        std::vector<sf::Vector2f> temp;
        //bool edge = false;

        for(auto& wall : all_walls) // wektor z daną prostą
        {
            float x2 = wall.first.x;
            float y2 = wall.first.y;
            float x1 = wall.second.x;
            float y1 = wall.second.y;
            float M_t = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
            float L_t = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4);

            float m_u = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
            if(M_t != 0 && m_u != 0 )
            {
                float t = L_t/M_t;
                //float u = l_u/m_u;
                if(0<=t && t <= 1 )
                {
                    sf::Vector2f cord(x1+t*(x2-x1),y1+t*(y2-y1));
                    sf::Vector2f rogi_offset(x3-x4,y3-y4);
                    sf::Vector2f cord_offset(cord.x-x4,cord.y-y4);
                    float iloczyn = rogi_offset.x*cord_offset.x+rogi_offset.y*cord_offset.y;
                    if(iloczyn > 0)
                    {
                        bool already_is = false;
                        for(auto& el : points_repeat)
                        {
                            if(el == cord)
                                already_is = true;
                        }
                        for(auto& el : temp) //wyłącza przecięcia na rogach
                        {
                            if(el == cord)
                                already_is = true;
                        }
                        if(already_is)
                            continue;
                        temp.emplace_back(cord);
                    }
                }
            }
        }

        if(temp.size() > 1)
        {
            std::sort(temp.begin(), temp.end(), [x4, y4](sf::Vector2f one, sf::Vector2f two) {return pow(x4-one.x,2) + pow(y4-one.y,2) < pow(x4-two.x,2) + pow(y4-two.y,2);});

            for(auto& poin : points)
            {
                if((temp[0].x == poin.x && temp[0].y == poin.y) || (temp[temp.size()-1].x == poin.x && temp[temp.size()-1].y == poin.y))
                {
                    insersection.emplace_back(temp);
                    break;
                }
            }
        }
        for(auto& el : temp)
            points_repeat.emplace_back(el);

    }
        //std::cout << insersection.size() << std::endl;

}

void maska::sort_vector()
{
    std::vector<std::vector<sf::Vector2f>> sorted;
    std::vector<double> vec_of_angle;
    double angle;
    for(auto& el : insersection)
    {
        if(el[0].x < Player_pos.x && el[0].y >= Player_pos.y)
        {
            angle = 90-atan2(el[0].y - Player_pos.y,  Player_pos.x - el[0].x)* 180 / M_PI;
        }
        else if(el[0].x <= Player_pos.x && el[0].y < Player_pos.y)
        {
            angle = atan2(Player_pos.y - el[0].y, Player_pos.x - el[0].x)* 180 / M_PI +90;
        }
        else if(el[0].x > Player_pos.x && el[0].y <= Player_pos.y)
        {
            angle =90- atan2(Player_pos.y - el[0].y,el[0].x - Player_pos.x)* 180 / M_PI +180;
        }
        else if(el[0].x >= Player_pos.x && el[0].y > Player_pos.y)
        {
            angle = atan2(el[0].y - Player_pos.y,el[0].x - Player_pos.x)* 180 / M_PI +270;
        }

        vec_of_angle.emplace_back(angle);
        sorted.emplace_back(el);
        if(vec_of_angle.size() != 1)
        {
            for (size_t i = 0; i < vec_of_angle.size() - 1; i++)
            {
                for (size_t j = 0; j < vec_of_angle.size()-i-1; j++)
                {
                    if (vec_of_angle[j] > vec_of_angle[j+1])
                    {
                        std::swap(sorted[j], sorted[j+1]);
                        std::swap(vec_of_angle[j],vec_of_angle[j+1]);
                    }
                }
            }
        }
    }
    sorted.emplace_back(sorted[0]);
    insersection =  sorted;
}

void maska::off_set()
{
    off_set_point.clear();
    std::vector<std::pair<size_t, size_t>> val;
    float x4 = Player_pos.x;
    float y4 = Player_pos.y;


    for(size_t i = 1; i < insersection.size(); i++)
    {
        float x3 = insersection[i][0].x;
        float y3 = insersection[i][0].y;

            if(insersection[i][0].y > insersection[i-1][0].y)
            {
                y3 = insersection[i-1][0].y + (insersection[i][0].y - insersection[i-1][0].y)/2;
            }
            else
            {
                y3 = insersection[i][0].y + (insersection[i-1][0].y - insersection[i][0].y)/2;
            }

            if(insersection[i][0].x > insersection[i-1][0].x)
            {
                x3 = insersection[i-1][0].x + (insersection[i][0].x - insersection[i-1][0].x)/2;
            }
            else
            {
                x3 = insersection[i][0].x + (insersection[i-1][0].x - insersection[i][0].x)/2;
            }



        std::vector<sf::Vector2f> temp;

        for(auto& wall : all_walls) // wektor z daną prostą
        {
            float x2 = wall.first.x;
            float y2 = wall.first.y;
            float x1 = wall.second.x;
            float y1 = wall.second.y;
            float M_t = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
            float L_t = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4);

            float m_u = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
            if(M_t != 0 && m_u != 0 )
            {
                float t = L_t/M_t;
                if(0<=t && t <= 1 )
                {
                    sf::Vector2f cord(x1+t*(x2-x1),y1+t*(y2-y1));
                    sf::Vector2f rogi_offset(x3-x4,y3-y4);
                    sf::Vector2f cord_offset(cord.x-x4,cord.y-y4);
                    float iloczyn = rogi_offset.x*cord_offset.x+rogi_offset.y*cord_offset.y;
                    if(iloczyn > 0)
                    {
                        bool already_is = false;

                        for(auto& el : temp) //wyłącza przecięcia na rogach
                        {
                            if(el == cord)
                                already_is = true;
                        }
                        if(already_is)
                            continue;
                        temp.emplace_back(cord);
                    }
                }
            }
        }

        if(temp.size() > 1)
        {
            std::sort(temp.begin(), temp.end(), [x4, y4](sf::Vector2f one, sf::Vector2f two) {return pow(x4-one.x,2) + pow(y4-one.y,2) < pow(x4-two.x,2) + pow(y4-two.y,2);});
            off_set_point.emplace_back(temp[0]);
        }
    }
}

maska::maska()
{
    //setFillColor(sf::Color(50,50,50));
}

void maska::rect_to_cheak(const sf::RectangleShape &bryla)
{
    std::pair<sf::Vector2f, sf::Vector2f> linia;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines;

    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
    };
    all_walls.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
    };
    all_walls.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
    };
    all_walls.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

    };
    all_walls.emplace_back(linia);

    points.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
    points.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
    points.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    points.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
}

void maska::set_pos(sf::RectangleShape view, sf::Vector2f mysz)
{
    current_view = view;
    Player_pos = mysz;
}


std::vector<sf::ConvexShape> maska::Done_maska()
{
    intersection_point();
    sort_vector();
    off_set();
    std::vector<sf::ConvexShape> vec;
    sf::ConvexShape maska;
    maska.setFillColor(sf::Color(50,50,50));


    for(size_t i = 1; i < insersection.size(); i++)
    {
        size_t idx_first = 0;
        size_t idx_sec = 0;

        for(size_t id_f = 0; id_f < insersection[i].size(); id_f ++)
        {
            bool next = false;
            for(size_t id_s = 0; id_s < insersection[i].size(); id_s ++)
            {
                if(insersection[i][id_f].x == off_set_point[i-1].x && insersection[i-1][id_s].x == off_set_point[i-1].x)
                {
                    idx_first = id_f;
                    idx_sec = id_s;
                    next = true;
                    break;
                }
                else if(insersection[i][id_f].y == off_set_point[i-1].y && insersection[i-1][id_s].y == off_set_point[i-1].y)
                {
                    idx_first = id_f;
                    idx_sec = id_s;
                    next = true;
                    break;
                }
            }
            if(next)
                break;
        }
        maska.setPointCount(4);
        maska.setPoint(0,insersection[i][idx_first]);
        maska.setPoint(1,insersection[i][insersection[i].size()-1]);
        maska.setPoint(2,insersection[i-1][insersection[i-1].size()-1]);
        maska.setPoint(3,insersection[i-1][idx_sec]);
        vec.emplace_back(maska);
    }
    return vec;
}
