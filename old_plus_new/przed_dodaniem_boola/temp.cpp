#include "temp.h"

std::vector<sf::RectangleShape> box(std::vector<std::vector<sf::Vector2f>> punkty)
{
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color(255,255,255));
    shape.setSize(sf::Vector2f(5,5));
    shape.setOrigin(2.5,2.5);

    std::vector<sf::RectangleShape> boxy;

    int tr = 0;

    for(auto& el : punkty)
    {
        for(auto& vec : el)
        {
        shape.setPosition(vec);
        boxy.emplace_back(shape);
        shape.setSize(sf::Vector2f(5+tr,5+tr));
        }
//        shape.setOrigin(5+tr/2,5+tr/2);
//        tr+=1;
    }
    //std::cout << punkty.size() << std::endl;
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

std::vector<std::vector<sf::Vector2f>> intersection_point(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines, std::vector<sf::Vector2f> points_enti, sf::Vector2f mysz)
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
        bool edge = false;

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
//            std::vector<std::pair<float, sf::Vector2f>> to_sort;
//            for(auto& el : temp)
//            {
//                to_sort.emplace_back(pow(x4-el.x,2) + pow(y4-el.y,2),el);
//            }
//            std::sort(to_sort.begin(),to_sort.end(), [](std::pair<float, sf::Vector2f> one, std::pair<float, sf::Vector2f> two){return one.first < two.first;});
            std::sort(temp.begin(), temp.end(), [x4, y4](sf::Vector2f one, sf::Vector2f two) {return pow(x4-one.x,2) + pow(y4-one.y,2) < pow(x4-two.x,2) + pow(y4-two.y,2);});
//            std::vector<sf::Vector2f> to_vector;

//            for(size_t i = 0; i < to_sort.size(); i++)
//            {
//                    to_vector.emplace_back(to_sort[i].second);
//                    points.emplace_back(to_sort[i].second);
//            }

//            vector_of_lines.emplace_back(to_vector);
            //vector_of_lines.emplace_back(temp);
            for(auto& poin : points_enti)
            {
                if((temp[0].x == poin.x && temp[0].y == poin.y) || (temp[temp.size()-1].x == poin.x && temp[temp.size()-1].y == poin.y))
                {
                    vector_of_lines.emplace_back(temp);
                    break;
                }
            }
        }



    }
    //std::cout << vector_of_lines.size() << std::endl;
    return vector_of_lines;
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

