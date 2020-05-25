#include "temp.h"

std::vector<sf::RectangleShape> box(std::vector<sf::Vector2f> punkty)
{
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color(255,255,255));
    shape.setSize(sf::Vector2f(5,5));
    shape.setOrigin(2.5,2.5);

    std::vector<sf::RectangleShape> boxy;

    int tr = 0;

    for(auto& el : punkty)
    {
        shape.setPosition(el);
        boxy.emplace_back(shape);
        shape.setSize(sf::Vector2f(5+tr,5+tr));
        shape.setOrigin(5+tr/2,5+tr/2);
        tr+=1;
    }
    return boxy;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rect(sf::RectangleShape bryla)
{
    std::pair<sf::Vector2f, sf::Vector2f> linia;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines;

    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
    };
    all_lines.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
    };
    all_lines.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
    };
    all_lines.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

    };
    all_lines.emplace_back(linia);

    return all_lines;
}

std::vector<sf::Vector2f> intersection_point(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines, std::vector<sf::Vector2f> points_enti, sf::Vector2f mysz)
{
    float x4 = mysz.x;
    float y4 = mysz.y;

    std::vector<sf::Vector2f> points;

    for(auto& el : points_enti)
    {
        float x3 = el.x;
        float y3 = el.y;
        std::vector<sf::Vector2f> temp;
        for(auto& wall : all_lines) // wektor z daną prostą
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
                        for(auto& el : points)
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
        if(temp.size() > 2)
        {
            float scal_min = pow(x4-temp[0].x,2) + pow(y4-temp[0].y,2);
            float scal_max = pow(x4-temp[0].x,2) + pow(y4-temp[0].y,2);
            size_t min = 0;
            size_t max = 0;

            int counter = 0;

            for(size_t i = 0; i < temp.size(); i++)
            {
                float val = pow(x4-temp[i].x,2) + pow(y4-temp[i].y,2);

                if(val <= 0)
                    counter++;

                if(val < scal_min)
                {
                    scal_min = val;
                    min = i;
                }
                if(val > scal_max)
                {
                    scal_max = val;
                    max = i;
                }
            }
            points.emplace_back(temp[min]);
            points.emplace_back(temp[max]);
        }
    }
    //std::cout << points.size() << std::endl;
    return points;
}

std::vector<sf::Vector2f> points_to_cheak(sf::RectangleShape bryla)
{
    std::vector<sf::Vector2f> temp;
    temp.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
    temp.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
    temp.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    temp.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    return temp;
}

std::vector<sf::Vector2f> sort(std::vector<sf::Vector2f> points, sf::Vector2f mysz)
{
    sf::RectangleShape rey;
    std::vector<sf::Vector2f> sorted;
    std::vector<size_t> iter;

    for(size_t index = 0; index < points.size(); index += 2)
    {
        float x = 0;
        float y = 0;

        rey.setSize(sf::Vector2f(1,10));
        rey.setPosition(mysz);

        std::vector<std::pair<float, float>> distance;

        for(float i = 0; i < 360; i+=5)
        {
            rey.rotate(5);

            if(i < 90 && i >= 0)
            {
                x = rey.getGlobalBounds().left;
                y = rey.getGlobalBounds().top+rey.getGlobalBounds().height;
            }
            else if(i < 180 && i >= 90)
            {

                x = rey.getGlobalBounds().left;
                y = rey.getGlobalBounds().top;
            }
            else if(i < 270 && i >= 180)
            {

                x = rey.getGlobalBounds().left+rey.getGlobalBounds().width;
                y = rey.getGlobalBounds().top;

            }
            else if(i < 360 && i >= 180)
            {
                x = rey.getGlobalBounds().left+rey.getGlobalBounds().width;
                y = rey.getGlobalBounds().top+rey.getGlobalBounds().height;
            }
            float val = pow(x-points[index].x,2) + pow(y-points[index].y,2);
            distance.emplace_back(val,i);
        }
        std::sort(distance.begin(),distance.end());
        iter.emplace_back(distance[0].second);
    }
    std::vector<std::pair<float, sf::Vector2f>> to_sort_1;
    std::vector<std::pair<float, sf::Vector2f>> to_sort_2;
    for(size_t i = 0; i < points.size()/2; i ++)
    {
        to_sort_1.emplace_back(iter[i],points[i*2]);
        //to_sort.emplace_back(iter[i],points[i*2+1]);
    }
    for(size_t i = 0; i < points.size()/2; i ++)
    {
        //to_sort.emplace_back(iter[i],points[i*2]);
        to_sort_2.emplace_back(iter[i],points[i*2+1]);
    }
    std::sort(to_sort_1.begin(),to_sort_1.end(),[](std::pair<float, sf::Vector2f> one, std::pair<float, sf::Vector2f> two){return one.first < two.first;});
    std::sort(to_sort_2.begin(),to_sort_2.end(),[](std::pair<float, sf::Vector2f> one, std::pair<float, sf::Vector2f> two){return one.first < two.first;});
    for(size_t i = 0; i < to_sort_1.size(); i++)
    {
        sorted.emplace_back(to_sort_1[i].second);
        sorted.emplace_back(to_sort_2[i].second);
    }
    return  sorted;
}

sf::ConvexShape mask(std::vector<sf::Vector2f> points)
{
    sf::ConvexShape temp;
    temp.setFillColor(sf::Color(50,50,50));
    temp.setPointCount(points.size()/2);

    for(size_t i = 0; i < points.size()/2; i++)
    {
        temp.setPoint(i,points[i*2]);
    }
    //    for(size_t i = 0; i < points.size(); i++)
    //    {
    //        temp.setPoint(points.size()/2 + i,points[points.size()-(i*2)-1]);
    //    }
    return temp;
}
