#include "temp.h"
#include <math.h>


std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rect(const sf::RectangleShape &bryla)
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

std::vector<std::vector<sf::Vector2f>> intersection_point( const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> &all_lines, const std::vector<sf::Vector2f> &points_enti, const sf::Vector2f &mysz)
{
    float x4 = mysz.x;
    float y4 = mysz.y;

    std::vector<sf::Vector2f> points;
    std::vector<std::vector<sf::Vector2f>> vector_of_lines;
    for(auto& el : points_enti)
    {
        float x3 = el.x;
        float y3 = el.y;

        std::vector<sf::Vector2f> temp;
        //bool edge = false;

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

            for(auto& poin : points_enti)
            {
                if((temp[0].x == poin.x && temp[0].y == poin.y) || (temp[temp.size()-1].x == poin.x && temp[temp.size()-1].y == poin.y))
                {
                    vector_of_lines.emplace_back(temp);
                    break;
                }
            }
        }
        for(auto& el : temp)
            points.emplace_back(el);



    }
    //std::cout << vector_of_lines.size() << std::endl;
    return vector_of_lines;
}

std::vector<sf::Vector2f> points_to_cheak(const sf::RectangleShape &bryla)
{
    std::vector<sf::Vector2f> temp;
    temp.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
    temp.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
    temp.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    temp.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    return temp;
}