std::vector<std::vector<sf::Vector2f>> sort(std::vector<std::vector<sf::Vector2f>> points_vect, sf::Vector2f mysz)//w razie porblemów z wydajnością
{
    sf::RectangleShape rey;
    std::vector<std::vector<sf::Vector2f>> sorted;
//    std::vector<size_t> iter;
    std::vector<std::pair<size_t, size_t>> iter;

    std::vector<sf::Vector2f> points;

    for(auto& el : points_vect)
    {
        points.emplace_back(el[0]);
    }

    for(size_t index = 0; index < points.size(); index += 1)
    {
        float x = 0;
        float y = 0;

        rey.setSize(sf::Vector2f(1,10));
        rey.setPosition(mysz);

        std::vector<std::pair<float, float>> distance;


        float resolution = 1;       //największe obciażenie
        for(float i = 0; i < 360; i+=resolution) // sprawdza ktory jest najblizej i zapisuje go w wektorze
        {
            rey.rotate(resolution);

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
        std::sort(distance.begin(),distance.end()); // sortuje według odległości
        iter.emplace_back(distance[0].second, index); // zapisuje kąt plus indeks wektora głównego
    }

//    std::vector<std::pair<float, sf::Vector2f>> to_sort_1;
//    std::vector<std::pair<float, sf::Vector2f>> to_sort_2;
//    for(size_t i = 0; i < points.size()/2; i ++)
//    {
//        to_sort_1.emplace_back(iter[i],points[i*2]);
//        //to_sort.emplace_back(iter[i],points[i*2+1]);
//    }
//    for(size_t i = 0; i < points.size()/2; i ++)
//    {
//        //to_sort.emplace_back(iter[i],points[i*2]);
//        to_sort_2.emplace_back(iter[i],points[i*2+1]);
//    }
//    std::sort(to_sort_1.begin(),to_sort_1.end(),[](std::pair<float, sf::Vector2f> one, std::pair<float, sf::Vector2f> two){return one.first < two.first;});
//    std::sort(to_sort_2.begin(),to_sort_2.end(),[](std::pair<float, sf::Vector2f> one, std::pair<float, sf::Vector2f> two){return one.first < two.first;});
//    for(size_t i = 0; i < to_sort_1.size(); i++)
//    {
//        sorted.emplace_back(to_sort_1[i].second);
//        sorted.emplace_back(to_sort_2[i].second);
//    }
    std::sort(iter.begin(),iter.end(), [](std::pair<size_t, size_t> one, std::pair<size_t, size_t> two){return one.first > two.first;});
    for(auto& el : iter)
        sorted.emplace_back(points_vect[el.second]);
    return  sorted;
}

sf::ConvexShape mask(std::vector<sf::Vector2f> points)
{
    sf::ConvexShape temp;
    temp.setFillColor(sf::Color(50,50,50));
    temp.setPointCount(points.size());

    for(size_t i = 0; i < points.size()/2; i++)
    {
        temp.setPoint(i,points[i*2]);
    }
    for(size_t i = 0; i < points.size()/2; i++)
    {
        temp.setPoint( i,points[points.size()-(i*2)-2]);
    }
    return temp;
}

std::vector<sf::ConvexShape> vector_mask(std::vector<sf::Vector2f> points)
{
    sf::ConvexShape maska;
    maska.setFillColor(sf::Color(50,50,50));
    maska.setPointCount(3);

    std::vector<sf::ConvexShape> vec;

    for(size_t i = 0; i < points.size()-2; i++)
    {
        //maska.setPosition(points[i]);
        maska.setPoint(0,points[i]);
        maska.setPoint(1,points[i+1]);
        maska.setPoint(2,points[i+2]);
        vec.emplace_back(maska);
    }
    return vec;
}

std::vector<sf::ConvexShape> vector_v2_mask(std::vector<std::vector<sf::Vector2f>> points)
{
    sf::ConvexShape maska;
    maska.setFillColor(sf::Color(50,50,50));
    maska.setPointCount(3);

    bool is_visible = false;
    std::vector<sf::ConvexShape> vec;
    for(size_t i = 1; i < points.size(); i++)
    {
//        if(is_visible && points[i].size() == 2)
//        {
//            maska.setPointCount(points[i].size() + points[i-1].size());
//            for(size_t j = 0; j < points[i].size(); j++)
//            {
//                maska.setPoint(j,points[i][j]);
//            }
//            for(size_t j = 0; j < points[i-1].size(); j++)
//            {
//                maska.setPoint(points[i].size() + j,points[i-1][points[i-1].size() - 1 - j]);
//            }
//            vec.emplace_back(maska);
//            is_visible = false;
//        }
        //else
        if(points[i].size() == 2)
        {
            continue;
        }
        else if(points[i].size() == points[i-1].size())
        {
            maska.setPointCount(points[i].size()*2);
            for(size_t j = 0; j < points[i].size(); j++)
            {
                maska.setPoint(j,points[i][j]);
            }
            for(size_t j = 0; j < points[i-1].size(); j++)
            {
                maska.setPoint(points[i].size() + j,points[i-1][points[i-1].size() - 1 - j]);
            }
            vec.emplace_back(maska);
        }
        else if(points[i].size() >= points[i-1].size())
        {
            maska.setPointCount(points[i].size() + points[i-1].size());
            for(size_t j = 0; j < points[i].size(); j++)
            {
                maska.setPoint(j,points[i][j]);
            }
            for(size_t j = 0; j < points[i-1].size(); j++)
            {
                maska.setPoint(points[i].size() + j,points[i-1][points[i-1].size() - 1 - j]);
            }
            vec.emplace_back(maska);
            is_visible = false;
        }
        else if(points[i].size() < points[i-1].size())
        {
            maska.setPointCount(points[i].size() + points[i-1].size());
            for(size_t j = 0; j < points[i].size(); j++)
            {
                maska.setPoint(j,points[i][j]);
            }
            for(size_t j = 0; j < points[i-1].size(); j++)
            {
                maska.setPoint(points[i].size() + j,points[i-1][points[i-1].size() - 1 - j]);
            }
            is_visible = true;
            vec.emplace_back(maska);
        }
    }
//    if(points[0].size() <= points[points.size()-1].size())
//    {
//        maska.setPointCount(points[0].size() + points[points.size()-1].size());
//        for(size_t j = 0; j < points[0].size(); j++)
//        {
//            maska.setPoint(j,points[0][j]);
//        }
//        for(size_t j = 0; j < points[points.size()-1].size(); j++)
//        {
//            maska.setPoint(points[0].size() + j,points[points.size()-1][points[points.size()-1].size() - 1 - j]);
//        }
//        is_visible = true;
//        vec.emplace_back(maska);
//    }


    return vec;
}