std::vector<std::vector<sf::Vector2f>> sort_vector(std::vector<std::vector<sf::Vector2f>> points_vect, const sf::Vector2f &mysz)//mysz -> srodek układu
{
    //sf::Vector2f ekran(1280,720); //do przekazania to będze
    ///   2 \  3
    /// ---------
    ///   1 \  4
    ///

    std::vector<std::vector<sf::Vector2f>> sorted;
    std::vector<double> vec_of_angle;
    double angle;
    for(auto& el : points_vect)
    {
        if(el[0].x < mysz.x && el[0].y >= mysz.y)
        {
            angle = 90-atan2(el[0].y - mysz.y,  mysz.x - el[0].x)* 180 / M_PI;
        }
        else if(el[0].x <= mysz.x && el[0].y < mysz.y)
        {
            angle = atan2(mysz.y - el[0].y, mysz.x - el[0].x)* 180 / M_PI +90;
        }
        else if(el[0].x > mysz.x && el[0].y <= mysz.y)
        {
            angle =90- atan2(mysz.y - el[0].y,el[0].x - mysz.x)* 180 / M_PI +180;
        }
        else if(el[0].x >= mysz.x && el[0].y > mysz.y)
        {
            angle = atan2(el[0].y - mysz.y,el[0].x - mysz.x)* 180 / M_PI +270;
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
    return sorted;
}

std::vector<sf::ConvexShape> vector_v2_mask(const std::vector<std::vector<sf::Vector2f>> &points, const std::vector<sf::Vector2f> &vert)
{
    sf::ConvexShape maska;
    maska.setFillColor(sf::Color(50,50,50));

    std::vector<sf::ConvexShape> vec;
    //points.emplace_back(points[0]); // by brało pod uwagę pierwszy punkt

    std::vector<size_t> off_set;
    for(size_t i = 0; i < points.size(); i++)
    {
        size_t temp = 0;
        for(size_t j = 0; j < points.size(); j++)
        {
            if(temp != j)
            {
                off_set.emplace_back(temp);
                break;
            }
            for(auto& el : vert)
            {
                if(points[i][j] == el)
                {
                    temp++;
                    break;
                }
            }
        }
    }


    for(size_t i = 1; i < points.size(); i++)
    {
        maska.setFillColor(sf::Color(50,50,50));
        size_t idx_first = 0;
        size_t idx_sec = 0;

        if(off_set[i] == 0 && off_set[i-1] == 0)
        {
            idx_first = 1;
            idx_sec = 1;
        }
        else if(off_set[i] == 0 && off_set[i-1] > 0)
        {
            if(points[i].size() == points[i-1].size())
            {

                if(points[i+1].size() > points[i].size())
                {
                    idx_first = off_set[i];
                    idx_sec = off_set[i-1];
                    if(points[i-1][0].x == points[i-1][1].x)
                    {
                        idx_first = 0;
                        idx_sec = 0;
                    }
                    else
                    {
                        idx_first = off_set[i];
                        idx_sec = off_set[i-1];
                    }
                }
                else if(points[i+1].size() < points[i].size())
                {
                    idx_first = off_set[i];
                    idx_sec =0;
                }
                else
                {
                    idx_first = 0;
                    idx_sec = 0;
                }


            }
            else if(points[i].size() > points[i-1].size())
            {

                idx_first = off_set[i];
                idx_sec = 0;
            }
            else if(points[i].size() < points[i-1].size())
            {

                idx_first = 0;
                idx_sec = off_set[i-1];
                if(points[i+1].size() > points[i].size())
                {
                    idx_first = off_set[i];
                    idx_sec = off_set[i-1];
                }
                else if(points[i+1].size() < points[i].size())
                {
                    idx_first = 0;
                    idx_sec =off_set[i-1];
                }
                else
                {
                    idx_first = off_set[i];
                    idx_sec = off_set[i-1];
                }
            }

        }
        else if(off_set[i] > 0 && off_set[i-1] == 0)
        {
            if(points[i].size() == points[i-1].size())
            {

                if(points[i-1][0].x != points[i-1][1].x)
                {

                    if(points[i-1][0].x == points[i][0].x || points[i-1][0].y == points[i][0].y )
                    {
                        idx_first = 0;
                        idx_sec = 0;
                    }
                    else
                    {
                        idx_first =  off_set[i];
                        idx_sec = off_set[i-1];
                    }

                }
                else
                {
                    idx_first = off_set[i];
                    idx_sec = off_set[i-1];
                }

            }
            else if(points[i].size() > points[i-1].size())
            {
                idx_first = off_set[i];
                idx_sec = 0;
            }
            else if(points[i].size() < points[i-1].size())
            {
                idx_first = 0;
                idx_sec = off_set[i-1];
            }

        }
        else if(off_set[i] > 0 && off_set[i-1] > 0)
        {
            if(points[i].size() == points[i-1].size())
            {
                idx_first = off_set[i];
                idx_sec = off_set[i-1];
            }
            else if(points[i].size() > points[i-1].size())
            {
                idx_first = off_set[i];
                idx_sec = 0;
            }
            else if(points[i].size() < points[i-1].size())
            {
                idx_first = 0;
                idx_sec = off_set[i-1];
            }
            if(points[i][0].x == points[i][1].x && points[i][0].y > points[i][1].y)
            {
                //idx_sec ++;
            }
            else if(points[i][0].x == points[i][1].x && points[i][0].y < points[i][1].y)
            {
                idx_sec ++;
            }
            else if(points[i-1][0].x == points[i-1][1].x && points[i-1][0].y > points[i-1][1].y)
            {
                idx_first ++;
            }
            else if(points[i-1][0].x == points[i-1][1].x && points[i-1][0].y < points[i-1][1].y)
            {
                idx_first ++;
            }
        }
        if(points[i].size()-1 <= idx_first)
        {
            if(points[i].size()-1 == idx_first)
                idx_first --;

            else
            idx_first = 0;
        }
        if(points[i-1].size()-1 <= idx_sec)
        {
               idx_sec = 0;
        }

        maska.setPointCount(4);
        maska.setPoint(0,points[i][idx_first]);
        maska.setPoint(1,points[i][points[i].size()-1]);
        maska.setPoint(2,points[i-1][points[i-1].size()-1]);
        maska.setPoint(3,points[i-1][idx_sec]);
        vec.emplace_back(maska);
    }
    return vec;
}


std::vector<sf::Vector2f> off_set(const std::vector<std::pair<sf::Vector2f, sf::Vector2f> > &all_lines, std::vector<std::vector<sf::Vector2f> > points, const sf::Vector2f &mysz)
{
    std::vector<sf::Vector2f> off_Set;

    std::vector<std::pair<size_t, size_t>> val;


    float x4 = mysz.x;
    float y4 = mysz.y;


    for(size_t i = 1; i < points.size(); i++)
    {
        float x3 = points[i][0].x;
        float y3 = points[i][0].y;

            if(points[i][0].y > points[i-1][0].y)
            {
                y3 = points[i-1][0].y + (points[i][0].y - points[i-1][0].y)/2;
            }
            else
            {
                y3 = points[i][0].y + (points[i-1][0].y - points[i][0].y)/2;
            }

            if(points[i][0].x > points[i-1][0].x)
            {
                x3 = points[i-1][0].x + (points[i][0].x - points[i-1][0].x)/2;
            }
            else
            {
                x3 = points[i][0].x + (points[i-1][0].x - points[i][0].x)/2;
            }



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
            off_Set.emplace_back(temp[0]);
        }
    }
    return off_Set;
}


std::vector<sf::ConvexShape> Done_maska(const std::vector<std::vector<sf::Vector2f>> &points, const std::vector<sf::Vector2f> &vertoff_Set)
{
    sf::ConvexShape maska;
    maska.setFillColor(sf::Color(50,50,50));

    std::vector<sf::ConvexShape> vec;
    //points.emplace_back(points[0]); // by brało pod uwagę pierwszy punkt


    for(size_t i = 1; i < points.size(); i++)
    {
        maska.setFillColor(sf::Color(50,50,50));
        size_t idx_first = 0;
        size_t idx_sec = 0;

        for(size_t id_f = 0; id_f < points[i].size(); id_f ++)
        {
            bool next = false;
            for(size_t id_s = 0; id_s < points[i].size(); id_s ++)
            {
                if(points[i][id_f].x == vertoff_Set[i-1].x && points[i-1][id_s].x == vertoff_Set[i-1].x)
                {
                    idx_first = id_f;
                    idx_sec = id_s;
                    next = true;
                    break;
                }
                else if(points[i][id_f].y == vertoff_Set[i-1].y && points[i-1][id_s].y == vertoff_Set[i-1].y)
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
        maska.setPoint(0,points[i][idx_first]);
        maska.setPoint(1,points[i][points[i].size()-1]);
        maska.setPoint(2,points[i-1][points[i-1].size()-1]);
        maska.setPoint(3,points[i-1][idx_sec]);
        vec.emplace_back(maska);
    }
    return vec;
}


std::vector<sf::ConvexShape> test(const std::vector<std::vector<sf::Vector2f>> &points, const std::vector<sf::Vector2f> &vertoff_Set)
{
    sf::ConvexShape maska;
    maska.setFillColor(sf::Color(50,50,50));

    std::vector<sf::ConvexShape> vec;
    //points.emplace_back(points[0]); // by brało pod uwagę pierwszy punkt


    for(size_t i = 1; i < points.size(); i++)
    {
        maska.setFillColor(sf::Color(50,50,50));
        size_t idx_first = 0;
        size_t idx_sec = 0;

        for(size_t id_f = 0; id_f < points[i].size(); id_f ++)
        {
            bool next = false;
            for(size_t id_s = 0; id_s < points[i].size(); id_s ++)
            {
                if(points[i][id_f].x == vertoff_Set[i-1].x && points[i-1][id_s].x == vertoff_Set[i-1].x)
                {
                    idx_first = id_f;
                    idx_sec = id_s;
                    next = true;
                    break;
                }
                else if(points[i][id_f].y == vertoff_Set[i-1].y && points[i-1][id_s].y == vertoff_Set[i-1].y)
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
        maska.setPoint(0,points[i][idx_first]);
        maska.setPoint(1,points[i][points[i].size()-1]);
        maska.setPoint(2,points[i-1][points[i-1].size()-1]);
        maska.setPoint(3,points[i-1][idx_sec]);
        vec.emplace_back(maska);
    }
    return vec;
}
